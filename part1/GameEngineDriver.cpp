#include "GameEngine.h"
#include <iostream>
#include <string>

// Demonstrating the Game Engine states with some console commands
int main() {
    // Create the engine
    GameEngine engine;

    std::cout << "--- COMP 345 Warzone Game Engine ---\n";
    std::cout << "Enter commands from the assignment's state diagram.\n";
    std::cout << "Commands: loadmap, validatemap, addplayer, assigncountries,\n"
              << "          issueorder, endissueorders, execorder,\n"
              << "          endexecorders, win, play, end\n";
    std::cout << "Type 'status' to display the state or 'help' to see commands.\n";
    std::cout << "Type 'quit' to stop the driver without a game transition.\n\n";

    // Store commmand by the user
    std::string command;

    // Asking for commands with a loop until the engine reaches the End state
    while (!engine.isFinished()) {

        std::cout << "[" << engine.getStateName() << "] > ";
        if (!std::getline(std::cin, command)) {
            break;
        }
        if (command == "quit") {
            std::cout << "Driver stopped.\n";
            break;
        }
        if (command == "status") {
            std::cout << engine << "\n";
            continue;
        }
        if (command == "help") {
            std::cout << "Commands: loadmap, validatemap, addplayer, assigncountries,\n"
                      << "issueorder, endissueorders, execorder, endexecorders,\n"
                      << "win, play, end\n";
            continue;
        }
        engine.processCommand(command);
    }

    // Confirming that the engine reached the End
    if (engine.isFinished()) {
        std::cout << "Game ended.\n";
    }
    return 0;
}
