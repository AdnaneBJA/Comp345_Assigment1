cmake_minimum_required(VERSION 3.10)
project(Comp345_Assignment1 CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(MapDriver
        part1/Map.cpp
        part1/Map.h
        part1/MapDriver.cpp
)

# Lets MapDriver find part1/maps/ no matter which directory it is run from.
target_compile_definitions(MapDriver PRIVATE MAPS_DIR="${CMAKE_CURRENT_SOURCE_DIR}/part1/maps/")


add_executable(CardsDriver
        part1/Cards.cpp
        part1/Cards.h
        part1/CardsDriver.cpp
        part1/Orders.cpp
        part1/Orders.h
)

add_executable(OrdersDriver
        part1/Orders.cpp
        part1/Orders.h
        part1/OrdersDriver.cpp
)


add_executable(MainDriver
        main.cpp)