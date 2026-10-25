#include "GameEngine.h"

// Default constructor
GameEngine::GameEngine() : currentState(State::Start) {}

// Copy constructor
GameEngine::GameEngine(const GameEngine& other)
    : currentState(other.currentState) {}

// Assignment opperator
GameEngine& GameEngine::operator=(const GameEngine& other) {
    if (this != &other) {
        currentState = other.currentState;
    }
    return *this;
}

// Destructor
GameEngine::~GameEngine() = default;

// Return current state as enum value
GameEngine::State GameEngine::getState() const {
    return currentState;
}
// Convert each state into displayable text
std::string GameEngine::stateName(State state) {
    switch (state) {
    case State::Start: return "start";
    case State::MapLoaded: return "map loaded";
    case State::MapValidated: return "map validated";
    case State::PlayersAdded: return "players added";
    case State::AssignReinforcement: return "assign reinforcement";
    case State::IssueOrders: return "issue orders";
    case State::ExecuteOrders: return "execute orders";
    case State::Win: return "win";
    case State::End: return "end";
    }
    return "unknown";
}
// Get readable name of state
std::string GameEngine::getStateName() const {
    return stateName(currentState);
}

// Implements the labeled edges in the Assignment 1 diagram
// No actual map loading or creations yet
bool GameEngine::nextState(const std::string& command, State& result) const {
    switch (currentState) {
    case State::Start:
        if (command == "loadmap") { result = State::MapLoaded; return true; }
        break;
    case State::MapLoaded:
        if (command == "loadmap") { result = State::MapLoaded; return true; }
        if (command == "validatemap") { result = State::MapValidated; return true; }
        break;
    case State::MapValidated:
        if (command == "addplayer") { result = State::PlayersAdded; return true; }
        break;
    case State::PlayersAdded:
        if (command == "addplayer") { result = State::PlayersAdded; return true; }
        if (command == "assigncountries") { result = State::AssignReinforcement; return true; }
        break;
    case State::AssignReinforcement:
        if (command == "issueorder") { result = State::IssueOrders; return true; }
        break;
    case State::IssueOrders:
        if (command == "issueorder") { result = State::IssueOrders; return true; }
        if (command == "endissueorders") { result = State::ExecuteOrders; return true; }
        break;
    case State::ExecuteOrders:
        if (command == "execorder") { result = State::ExecuteOrders; return true; }
        if (command == "endexecorders") { result = State::AssignReinforcement; return true; }
        if (command == "win") { result = State::Win; return true; }
        break;
    case State::Win:
        if (command == "play") { result = State::Start; return true; }
        if (command == "end") { result = State::End; return true; }
        break;
    case State::End:
        break;
    }
    return false;
}

// Accepts valid commands to update the state and reject invalid commands then print the result, does not change the current state
bool GameEngine::processCommand(const std::string& command) {
    State destination = currentState;
    if (!nextState(command, destination)) {
        std::cout << "Invalid command '" << command
                  << "' in state '" << getStateName() << "'. State unchanged.\n";
        return false;
    }

    const std::string previous = getStateName();
    currentState = destination;
    std::cout << "Command accepted: " << command << "\n"
              << "Transition: " << previous << " -> " << getStateName() << "\n";
    return true;
}


bool GameEngine::isFinished() const {
    return currentState == State::End;
}

// Print the current state of the engine
std::ostream& operator<<(std::ostream& out, const GameEngine& engine) {
    out << "GameEngine state: " << engine.getStateName();
    return out;
}
