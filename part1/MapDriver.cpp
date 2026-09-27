//
// Created by Adnane Bejja on 2026-09-25.
//
// Part 1 driver. Reads a set of Domination map files, creates a Map object for
// each valid file and rejects the invalid ones, then demonstrates the three
// Map::validate() checks:
//   1) the map is a connected graph
//   2) continents are connected subgraphs
//   3) each territory belongs to one and only one continent
//

#include <iostream>
#include <string>
#include <vector>

#include "Map.h"

// Folder holding the .map files. CMake sets it to the absolute path of part1/maps/
// so the driver works from any working directory; it can also be passed as the
// first command-line argument.
#ifndef MAPS_DIR
#define MAPS_DIR "part1/maps/"
#endif

// One map file to test and whether it is expected to be accepted.
struct MapTestCase {
    std::string file;
    std::string description;
    bool expected_valid;
};

// Prints a horizontal separator line.
void printSeparator() {
    std::cout << "------------------------------------------------------------------------" << std::endl;
}

// Loads one map file and validates it. Returns true if the file produced a valid
// Map, false if the loader rejected it or validate() failed. The Map is deleted
// before returning.
bool testMapFile(MapLoader& loader, const std::string& maps_dir, const MapTestCase& test) {
    printSeparator();
    std::cout << "FILE:     " << test.file << std::endl;
    std::cout << "EXPECTED: " << (test.expected_valid ? "valid" : "invalid") << " (" << test.description << ")" << std::endl;

    Map* map = loader.load_map(maps_dir + test.file);

    if (map == nullptr) {
        std::cout << "RESULT:   REJECTED by the map loader" << std::endl;
        return false;
    }

    std::cout << "Loaded:   " << map->getContinents().size() << " continents, " << map->getTerritories().size() << " territories" << std::endl;

    const bool valid = map->validate();

    if (valid) {
        std::cout << "Checks:   1) connected graph  2) connected continents  3) one continent per territory -> all passed" << std::endl;
        std::cout << "RESULT:   VALID, Map object created" << std::endl;
    }
    else {
        std::cout << "RESULT:   REJECTED by Map::validate()" << std::endl;
    }

    delete map;
    return valid;
}

// Check 3 cannot be reached through a map file, because the loader already rejects a
// territory whose continent does not exist. This builds such a Map by hand to show
// that validate() catches it too.
void demonstrateCheck3() {
    printSeparator();
    std::cout << "HAND-BUILT MAP: territory 2 points to continent 7, which does not exist" << std::endl;
    std::cout << "EXPECTED: invalid (validate check 3)" << std::endl;

    Map* map = new Map();

    auto* continent = new Continent();
    continent->setContinentId(1);
    continent->setName("Only_Continent");
    map->addContinent(continent);

    auto* first = new Territory();
    first->setTerritoryId(1);
    first->setTerritoryName("Inside");
    first->setContinentId(1);
    first->setContinent(continent);
    continent->addTerritory(first);

    auto* second = new Territory();
    second->setTerritoryId(2);
    second->setTerritoryName("Orphan");
    second->setContinentId(7);

    first->addNeighbor(second);
    second->addNeighbor(first);

    map->addTerritory(first);
    map->addTerritory(second);

    if (map->validate()) {
        std::cout << "RESULT:   VALID (unexpected)" << std::endl;
    }
    else {
        std::cout << "RESULT:   REJECTED by Map::validate()" << std::endl;
    }

    delete map;
}

// Runs every test case and prints a summary of which files were accepted and rejected.
int main(int argc, char* argv[]) {
    std::string maps_dir = MAPS_DIR;
    if (argc > 1) {
        maps_dir = argv[1];
        if (maps_dir.back() != '/' && maps_dir.back() != '\\') {
            maps_dir += '/';
        }
    }

    const std::vector<MapTestCase> tests = {
        // Valid Domination maps
        {"risk.map",                              "classic Risk map",                        true},
        {"canada.map",                            "Canada map",                              true},
        {"bigeurope.map",                         "large Europe map",                        true},

        // Invalid graphs: the file parses, but validate() rejects the map
        {"invalid/disconnected_map.map",          "check 1: map is not connected",           false},
        {"invalid/disconnected_continent.map",    "check 2: continent is not connected",     false},
        {"invalid/empty_continent.map",           "check 2: continent has no territories",   false},

        // Invalid files: the loader rejects them
        {"invalid/unknown_continent.map",         "territory in a continent that does not exist", false},
        {"invalid/duplicate_territory_id.map",    "two territories share an id",             false},
        {"invalid/unknown_border_neighbor.map",   "border to a territory that does not exist", false},
        {"invalid/unknown_border_source.map",     "border from a territory that does not exist", false},
        {"invalid/malformed_country_line.map",    "word instead of a number",                false},
        {"invalid/malformed_continent_line.map",  "missing field",                           false},
        {"invalid/malformed_border_line.map",     "junk after the neighbor ids",             false},
        {"invalid/missing_borders_section.map",   "required section missing",                false},
        {"invalid/not_a_map.txt",                 "plain text file",                         false},
        {"invalid/empty.map",                     "empty file",                              false},
        {"invalid/does_not_exist.map",            "file does not exist",                     false},
    };

    std::cout << "PART 1: MAP DRIVER" << std::endl;
    std::cout << "Reading map files from: " << maps_dir << std::endl;

    MapLoader loader;
    std::vector<bool> results;

    for (const MapTestCase& test: tests) {
        results.push_back(testMapFile(loader, maps_dir, test));
    }

    demonstrateCheck3();

    // Summary
    printSeparator();
    std::cout << "SUMMARY" << std::endl;

    int accepted = 0;
    int unexpected = 0;

    for (std::size_t i = 0; i < tests.size(); i++) {
        const bool matches = results[i] == tests[i].expected_valid;

        std::cout << (results[i] ? "  VALID     " : "  REJECTED  ") << tests[i].file;
        if (!matches) {
            std::cout << "   <-- UNEXPECTED";
            unexpected++;
        }
        std::cout << std::endl;

        if (results[i]) {
            accepted++;
        }
    }

    std::cout << std::endl;
    std::cout << accepted << " valid, " << tests.size() - accepted << " rejected, " << unexpected << " unexpected results" << std::endl;

    return unexpected == 0 ? 0 : 1;
}
