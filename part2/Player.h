#ifndef PLAYER_H
#define PLAYER_H

#include <iosfwd>
#include <string>
#include <vector>

#include "Map.h"
#include "Cards.h"
#include "Orders.h"

// A player of the game. A player owns a collection of territories (from Map.h),
// a hand of cards (Hand, from Cards.h) and a list of orders (OrdersList, from
// Orders.h). Every data member is a pointer. The player owns (and deletes) its
// name, its hand and its orders list, but the territories belong to the Map, so
// the player only keeps pointers to them and never deletes them.
class Player {

	//methods
	public:
		Player();
		Player(std::string name);
		Player(const Player &p);
		~Player();
		Player &operator=(const Player& p);
		friend std::ostream& operator<<(std::ostream& out, const Player& p);

		//getters
		std::string getName() const;
		std::vector<Territory*> getTerritories() const;
		Hand* getHand() const;
		OrdersList* getOrders() const;

		// needed methods
		std::vector<Territory*> toDefend();
		std::vector<Territory*> toAttack();
		void issueOrder(std::string orderType);

		// adding a territory to the player
		void addTerritory(Territory* terr);

		// printing a list of territories to the console
		static void printTerritories(const std::vector<Territory*>& inputList);

	// attributes
	private:
		std::string* name;
		std::vector<Territory*>* territoriesOfPlayer;
		Hand* hand;
		OrdersList* ordersOfPlayer;
};

#endif // PLAYER_H
