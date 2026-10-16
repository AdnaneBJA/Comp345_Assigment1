#include <iostream>	
#include "Player.h"

int main() {

	string country1 = "Canada";

	Territory terr1 = Territory(&country1);

	Player p1 = Player();

	p1.addTerritory(terr1);

	std::cout << p1 << endl;


	return 0;
}