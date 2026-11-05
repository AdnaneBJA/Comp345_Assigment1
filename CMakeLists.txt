cmake_minimum_required(VERSION 3.10)
project(Comp345_Assignment1 CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(MapDriver
        part2/Map.cpp
        part2/Map.h
        part2/MapDriver.cpp
)

# Lets MapDriver find part2/maps/ no matter which directory it is run from.
target_compile_definitions(MapDriver PRIVATE MAPS_DIR="${CMAKE_CURRENT_SOURCE_DIR}/part2/maps/")


add_executable(CardsDriver
        part2/Cards.cpp
        part2/Cards.h
        part2/CardsDriver.cpp
        part2/Orders.cpp
        part2/Orders.h
        part2/Player.cpp
        part2/Player.h
        part2/Map.cpp
        part2/Map.h
)

add_executable(OrdersDriver
        part2/Orders.cpp
        part2/Orders.h
        part2/OrdersDriver.cpp
)

add_executable(PlayerDriver
        part2/Player.cpp
        part2/Player.h
        part2/PlayerDriver.cpp
        part2/Map.cpp
        part2/Map.h
        part2/Cards.cpp
        part2/Cards.h
        part2/Orders.cpp
        part2/Orders.h
)

add_executable(GameEngineDriver
        part2/GameEngine.cpp
        part2/GameEngine.h
        part2/GameEngineDriver.cpp
)

add_executable(MainDriver
        main.cpp)

# Assignment 2, Part 1. Run with no option (uses part2/commands.txt),
# with -console, or with -file <filename>
add_executable(CommandProcessingDriver
        part2/CommandProcessing.cpp
        part2/CommandProcessing.h
        part2/CommandProcessingDriver.cpp
        part2/GameEngine.cpp
        part2/GameEngine.h
)
target_compile_definitions(CommandProcessingDriver PRIVATE COMMANDS_FILE="${CMAKE_CURRENT_SOURCE_DIR}/part2/Commands.txt")