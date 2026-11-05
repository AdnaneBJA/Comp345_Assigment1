#include "CommandProcessing.h"

#include <sstream>

using namespace std;

// Command

// Constructor: saves the text of the command, no effect yet
Command::Command(string text) {
    command = new string(text);
    effect = new string("");
}

// Copy constructor: deep copy of the text and the effect
Command::Command(const Command& other) {
    command = new string(*other.command);
    effect = new string(*other.effect);
}

// Destructor: frees the two strings
Command::~Command() {
    delete command;
    delete effect;
}

// Assignment operator: copies the values into our own strings
Command& Command::operator=(const Command& other) {
    if (this != &other) {
        *command = *other.command;
        *effect = *other.effect;
    }
    return *this;
}

// Prints the command and its effect
ostream& operator<<(ostream& out, const Command& command) {
    out << *command.command << " -> " << *command.effect;
    return out;
}

// Saves the effect of the command (or the error message if it was invalid)
void Command::saveEffect(string newEffect) {
    *effect = newEffect;
}

// Getter of the command text
string Command::getCommand() const {
    return *command;
}

// Getter of the effect
string Command::getEffect() const {
    return *effect;
}

// CommandProcessor

// Default constructor: empty list of commands
CommandProcessor::CommandProcessor() {
    commands = new vector<Command*>();
}

// Copy constructor: deep copy of every command
CommandProcessor::CommandProcessor(const CommandProcessor& other) {
    commands = new vector<Command*>();
    for (Command* c : *other.commands) {
        commands->push_back(new Command(*c));
    }
}

// Destructor: deletes every command, then the list
CommandProcessor::~CommandProcessor() {
    for (Command* c : *commands) {
        delete c;
    }
    delete commands;
}

// Assignment operator: deletes our commands, then deep copies the other ones
CommandProcessor& CommandProcessor::operator=(const CommandProcessor& other) {
    if (this != &other) {
        for (Command* c : *commands) {
            delete c;
        }
        commands->clear();
        for (Command* c : *other.commands) {
            commands->push_back(new Command(*c));
        }
    }
    return *this;
}

// Prints every saved command with its effect
ostream& operator<<(ostream& out, const CommandProcessor& processor) {
    out << "Saved commands:" << endl;
    for (Command* c : *processor.commands) {
        out << "  " << *c << endl;
    }
    return out;
}

// Reads a command, saves it, and returns it (nullptr when there is no more input)
Command* CommandProcessor::getCommand() {
    string text = readCommand();
    if (text == "") {
        return nullptr;
    }
    saveCommand(text);
    return commands->back();
}

// Reads one line from the console, skipping empty lines ("" at the end of input)
string CommandProcessor::readCommand() {
    string line;
    while (getline(cin, line)) {
        if (line != "") {
            return line;
        }
    }
    return "";
}

// Creates a Command and adds it to the list of commands
void CommandProcessor::saveCommand(string text) {
    commands->push_back(new Command(text));
}

// Checks if the command is valid in the current state of the game engine.
// If not, an error message is saved as the effect of the command.
bool CommandProcessor::validate(Command* command, GameEngine* engine) {
    // split the command into its name and its argument (e.g. "addplayer" and "Alice")
    stringstream ss(command->getCommand());
    string name;
    string argument;
    ss >> name >> argument;

    GameEngine::State state = engine->getState();

    // the command must exist
    if (name != "loadmap" && name != "validatemap" && name != "addplayer"
        && name != "gamestart" && name != "replay" && name != "quit") {
        command->saveEffect("Invalid: unknown command \"" + name + "\".");
        return false;
    }

    // loadmap and addplayer need an argument
    if (name == "loadmap" && argument == "") {
        command->saveEffect("Invalid: loadmap needs a map file (loadmap <mapfile>).");
        return false;
    }
    if (name == "addplayer" && argument == "") {
        command->saveEffect("Invalid: addplayer needs a player name (addplayer <playername>).");
        return false;
    }

    // the command must be allowed in the current state
    bool allowed = false;
    if (name == "loadmap") {
        allowed = state == GameEngine::State::Start || state == GameEngine::State::MapLoaded;
    }
    else if (name == "validatemap") {
        allowed = state == GameEngine::State::MapLoaded;
    }
    else if (name == "addplayer") {
        allowed = state == GameEngine::State::MapValidated || state == GameEngine::State::PlayersAdded;
    }
    else if (name == "gamestart") {
        allowed = state == GameEngine::State::PlayersAdded;
    }
    else {
        allowed = state == GameEngine::State::Win; // replay and quit
    }

    if (!allowed) {
        command->saveEffect("Invalid: " + name + " cannot be used in state \"" + engine->getStateName() + "\".");
        return false;
    }
    return true;
}

