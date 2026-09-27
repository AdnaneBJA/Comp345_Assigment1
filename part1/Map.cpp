//
// Created by Adnane Bejja on 2026-09-25.
//

#include "Map.h"

#include <fstream>
#include <iostream>
#include <map>
#include <set>
#include <sstream>
#include <utility>

// =============================================================================
// Territory
// =============================================================================

// Stream insertion: prints the territory's id, name, continent id and coordinates.
std::ostream& operator<<(std::ostream& os, const Territory& territory) {
    os << "Territory ID: " << territory.territory_id << ", Name: " << territory.territory_name << ", Continent ID: " << territory.continent_id << ", X: " << territory.x << ", Y: " << territory.y << ", Armies: " << territory.armies;
    return os;
}

// Default constructor: all fields keep their in-class default values.
Territory::Territory() = default;

// Destructor: deletes nothing. The continent, player and neighbors are owned by
// the Map (or the game), so deleting them here would cause double deletes.
Territory::~Territory() = default;

// Copy constructor: shallow-copies continent, player and neighbors because the
// Map owns those objects, not the Territory.
Territory::Territory(const Territory& obj)
     : territory_id(obj.territory_id),
       territory_name(obj.territory_name),
       continent_id(obj.continent_id),
       continent(obj.continent),
       x(obj.x),
       y(obj.y),
       player(obj.player),
       neighbors(obj.neighbors) {} // copies the pointers, not the territories

// Assignment operator: shallow-copies every field, like the copy constructor.
Territory &Territory::operator=(const Territory& other) {
    if (this != &other) {
        territory_id = other.territory_id;
        territory_name = other.territory_name;
        continent_id = other.continent_id;
        continent = other.continent;
        x = other.x;
        y = other.y;
        player = other.player;
        neighbors = other.neighbors;
    }

    return *this;
}

// Sets the territory's id, as read from the [countries] section.
void Territory::setTerritoryId(const int n) {
    territory_id = n;
}

// Sets the territory's name.
void Territory::setTerritoryName(std::string n) {
    territory_name = std::move(n);
}

// Sets the id of the continent this territory belongs to.
void Territory::setContinentId(const int n) {
    continent_id = n;
}

// Sets the x coordinate used to draw the territory.
void Territory::setX(const int newX) {
    x = newX;
}

// Sets the y coordinate used to draw the territory.
void Territory::setY(const int newY) {
    y = newY;
}

// Sets the continent this territory belongs to.
void Territory::setContinent(Continent *c) {
    continent = c;
}

// Returns the continent this territory belongs to (nullptr if none).
Continent* Territory::getContinent() const {
    return continent;
}

// Returns the territory's id.
int Territory::getId() const {
    return territory_id;
}

// Returns the id of the continent this territory belongs to.
int Territory::getContinentId() const {
    return continent_id;
}

// Adds an edge from this territory to an adjacent territory.
void Territory::addNeighbor(Territory *territory) {
    neighbors.push_back(territory);
}

// Prints every adjacent territory (debugging helper).
void Territory::printNeighbors() {
    std::cout << "PRINTING NEIGHBORS FOR: " << territory_name << std::endl;
    for (Territory* territory: neighbors) {
        std::cout << *territory << std::endl;
    }
    std::cout << "END OF NEIGHBORS" << std::endl;
}

// Returns the adjacent territories.
std::vector<Territory*> Territory::getNeighbors() {
    return neighbors;
}

// Replaces the adjacent territories (used by the Map deep copy).
void Territory::setNeighbors(std::vector<Territory*> n) {
    neighbors = std::move(n);
}

// =============================================================================
// Continent
// =============================================================================

// Stream insertion: prints the continent's id, name, control bonus and color.
std::ostream& operator<<(std::ostream& os, const Continent& continent) {
    os <<  "ID: " << continent.continent_id <<", Continent Name: " << continent.name << ", Control Bonus: " << continent.control_bonus << ", Color: " << continent.color;
    return os;
}

// Default constructor: all fields keep their in-class default values.
Continent::Continent() = default;

// Destructor: deletes nothing. The territories are owned by the Map.
Continent::~Continent() = default;

// Copy constructor: shallow-copies the territory pointers because the Map
// owns the territories, not the Continent.
Continent::Continent(const Continent& obj)
    : continent_id(obj.continent_id),
      control_bonus(obj.control_bonus),
      name(obj.name),
      color(obj.color),
      territories(obj.territories) {}

