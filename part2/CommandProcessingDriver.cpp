//
// Part 1 driver. Shows that:
//   1) commands can be read from the console with the CommandProcessor
//   2) commands can be read from a text file with the FileCommandProcessorAdapter
//   3) invalid commands are rejected and valid commands change the game state
//
// Usage:  CommandProcessingDriver -console
//         CommandProcessingDriver -file <filename>
//         CommandProcessingDriver                   (uses COMMANDS_FILE)
//

#include <iostream>
#include <sstream>
#include <string>

#include "CommandProcessing.h"
#include "GameEngine.h"

using namespace std;

// File used when no option is given. CMake sets it to the full path of
// part2/commands.txt so the driver finds it from any folder.
#ifndef COMMANDS_FILE
#define COMMANDS_FILE "Commands.txt"
#endif

// Reads commands until quit or the end of the input. Invalid commands are
// rejected, valid ones change the state of the game engine.
void testCommandProcessor(CommandProcessor* processor) {
    GameEngine engine;

    while (!engine.isFinished()) {
        cout << endl << "[" << engine.getStateName() << "] > ";
        Command* command = processor->getCommand();
        if (command == nullptr) {
            cout << endl << "No more commands." << endl;
            break;
        }

                if (processor->validate(command, &engine)) {
            engine.transition(processor->nextState(command));
            command->saveEffect("Accepted, new state: " + engine.getStateName());
        }
        cout << *command << endl;

        // the play phase is done in Part 3, so the driver goes straight to the
        // win state to be able to test replay and quit
        if (engine.getState() == GameEngine::State::AssignReinforcement) {
            cout << "(play phase skipped, done in Part 3)" << endl;
            engine.transition(GameEngine::State::Win);
        }
    }

    cout << endl << *processor << endl;
}

// Creates the console or the file command processor from the command line option
int main(int argc, char* argv[]) {
    cout << "PART 1: COMMAND PROCESSOR" << endl;
    cout << "Commands: loadmap <mapfile>, validatemap, addplayer <playername>, gamestart, replay, quit" << endl;

    string option = "-file";
    string fileName = COMMANDS_FILE;
    if (argc >= 2) {
        option = argv[1];
    }
    if (argc >= 3) {
        fileName = argv[2];
    }

    CommandProcessor* processor = nullptr;
    if (option == "-console") {
        cout << "Reading commands from the console." << endl;
        processor = new CommandProcessor();
    }
    else if (option == "-file") {
        FileCommandProcessorAdapter* adapter = new FileCommandProcessorAdapter(fileName);
        if (!adapter->isFileOpen()) {
            cout << "Could not open " << fileName << endl;
            delete adapter;
            return 1;
        }
        cout << "Reading commands from the file " << fileName << endl;
        processor = adapter;
    }
    else {
        cout << "Usage: -console or -file <filename>" << endl;
        return 1;
    }

    testCommandProcessor(processor);

    delete processor;
    return 0;
}