// Returns the state a valid command leads to
GameEngine::State CommandProcessor::nextState(Command* command) {
    stringstream ss(command->getCommand());
    string name;
    ss >> name; // first word of the command

    if (name == "loadmap")     return GameEngine::State::MapLoaded;
    if (name == "validatemap") return GameEngine::State::MapValidated;
    if (name == "addplayer")   return GameEngine::State::PlayersAdded;
    if (name == "gamestart")   return GameEngine::State::AssignReinforcement;
    if (name == "replay")      return GameEngine::State::Start;
    return GameEngine::State::End; // quit
}

// FileLineReader

// Constructor: opens the file
FileLineReader::FileLineReader(string name) {
    fileName = new string(name);
    file = new ifstream(name);
}

// Copy constructor: opens the same file (an ifstream cannot be copied),
// so the copy reads from the beginning of the file
FileLineReader::FileLineReader(const FileLineReader& other) {
    fileName = new string(*other.fileName);
    file = new ifstream(*fileName);
}

// Destructor: closes the file and frees the members
FileLineReader::~FileLineReader() {
    file->close();
    delete file;
    delete fileName;
}

// Assignment operator: closes our file and opens the other reader's file
FileLineReader& FileLineReader::operator=(const FileLineReader& other) {
    if (this != &other) {
        *fileName = *other.fileName;
        file->close();
        file->clear();
        file->open(*fileName);
    }
    return *this;
}

// Prints the name of the file
ostream& operator<<(ostream& out, const FileLineReader& reader) {
    out << "FileLineReader reading " << *reader.fileName;
    return out;
}

// Reads the next line into line. Returns false at the end of the file.
bool FileLineReader::readLineFromFile(string& line) {
    if (getline(*file, line)) {
        // remove the '\r' left at the end of the line by files saved on Windows
        if (!line.empty() && line.back() == '\r') {
            line.pop_back();
        }
        return true;
    }
    return false;
}

// Returns true if the file could be opened
bool FileLineReader::isOpen() const {
    return file->is_open();
}

// FileCommandProcessorAdapter

// Constructor: creates the file line reader for the file
FileCommandProcessorAdapter::FileCommandProcessorAdapter(string fileName) {
    flr = new FileLineReader(fileName);
}

// Copy constructor: copies the commands (base class) and the reader
FileCommandProcessorAdapter::FileCommandProcessorAdapter(const FileCommandProcessorAdapter& other)
    : CommandProcessor(other) {
    flr = new FileLineReader(*other.flr);
}

// Destructor: deletes the reader (the base class deletes the commands)
FileCommandProcessorAdapter::~FileCommandProcessorAdapter() {
    delete flr;
}

// Assignment operator: copies the commands (base class) and the reader
FileCommandProcessorAdapter& FileCommandProcessorAdapter::operator=(const FileCommandProcessorAdapter& other) {
    if (this != &other) {
        CommandProcessor::operator=(other);
        *flr = *other.flr;
    }
    return *this;
}

// Prints the reader and the saved commands
ostream& operator<<(ostream& out, const FileCommandProcessorAdapter& adapter) {
    out << *adapter.flr << endl;
    out << static_cast<const CommandProcessor&>(adapter);
    return out;
}

// Returns true if the command file could be opened
bool FileCommandProcessorAdapter::isFileOpen() const {
    return flr->isOpen();
}

// Reads the next command from the file instead of the console, skipping empty
// lines ("" at the end of the file). This is where the adapter uses the reader.
string FileCommandProcessorAdapter::readCommand() {
    string line;
    while (flr->readLineFromFile(line)) {
        if (line != "") {
            cout << line << endl; // show the command read from the file
            return line;
        }
    }
    return "";
}