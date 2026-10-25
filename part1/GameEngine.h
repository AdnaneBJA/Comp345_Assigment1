#ifndef GAMEENGINE_H
#define GAMEENGINE_H
#include <iostream>
#include <string>

// GameEngine class implementation
class GameEngine {
public:
    // All states that are possible
    enum class State {
        Start,
        MapLoaded,
        MapValidated,
        PlayersAdded,
        AssignReinforcement,
        IssueOrders,
        ExecuteOrders,
        Win,
        End
    };

    // methods
    GameEngine();
    GameEngine(const GameEngine& other);
    GameEngine& operator=(const GameEngine& other);
    ~GameEngine();

    State getState() const;
    std::string getStateName() const;
    bool processCommand(const std::string& command);
    bool isFinished() const;
    // print the current state
    friend std::ostream& operator<<(std::ostream& out, const GameEngine& engine);

private:
    State currentState;
    static std::string stateName(State state);
    // store the next state in result
    bool nextState(const std::string& command, State& result) const;
};

#endif
