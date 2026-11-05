//
// Part 2 driver: creates players that own territories of a real Map, a Hand of
// cards drawn from a Deck and an OrdersList, then demonstrates toDefend(),
// toAttack(), issueOrder(), the copy constructor and the assignment operator.
//

#include <iostream>
#include "Player.h"

// Creates a territory with the given id, name and armies and adds it to the map
// (the map owns it and deletes it).
Territory* addTerritory(Map& map, Continent* continent, int id, std::string name, int armies) {
	Territory* terr = new Territory();
	terr->setTerritoryId(id);
	terr->setTerritoryName(name);
	terr->setContinentId(continent->getContinentId());
	terr->setContinent(continent);
	terr->setArmies(armies);
	continent->addTerritory(terr);
	map.addTerritory(terr);
	return terr;
}

// Adds an adjacency in both directions between two territories.
void connect(Territory* a, Territory* b) {
	a->addNeighbor(b);
	b->addNeighbor(a);
}

// Runs the Player demonstration.
int main() {

	// a small map: France - Spain - Portugal, France - Italy
	Map map;
	Continent* europe = new Continent();
	europe->setContinentId(1);
	europe->setName("Europe");
	map.addContinent(europe);

	Territory* france = addTerritory(map, europe, 1, "France", 6);
	Territory* spain = addTerritory(map, europe, 2, "Spain", 1);
	Territory* portugal = addTerritory(map, europe, 3, "Portugal", 7);
	Territory* italy = addTerritory(map, europe, 4, "Italy", 0);

	connect(france, spain);
	connect(france, italy);
	connect(spain, portugal);

	Deck deck;

	std::cout << "=== 1. Player one owns Spain and Portugal ===" << std::endl;
	Player p1("Alice");
	p1.addTerritory(spain);
	p1.addTerritory(portugal);
	deck.draw(p1.getHand());
	deck.draw(p1.getHand());
	std::cout << p1 << std::endl;

	std::cout << "=== 2. Player two owns France and Italy ===" << std::endl;
	Player p2("Bob");
	p2.addTerritory(france);
	p2.addTerritory(italy);
	deck.draw(p2.getHand());
	std::cout << p2 << std::endl;

	std::cout << "=== 3. toDefend() and toAttack() for player one ===" << std::endl;
	std::cout << "Territories to defend (less than 3 armies):" << std::endl;
	Player::printTerritories(p1.toDefend());
	std::cout << "Territories to attack (enemy neighbours):" << std::endl;
	Player::printTerritories(p1.toAttack());
	std::cout << std::endl;

	std::cout << "=== 4. issueOrder() adds orders to player one's list ===" << std::endl;
	p1.issueOrder("deploy");
	p1.issueOrder("advance");
	p1.issueOrder("bomb");
	p1.issueOrder("blockade");
	p1.issueOrder("airlift");
	p1.issueOrder("negotiate");
	p1.issueOrder("surrender");
	std::cout << "Orders of player one:" << std::endl << *p1.getOrders() << std::endl;

	std::cout << "=== 5. Copy constructor (deep copy of hand and orders) ===" << std::endl;
	Player pCopy(p1);
	pCopy.getOrders()->remove(0);
	std::cout << "Copy after removing its first order:" << std::endl << pCopy << std::endl;
	std::cout << "Player one is unchanged:" << std::endl << p1 << std::endl;

	std::cout << "=== 6. Assignment operator ===" << std::endl;
	Player p3;
	p3 = p2;
	std::cout << "Assigned player:" << std::endl << p3 << std::endl;

	// the map deletes the territories and continent, each player deletes its
	// own hand and orders, and the deck deletes the cards left in it
	return 0;
}
