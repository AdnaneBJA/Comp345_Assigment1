#include "Player.h"
#include <list>
#include <vector>
#include <string>
#include <iostream>
using namespace std;

// initiallization of static member
// this will be used to keep track of players
int* Player::counterID = new int(1); 

// player constructor
Player::Player() {

	territoriesOfPlayer = new list<Territory*>();
	cardsOfPlayer = new list<Cards>();
	ordersOfPlayer = new list<Order>();
	playerID = new int(*counterID);
	(*counterID)++;
}

// copy constructor
Player::Player(const Player& p) {

	territoriesOfPlayer = new list<Territory*>(*(p.territoriesOfPlayer));
	cardsOfPlayer = new list<Cards>(*(p.cardsOfPlayer));
	ordersOfPlayer = new list<Order>(*(p.ordersOfPlayer));
	playerID = new int(*(p.playerID));
}

//Player destructor
Player::~Player() {

	delete territoriesOfPlayer;
	delete cardsOfPlayer;
	delete ordersOfPlayer;
	delete playerID;

	territoriesOfPlayer = nullptr;
	cardsOfPlayer = nullptr;
	ordersOfPlayer = nullptr;
	playerID = nullptr;

}

 //insertion operator overlaod
ostream& operator<<(ostream& out, const Player & p) {

	out << "Player ID " << *p.playerID <<endl;
	return out;

}

//assignment Operator
Player& Player::operator=(const Player& p) {

	for (Territory* terr: *p.territoriesOfPlayer) {
		Territory coipiedTerr = Territory(*terr);
		territoriesOfPlayer->push_back(new Territory(coipiedTerr));
	}

	cardsOfPlayer = new list<Cards>(*(p.cardsOfPlayer));
	ordersOfPlayer = new list<Order>(*(p.ordersOfPlayer));
	playerID = new int(*(p.playerID));

	return *this;
}


// getter of the player's territories
list<Territory*>* Player::getListOfTerritories(){
	return territoriesOfPlayer;
}

// getter of the player's cards
list<Cards>* Player::getListofCards() {
	return cardsOfPlayer;
}

// this method returns a list of territories that need defence. If a given
// player territory has less than 3 units then it is added to the list
list<Territory*> Player::toDefend() {

	list<Territory*> territoriesToDefend;

	for (Territory *terr: *territoriesOfPlayer) {
		if (*(*terr).armies < 3) {
			territoriesToDefend.push_back(terr);
		}
	}

	return territoriesToDefend;
}

// this method checks the neighbours of each territory belonging to a player. 
// If the territory does not belong to the current player, then those territories are added to the territories to be attacked 
list<Territory*> Player::toAttack() {

	list<Territory*> enemyTerritoriesToAttack;
	for ( Territory* terr: *territoriesOfPlayer) {
		for (Territory* neighbourTerr: *(*terr).neighbours) {
			if (*(*neighbourTerr).owner != *this->playerID) {;
				enemyTerritoriesToAttack.push_back(neighbourTerr);
			}
		}
	}

	return enemyTerritoriesToAttack;
}

// this method creates an Order object with the corresponding input and then is sent to the list
void Player::issueOrder(string input) {

	Order o1 = Order(input);
	ordersOfPlayer->push_back(o1);

}

// print territories of player
void Player::printTerritories(){

	for (Territory *terr: *territoriesOfPlayer) {
		cout << "name of territory: " << *(*terr).name <<endl;
	}
}

// print list of territories
void Player::printTerritories(list<Territory*> inputList) {

	for (Territory* terr: inputList) {
		cout << *(*terr).name << endl;
	}

}

// this method adds a territory to a plyer and sets its owner variable to the ID of the player controlling that territory
void Player::addTerritory(Territory& terr){ 

	territoriesOfPlayer->push_back(&terr);
	*terr.owner = *this->playerID;
}

void Player::deleteTerritories() {

	for (Territory* terr: *territoriesOfPlayer) {
		(*terr).customDestructorTerritory();
	}
}

// adding a card to a player
void Player::addCard(Cards input) {
	cardsOfPlayer->push_back(input);
}

void Player::printCards() {
	for (Cards c: *cardsOfPlayer) {
		cout << *c.type << endl;
	}
}

// temporary constructor for Territory
Territory::Territory(string n) {
	cout << "surprise normal" << endl;
	name = new string(n);
	owner = new int(0);
	armies = new int(0);
	neighbours = new list<Territory*>();
}

Territory::Territory(const Territory &terr) {
	cout << "surprise" << endl;
	name = new string(*terr.name);
	owner = new int(*terr.owner);
	armies = new int(*terr.armies);
	neighbours = new list<Territory*>(*terr.neighbours);
}



void Territory::customDestructorTerritory() {

	delete name;
	delete owner;
	delete armies;
	delete neighbours;

	name = nullptr;
	owner = nullptr;
	armies = nullptr;
	neighbours = nullptr;

}

//temporary constructor for orders
Order::Order(string inputType) {
	type = new string(inputType);
}

Order::~Order() {
	
	//delete type;
	//type = nullptr;

}

void Player::printOrders() {

	for (Order o: *ordersOfPlayer) {
		cout << *o.type << endl;
	}
}

Cards::Cards(string input) {

	type = new string(input);

}

Cards::~Cards() {

	//delete type;
	//type = nullptr;
}

