//
// Created by Adnane Bejja on 2026-09-25.
//

#ifndef COMP345_ASSIGNMENT1_MAP_H
#define COMP345_ASSIGNMENT1_MAP_H
#include <iosfwd>
#include <set>
#include <string>
#include <vector>

class Continent;
class Player;

// A node of the map graph. Each territory belongs to one continent, is owned by a
// player and knows its adjacent territories (the edges of the graph). Every data
// member is a pointer. A Territory owns (and deletes) its own values (id, name,
// coordinates, armies, neighbor list), but the Map owns the continents and the
// neighboring territories, so a Territory never deletes those.
class Territory {
    int* territory_id;
    std::string* territory_name;
    int* continent_id;
    Continent* continent;
    int* x;
    int* y;
    int* armies;

    Player* player;

    std::vector<Territory*>* neighbors;

public:
    friend std::ostream& operator<<(std::ostream& os, const Territory& territory);

    Territory();
    ~Territory();
    Territory(const Territory &obj);
    Territory& operator=(const Territory& other);

    void setTerritoryId(int n);
    void setTerritoryName(std::string n);
    void setContinentId(int n);
    void setX(int newX);
    void setY(int newY);
    void setContinent(Continent *c);
    Continent* getContinent() const;
    int getContinentId() const;
    int getId() const;

    void addNeighbor(Territory* territory);
    void printNeighbors();
    std::vector<Territory *> getNeighbors();
    void setNeighbors(std::vector<Territory*> n);
};

// A group of territories that must form a connected subgraph of the map. Holding
// every territory of a continent gives its owner the control bonus. Every data
// member is a pointer. A Continent owns (and deletes) its own values and its
// territory list, but the Map owns the territories themselves.
class Continent {
    int* continent_id;
    int* control_bonus;
    std::string* name;
    std::string* color;
    std::vector<Territory*>* territories;

public:
    friend std::ostream& operator<<(std::ostream& os, const Continent& continent);

    Continent();
    ~Continent();
    Continent(const Continent &obj);
    Continent& operator=(const Continent& other);

    void setName(std::string n);
    void setControlBonus(int n);
    void setColor(std::string c);
    void setContinentId(int n);
    int getContinentId() const;
    std::string getName();

    void addTerritory(Territory* territory);
    std::vector<Territory*> getTerritories();
    void setTerritories(std::vector<Territory*> t);
};

// The game map: a graph whose nodes are territories and whose edges are the
// adjacencies between them, grouped into continents. Every data member is a
// pointer. The Map owns (and deletes) both lists and all of its territories and
// continents.
class Map {
    std::vector<Territory*>* territories;
    std::vector<Continent*>* continents;

    void copyFrom(const Map& other);
    void clear();

public:
    friend std::ostream& operator<<(std::ostream& os, const Map& map);

    Map();
    ~Map();
    Map(const Map &obj);
    Map& operator=(const Map& other);

    void addTerritory(Territory* territory);
    void addContinent(Continent* continent);

    std::vector<Continent*> getContinents();
    std::vector<Territory*> getTerritories();
    Territory* get_territory_by_id(int territory_id) const;

    bool validate();

    void display_continents();
    void dfs(Territory* territory, std::set<Territory*> &visited, int continent_id);
    void dfs(Territory *territory, std::set<Territory *> &visited);
};

// Reads Domination .map files and builds Map objects from them. It accepts any text
// file: invalid input is reported and rejected instead of crashing.
class MapLoader {
public:
    friend std::ostream& operator<<(std::ostream& os, const MapLoader& loader);

    MapLoader();
    ~MapLoader();
    MapLoader(const MapLoader &obj);
    MapLoader& operator=(const MapLoader& other);

    Map* load_map(const std::string &filepath);
};

#endif //COMP345_ASSIGNMENT1_MAP_H
