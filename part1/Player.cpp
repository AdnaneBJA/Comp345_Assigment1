#include "Player.h"

#include <algorithm>
#include <iostream>

// default constructor: a player with a default name, no territories, an empty
// hand and an empty list of orders
Player::Player()
	: name(new std::string("Unnamed player")),
	  territoriesOfPlayer(new std::vector<Territory*>()),
	  hand(new Hand()),
	  ordersOfPlayer(new OrdersList()) {}

// constructor: a player with the given name, no territories, an empty hand and
// an empty list of orders
Player::Player(std::string n)
	: name(new std::string(n)),
	  territoriesOfPlayer(new std::vector<Territory*>()),
	  hand(new Hand()),
	  ordersOfPlayer(new OrdersList()) {}

// copy constructor: deep-copies the name, the hand and the orders (Hand and
// OrdersList copy their cards and orders). The territory pointers are copied
// as-is because the Map owns the territories.
Player::Player(const Player& p)
	: name(new std::string(*p.name)),
	  territoriesOfPlayer(new std::vector<Territory*>(*p.territoriesOfPlayer)),
	  hand(new Hand(*p.hand)),
	  ordersOfPlayer(new OrdersList(*p.ordersOfPlayer)) {}

// destructor: deletes what the player owns (name, territory list, hand and
// orders). The territories themselves belong to the Map and are not deleted.
Player::~Player() {

	delete name;
	delete territoriesOfPlayer;
	delete hand;
	delete ordersOfPlayer;

	name = nullptr;
	territoriesOfPlayer = nullptr;
	hand = nullptr;
	ordersOfPlayer = nullptr;
}

// assignment operator: copies the other player's values into this player's own
// memory, like the copy constructor (Hand and OrdersList do the deep copies)
Player& Player::operator=(const Player& p) {

	if (this != &p) {
		*name = *p.name;
		*territoriesOfPlayer = *p.territoriesOfPlayer;
		*hand = *p.hand;
		*ordersOfPlayer = *p.ordersOfPlayer;
	}

	return *this;
}

// insertion operator overload: prints the player's name, territories, hand and orders
std::ostream& operator<<(std::ostream& out, const Player& p) {

	out << "Player " << *p.name << std::endl;
	out << "  Territories:";
	for (Territory* terr: *p.territoriesOfPlayer) {
		out << " " << terr->getName() << "(" << terr->getArmies() << ")";
	}
	out << std::endl;
	out << "  " << *p.hand << std::endl;
	out << "  Orders:" << std::endl << *p.ordersOfPlayer;
	return out;
}

// getter of the player's name
std::string Player::getName() const {
	return *name;
}

// getter of the player's territories
std::vector<Territory*> Player::getTerritories() const {
	return *territoriesOfPlayer;
}

// getter of the player's hand of cards
Hand* Player::getHand() const {
	return hand;
}

// getter of the player's list of orders
OrdersList* Player::getOrders() const {
	return ordersOfPlayer;
}

// this method returns a list of territories that need defence. If a given
// player territory has less than 3 armies then it is added to the list
std::vector<Territory*> Player::toDefend() {

	std::vector<Territory*> territoriesToDefend;

	for (Territory* terr: *territoriesOfPlayer) {
		if (terr->getArmies() < 3) {
			territoriesToDefend.push_back(terr);
		}
	}

	return territoriesToDefend;
}

// this method checks the neighbours of each territory belonging to a player.
// If the territory does not belong to the current player, then it is added to
// the territories to be attacked (each territory only once)
std::vector<Territory*> Player::toAttack() {

	std::vector<Territory*> enemyTerritoriesToAttack;
	for (Territory* terr: *territoriesOfPlayer) {
		for (Territory* neighbourTerr: terr->getNeighbors()) {
			bool alreadyAdded = std::find(enemyTerritoriesToAttack.begin(), enemyTerritoriesToAttack.end(), neighbourTerr) != enemyTerritoriesToAttack.end();
			if (neighbourTerr->getPlayer() != this && !alreadyAdded) {
				enemyTerritoriesToAttack.push_back(neighbourTerr);
			}
		}
	}

	return enemyTerritoriesToAttack;
}

// this method creates an Order object of the given type (deploy, advance, bomb,
// blockade, airlift or negotiate) and adds it to the player's list of orders.
// The targets are taken from toDefend() and toAttack(). An unknown type adds nothing.
void Player::issueOrder(std::string orderType) {

	std::vector<Territory*> defend = toDefend();
	std::vector<Territory*> attack = toAttack();

	// territories the orders refer to (empty name when there is none, which makes the order invalid)
	std::string own = territoriesOfPlayer->empty() ? "" : territoriesOfPlayer->front()->getName();
	std::string ownLast = territoriesOfPlayer->empty() ? "" : territoriesOfPlayer->back()->getName();
	std::string toProtect = defend.empty() ? own : defend.front()->getName();
	std::string enemy = attack.empty() ? "" : attack.front()->getName();
	std::string enemyPlayer = "";
	if (!attack.empty() && attack.front()->getPlayer() != nullptr) {
		enemyPlayer = attack.front()->getPlayer()->getName();
	}

	Order* order = nullptr;
	if (orderType == "deploy") {
		order = new Deploy(3, toProtect);
	} else if (orderType == "advance") {
		order = new Advance(2, own, enemy);
	} else if (orderType == "bomb") {
		order = new Bomb(enemy);
	} else if (orderType == "blockade") {
		order = new Blockade(toProtect);
	} else if (orderType == "airlift") {
		order = new Airlift(1, own, ownLast);
	} else if (orderType == "negotiate") {
		order = new Negotiate(enemyPlayer);
	} else {
		std::cout << "Unknown order type: " << orderType << std::endl;
		return;
	}

	ordersOfPlayer->add(order);
}

// this method adds a territory to a player and sets the territory's owner to this player
void Player::addTerritory(Territory* terr) {

	territoriesOfPlayer->push_back(terr);
	terr->setPlayer(this);
}

// print a list of territories with their armies
void Player::printTerritories(const std::vector<Territory*>& inputList) {

	for (Territory* terr: inputList) {
		std::cout << "  " << terr->getName() << " (" << terr->getArmies() << " armies)" << std::endl;
	}
}
