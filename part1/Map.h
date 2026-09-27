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
// player and knows its adjacent territories (the edges of the graph). The Map owns
// every Territory; a Territory never deletes the objects it points to.
class Territory {
    int territory_id = 0;
    std::string territory_name = "DEFAULT_TERRITORY";
    int continent_id = 0;
    Continent* continent = nullptr;
    int x = 0;
    int y = 0;
    int armies = 0;

    Player* player = nullptr;

    std::vector<Territory*> neighbors;

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
// every territory of a continent gives its owner the control bonus. The Map owns
// every Continent; a Continent never deletes its territories.
class Continent {
    int continent_id = 0;
    int control_bonus = 0;
    std::string name = "CONTINENT";
    std::string color = "DEFAULT";
    std::vector<Territory*> territories;

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
// adjacencies between them, grouped into continents. The Map owns (and deletes)
// all of its territories and continents.
class Map {
    std::vector<Territory*> territories;
    std::vector<Continent*> continents;

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
