#include <iostream>	
#include "Player.h"
#define _CRTDBG_MAP_ALLOC
#include <cstdlib>
#include <crtdbg.h>



int main() {
	// checking memory leaks 
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);


	// info of territories
	string country1 = "France";
	Territory terr1 = Territory(country1);
	*terr1.armies = 6;

	string country2 = "Spain";
	Territory terr2 = Territory(country2);
	*terr2.armies = 1;

	string country3 = "Portugal";
	Territory terr3 = Territory(country3);
	*terr3.armies = 7;

	string country4 = "Italy";
	Territory terr4 = Territory(country4);
	*terr4.armies = 0;

	// France is connected to Spain and Italy
	terr1.neighbours->push_back(&terr2);
	terr1.neighbours->push_back(&terr4);

	// Spain is connected to France and Portugal
	terr2.neighbours->push_back(&terr1);
	terr2.neighbours->push_back(&terr3);

	// Portugal is connected to Spain
	terr3.neighbours->push_back(&terr2);

	// Italy is connected to France
	terr4.neighbours->push_back(&terr1);


	// info of player one
	// It has Spain and portugal
	Player p1 = Player();
	p1.addTerritory(terr2);
	p1.addTerritory(terr3);
	cout << "printing player one: " << p1 << endl;
	p1.printTerritories();
	cout << endl;

	//adding orders to player one
	p1.issueOrder("deployment");
	p1.issueOrder("advance");

	// adding cards to player one
	Cards c1 = Cards("bomb");
	p1.addCard(c1);

	//info of player two
	// It has France and Italy
	Player p2 = Player();
	p2.addTerritory(terr1);
	p2.addTerritory(terr4);
	cout << "printing player two: " << p2 << endl;
	p2.printTerritories();
	cout << endl;

	// copying player one
	Player pCopy = Player(p1);
	cout << "Copied player" << endl;
	pCopy.printTerritories();
	pCopy.getListOfTerritories()->pop_front();
	cout << "after poping" << endl;
	pCopy.printTerritories();
	cout << "player one again" << endl;
	p1.printTerritories();

	cout << endl;

	// assigment operator
	Player p3;
	p3 = p2;
	cout << endl << "assigned Player" << endl;
	cout << p3 << endl;
	p3.printTerritories();
	cout << endl;

	list<Territory*> l1toAttack = p1.toAttack();
	list<Territory*> l1ToDefend = p1.toDefend();

	cout << "From the perspective of Player one" << endl;
	cout << "These are the territoires that could be attacked" << endl;
	p1.printTerritories(l1toAttack);
	cout << "These are the territoires that could be defended" << endl;
	p1.printTerritories(l1ToDefend);
	cout << endl << "orders of player one" << endl;
	p1.printOrders();
	cout << "Cards of player one" << endl;
	p1.printCards();

	p1.deleteTerritories();
	p2.deleteTerritories();
	pCopy.deleteTerritories();
	p3.deleteTerritories();

	return 0;
}