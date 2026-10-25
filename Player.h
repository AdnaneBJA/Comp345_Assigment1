#ifndef PLAYER_H
#define PLAYER_H

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
		~Player();
		Player &operator=(const Player& p);
		static int* counterID;

		//getters	
		list<Territory*>* getListOfTerritories();
		list<Cards>* getListofCards();

		// needed methods
		list<Territory*> toDefend();
		list<Territory*> toAttack();
		void issueOrder(string input);

		// additional methods
		friend ostream& operator<<(ostream& out, const Player& p);
		// printing to console
		void printTerritories();
		void printTerritories(list<Territory*> inputList);
		void printCards();
		void printOrders();
		// delete pointers inside of lists
		void deleteTerritories();
		void deleteOrders();
		void deleteCards();
		// adding objects to lists
		void addTerritory(Territory& terr);
		void addCard(Cards input);

	// attributes
	private:
		// setting a list of void pointers so to have more flexibility for later implementations
		list<Territory*>* territoriesOfPlayer;
		list<Cards>* cardsOfPlayer;
		list<Order>* ordersOfPlayer;
		int* playerID;
};


// temporary Territory logic
class Territory {

public:
	string* name;
	int* armies;
	list<Territory*>* neighbours;
	int* owner;

	Territory();
	Territory(const Territory &terr);
	Territory(string name);
	void customDestructorTerritory();
	Territory(int* id, string* name, int* armies, list<Territory>* neighbours, Player* player);

};

// temporary Cards logic
class Cards {
public:
	string* type;
	Cards();
	Cards(string input);
	void customDeleteCards();

};

// temporary Order logic
class Order {
public:
		string* type;
		Order(string input);
		void customDeleteOrders();
};


#endif // PLAYER_H


