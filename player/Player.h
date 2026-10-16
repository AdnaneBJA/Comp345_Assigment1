#pragma once
#include <list>
#include <string>
#include <vector>
using namespace std; //??????

class Territory;
class Cards;
class Order;

// implementation of the Player class. 
class Player {

	//methods
	public:
		Player();
		//Player(list<Territory>* territoriesOfPlayer,list<Cards>* cardsOfPlayer, list<Order>* ordersOfPlayer);
		Player(const Player &p);

		list<Territory>* getListOfTerritories();
		list<Cards>* getListofCards();

		list<Territory> toDefend();
		list<Territory> toAttack();
		void issueOrder();

		friend ostream& operator<<(ostream& out, const Player& p);
		void printTerritories() const;
		void addTerritory(Territory terr);

	// attributes
	private:
		// setting a list of void pointers so to have more flexibility for later implementations
		list<Territory>* territoriesOfPlayer;
		list<Cards>* cardsOfPlayer;
		list<Order>* ordersOfPlayer;
};


// temporary Territory logic
class Territory {

public:
	int* id;
	string* name;
	int* armies;
	list<Territory>* neighbours;
	Player* player;


	Territory();
	Territory(string* name);
	Territory(int* id, string* name, int* armies, list<Territory>* neighbours, Player* player);

};

// temporary Cards logic
class Cards {
	string* name;
	Cards();
	Cards(string* name);

};

// temporary Order logic
class Order {
	public:
		string* type;
		Order();
		Order(string* type);
};