// Assignment operator: shallow-copies the territory pointers, like the copy constructor.
Continent& Continent::operator=(const Continent& other) {
    if (this != &other) {
        continent_id = other.continent_id;
        control_bonus = other.control_bonus;
        name = other.name;
        color = other.color;
        territories = other.territories;
    }

    return *this;
}

// Sets the continent's name.
void Continent::setName(std::string n) {
    name = std::move(n);
}

// Sets the bonus armies given to the player who controls the whole continent.
void Continent::setControlBonus(const int n) {
    control_bonus = n;
}

// Sets the color used to draw the continent.
void Continent::setColor(std::string c) {
    color = std::move(c);
}

// Sets the continent's id (its 1-based position in the [continents] section).
void Continent::setContinentId(const int n) {
    continent_id = n;
}

// Returns the continent's id.
int Continent::getContinentId() const {
    return continent_id;
}

// Returns the continent's name.
std::string Continent::getName() {
    return name;
}

// Adds a territory to this continent.
void Continent::addTerritory(Territory *territory) {
    territories.push_back(territory);
}

// Returns the territories of this continent.
std::vector<Territory *> Continent::getTerritories() {
    return territories;
}

// Replaces the territories of this continent (used by the Map deep copy).
void Continent::setTerritories(std::vector<Territory*> t) {
    territories = std::move(t);
}

// =============================================================================
// Map
// =============================================================================

// Stream insertion: prints the map size, then each continent followed by its territories.
std::ostream& operator<<(std::ostream& os, const Map& map) {
    os << "Map: " << map.continents.size() << " continents, " << map.territories.size() << " territories";
    for (Continent* continent: map.continents) {
        os << "\n  " << *continent;
        for (const Territory* territory: continent->getTerritories()) {
            os << "\n    " << *territory;
        }
    }
    return os;
}

// Default constructor: creates an empty map.
Map::Map() = default;

// Destructor: the Map owns its territories and continents, so it deletes them.
Map::~Map() {
    clear();
}

// Copy constructor: deep copy of another map.
Map::Map(const Map& obj) {
    copyFrom(obj);
}

// Assignment operator: frees this map's territories and continents, then deep-copies the other map.
Map& Map::operator=(const Map& other) {
    if (this != &other) {
        clear();
        copyFrom(other);
    }

    return *this;
}

// Deletes every territory and continent this map owns and empties both lists.
void Map::clear() {
    for (const Territory* territory: territories) {
        delete territory;
    }
    for (const Continent* continent: continents) {
        delete continent;
    }
    territories.clear();
    continents.clear();
}

// Deep copy. The Map owns its territories and continents, so each one is
// duplicated, then every neighbor/continent/territory pointer in the copies is
// redirected to the new objects instead of the originals.
void Map::copyFrom(const Map& obj) {
    std::map<const Continent*, Continent*> continent_copies;
    std::map<const Territory*, Territory*> territory_copies;

    for (Continent* continent: obj.continents) {
        auto* copy = new Continent(*continent);
        continent_copies[continent] = copy;
        continents.push_back(copy);
    }

    for (Territory* territory: obj.territories) {
        auto* copy = new Territory(*territory);
        territory_copies[territory] = copy;
        territories.push_back(copy);
    }

    for (Territory* copy: territories) {
        std::vector<Territory*> new_neighbors;
        for (Territory* neighbor: copy->getNeighbors()) {
            new_neighbors.push_back(territory_copies[neighbor]);
        }
        copy->setNeighbors(new_neighbors);
        copy->setContinent(continent_copies[copy->getContinent()]);
    }

    for (Continent* copy: continents) {
        std::vector<Territory*> new_territories;
        for (Territory* territory: copy->getTerritories()) {
            new_territories.push_back(territory_copies[territory]);
        }
        copy->setTerritories(new_territories);
    }
}

// Adds a continent to the map. The map takes ownership of it.
void Map::addContinent(Continent *continent) {
    continents.push_back(continent);
}

// Adds a territory to the map. The map takes ownership of it.
void Map::addTerritory(Territory *territory) {
    territories.push_back(territory);
}

