#include "Player.h"
#include <list>
#include <vector>
#include <string>
#include <iostream>
using namespace std;

int* Player::counterID = new int(1);

// player constrcutor
Player::Player() {

	territoriesOfPlayer = new list<Territory>();
	cardsOfPlayer = new list<Cards>();
	ordersOfPlayer = new list<Order>();
	playerID = new int(*counterID);
	(*counterID)++;
}

// copy constructor
Player::Player(const Player& p) {

	territoriesOfPlayer = new list<Territory>(*(p.territoriesOfPlayer));
	cardsOfPlayer = new list<Cards>(*(p.cardsOfPlayer));
	ordersOfPlayer = new list<Order>(*(p.ordersOfPlayer));
	playerID = new int(*(p.playerID));
}

 //insertion operator overlaod
ostream& operator<<(ostream& out, const Player & p) {

	out << "Player ID " << *p.playerID <<endl;
	return out;

}


// getter of the player's territories
list<Territory>* Player::getListOfTerritories(){
	return territoriesOfPlayer;
}

// getter of the player's cards
list<Cards>* Player::getListofCards() {
	return cardsOfPlayer;
}

// this method returns a list of territories that need defence. If a given
// player territory has less than 3 units then it is added to the list
list<Territory> Player::toDefend() {

	list<Territory> territoriesToDefend;

	for (Territory terr: *territoriesOfPlayer) {
		if (*terr.armies < 3) {
			territoriesToDefend.push_back(terr);
		}
	}

	return territoriesToDefend;
}

// this method checks the neighbours of each territory belonging to a player. 
// If the territory does not belong to the current player, then those territories are added to the territories to be attacked 
list<Territory> Player::toAttack() {
	list<Territory> enemyTerritoriesToAttack;
	for (Territory terr: *territoriesOfPlayer) {
		for (Territory neighbourTerr: *terr.neighbours) {
			if (*neighbourTerr.owner != *this->playerID) {;
				enemyTerritoriesToAttack.push_back(neighbourTerr);
			}
		}
	}

	return enemyTerritoriesToAttack;
}

void Player::printTerritories(){

	for (Territory terr: *territoriesOfPlayer) {
		cout << "name of territory: " << *terr.name << endl;
	}
}

void Player::printTerritories(list<Territory> inputList) {

	for (Territory terr: inputList) {
		cout << *terr.name << endl;
	}

}

void Player::addTerritory(Territory terr){ 

	territoriesOfPlayer->push_back(terr);
	*terr.owner = *this->playerID;
}


Territory::Territory(string* n) {
	name = n;
	owner = new int(0);
	armies = new int(0);
	neighbours = new list<Territory>();
}




