#pragma once
#include <list>
#include <string>
using namespace std; 

class Territory;
class Cards;
class Order;

// implementation of the Player class. 
class Player {

	//methods
	public:
		Player();
		Player(const Player &p);
		Player &operator=(const Player& p);
		static int* counterID;

			
		list<Territory>* getListOfTerritories();
		list<Cards>* getListofCards();

		list<Territory> toDefend();
		list<Territory> toAttack();
		void issueOrder();

		friend ostream& operator<<(ostream& out, const Player& p);
		void printTerritories();
		void printTerritories(list<Territory> inputList);
		void addTerritory(Territory terr);

	// attributes
	private:
		// setting a list of void pointers so to have more flexibility for later implementations
		list<Territory>* territoriesOfPlayer;
		list<Cards>* cardsOfPlayer;
		list<Order>* ordersOfPlayer;
		int* playerID;
};


// temporary Territory logic
class Territory {

public:
	string* name;
	int* armies;
	list<Territory>* neighbours;
	int* owner;

	Territory();
	Territory(string* name);
	Territory(int* id, string* name, int* armies, list<Territory>* neighbours, Player* player);

};

// temporary Cards logic
class Cards {
public:
	string* name;
	Cards();
	Cards(string* name);

};

// temporary Order logic
class Order {
private:
		string* type;
		Order(string* type);
};