// Checks that 1) the map is a connected graph, 2) every continent is a connected
// subgraph and 3) every territory belongs to one and only one continent.
// Prints which check failed and returns false on the first failure.
bool Map::validate() {
    // 1. The whole map is connected: a DFS from any territory reaches all of them.
    if (territories.empty()) {
        std::cout << "CHECK 1 FAILED: the map has no territories" << std::endl;
        return false;
    }

    const std::size_t number_of_territories = territories.size();

    Territory* starting_territory = territories[0];
    std::set<Territory*> visited;

    dfs(starting_territory, visited);

    if (number_of_territories != visited.size()) {
        std::cout << "CHECK 1 FAILED: the map is not connected (reached " << visited.size() << " of " << number_of_territories << " territories)" << std::endl;
        return false;
    }

    // 2. Each continent is connected: a DFS that stays inside the continent reaches all of its territories.
    for (Continent* continent: continents) {
        const std::size_t expected_size_result = continent->getTerritories().size();

        if (continent->getTerritories().empty()) {
            std::cout << "CHECK 2 FAILED: continent " << continent->getName() << " has no territories" << std::endl;
            return false;
        }

        Territory* starting_source = continent->getTerritories()[0];

        std::set<Territory*> continent_visited;

        dfs(starting_source, continent_visited, continent->getContinentId());

        if (expected_size_result != continent_visited.size()) {
            std::cout << "CHECK 2 FAILED: continent " << continent->getName() << " is not a connected subgraph" << std::endl;
            return false;
        }
    }

    // 3. Each territory belongs to exactly one continent.
    for (const Territory* territory: territories) {
        int count = 0;

        for (const Continent* continent: continents) {
            if (territory->getContinentId() == continent->getContinentId()) {
                count += 1;
            }
        }
        if (count != 1) {
            std::cout << "CHECK 3 FAILED: territory " << territory->getId() << " belongs to " << count << " continents" << std::endl;
            return false;
        }
    }

    return true;
}

// Prints every continent of the map.
void Map::display_continents() {
    for (const Continent* continent: continents) {
        std::cout << *continent << std::endl;
    }
}

// Returns the territory with the given id, or nullptr if there is none.
Territory* Map::get_territory_by_id(const int territory_id) const {
    for (Territory* territory: territories) {
        if (territory_id == territory->getId()) {
            return territory;
        }
    }
    return nullptr;
}

// Returns the continents of the map.
std::vector<Continent*> Map::getContinents() {
    return continents;
}

// Returns the territories of the map.
std::vector<Territory*> Map::getTerritories() {
    return territories;
}

// Depth-first search that only follows neighbors in the given continent.
// Every territory reached is added to visited.
void Map::dfs(Territory* territory, std::set<Territory*> &visited, const int continent_id) {
    visited.insert(territory);

    for (Territory* neighbor: territory->getNeighbors()) {
        if (neighbor->getContinentId() == continent_id && visited.find(neighbor) == visited.end()) {
            dfs(neighbor, visited, continent_id);
        }
    }
}

// Depth-first search over the whole map. Every territory reached is added to visited.
void Map::dfs(Territory* territory, std::set<Territory*> &visited) {
    visited.insert(territory);

    for (Territory* neighbor: territory->getNeighbors()) {
        if (visited.find(neighbor) == visited.end()) {
            dfs(neighbor, visited);
        }
    }
}

// =============================================================================
// MapLoader
// =============================================================================

// Stream insertion: MapLoader has no state, so it only prints its type.
std::ostream& operator<<(std::ostream& os, const MapLoader& loader) {
    os << "MapLoader (reads Domination .map files)";
    return os;
}

// Default constructor: MapLoader has no state.
MapLoader::MapLoader() = default;

// Destructor: MapLoader has no state. Maps it returns are owned by the caller.
MapLoader::~MapLoader() = default;

// Copy constructor: MapLoader has no state, so there is nothing to copy.
MapLoader::MapLoader(const MapLoader& obj) {}

// Assignment operator: MapLoader has no state, so there is nothing to copy.
MapLoader& MapLoader::operator=(const MapLoader& other) {
    return *this;
}

// Reads a Domination .map file and builds a Map from its [continents], [countries]
// and [borders] sections. Returns nullptr (after printing the reason) if the file
// cannot be opened or is not a valid map file. The caller owns the returned Map.
Map* MapLoader::load_map(const std::string &filepath) {
    int next_continent_id = 1;
    // [files] is optional; the other three sections are required.
    bool saw_continents = false;
    bool saw_countries = false;
    bool saw_borders = false;

    auto* map = new Map();

    std::string myText;

    std::ifstream MyReadFile(filepath);
    std::set<int> seen_id;

    if (!MyReadFile.is_open()) {
        std::cout << "COULD NOT OPEN FILE: " << filepath << std::endl;
        delete map;
        return nullptr;
    }

    std::string current_section = "NONE";
    while (std::getline(MyReadFile, myText)) {
        if (myText.find_first_not_of(" \t\r") == std::string::npos) {
            continue;
        }

        // Skip comment lines.
        if (myText[0] == ';') {
            continue;
        }


        if (myText == "[files]") {
            current_section = "FILES";
            continue;
        }

        if (myText == "[continents]") {
            current_section = "CONTINENTS";
            saw_continents = true;
            continue;
        }

        if (myText == "[countries]") {
            current_section = "COUNTRIES";
            saw_countries = true;
            continue;
        }

        if (myText == "[borders]") {
            current_section = "BORDERS";
            saw_borders = true;
            continue;
        }



        std::stringstream ss(myText);


        if (current_section == "CONTINENTS") {
            std::string color;
            int control_bonus;
            std::string name;

            if (ss >> name >> control_bonus >> color) {
                auto* continent = new Continent();

                continent->setContinentId(next_continent_id);
                continent->setName(name);
                continent->setControlBonus(control_bonus);
                continent->setColor(color);

                map->addContinent(continent);

                next_continent_id += 1;
            }
            else {
                std::cout << "MALFORMED CONTINENT LINE: " << myText << std::endl;
                delete map;
                return nullptr;
            }

        }
        else if (current_section == "COUNTRIES") {
            int territory_id;
            std::string territory_name;
            int continent_id;
            int x;
            int y;





            if (ss >> territory_id >> territory_name >> continent_id >> x >> y) {
                if (seen_id.find(territory_id) != seen_id.end()) {
                    std::cout << "DUPLICATE TERRITORY ID = " << territory_id << " INSIDE MAP FILE, INVALID INPUT" << std::endl;
                    delete map;
                    return nullptr;
                }

                seen_id.insert(territory_id);

                auto* territory = new Territory();

                territory->setTerritoryId(territory_id);
                territory->setTerritoryName(territory_name);
                territory->setContinentId(continent_id);
                territory->setX(x);
                territory->setY(y);

                map->addTerritory(territory);

                bool found_matching_continent = false;


                for (Continent* continent: map->getContinents()) {
                    if (continent_id == continent->getContinentId()) {
                        continent->addTerritory(territory);
                        territory->setContinent(continent);
                        found_matching_continent = true;
                        break;
                    }
                }

                if (!found_matching_continent) {
                    std::cout << "THE CONTINENT ID: " << continent_id << " DOES NOT EXIST !" << std::endl;
                    delete map;
                    return nullptr;
                }

            }
            else {
                std::cout << "MALFORMED COUNTRY LINE: " << myText << std::endl;
                delete map;
                return nullptr;
            }
        }
        else if (current_section == "BORDERS") {
            int source_territory_id;

            if (!(ss >> source_territory_id)) {
                std::cout << "MALFORMED BORDER LINE: " << myText << std::endl;
                delete map;
                return nullptr;
            }

            Territory* source = map->get_territory_by_id(source_territory_id);

            if (source == nullptr) {
                std::cout << "UNKNOWN TERRITORY ID " << source_territory_id << " IN BORDERS, INVALID INPUT" << std::endl;
                delete map;
                return nullptr;
            }

            int neighbor_id;

            while (ss >> neighbor_id) {
                Territory* neighbor = map->get_territory_by_id(neighbor_id);

                if (neighbor == nullptr) {
                    std::cout << "UNKNOWN NEIGHBOR ID " << neighbor_id << " FOR TERRITORY " << source_territory_id << ", INVALID INPUT" << std::endl;
                    delete map;
                    return nullptr;
                }

                source->addNeighbor(neighbor);
            }

            // The loop stops early on anything that is not a number (e.g. "1 2 abc").
            if (!ss.eof()) {
                std::cout << "MALFORMED BORDER LINE: " << myText << std::endl;
                delete map;
                return nullptr;
            }
        }
    }


    if (!saw_continents || !saw_countries || !saw_borders) {
        delete map;

        std::cout << "MALFORMED MAP WAS PASSED, INVALID INPUT" << std::endl;

        return nullptr;
    }


    return map;
}
