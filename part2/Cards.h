// Part 4 (Cards)

#ifndef COMP345_ASSIGNMENT1_CARDS_H
#define COMP345_ASSIGNMENT1_CARDS_H
#include <iostream>
#include <vector>
#include "Orders.h"

//I declared them before because cards doesnt see hand or deck.
class Hand;        // defined below
class Deck;        // defined below
class Player; // Only needs to know that player exists

// The five kinds of Warzone cards.
enum class CardType { Bomb, Reinforcement, Blockade, Airlift, Diplomacy };

// A card of one of the five types. Playing it creates the matching order.
class Card {
public:
	Card(CardType type);
	Card(const Card& otherCard);
	~Card();
	Card& operator=(const Card& other);
	friend std::ostream& operator<<(std::ostream& os, const Card& card);
	CardType getType() const;
	void play(Player* player, Deck* deck);
private:
	CardType* type;
};

// The cards a player is holding.
class Hand {
public:
	Hand();
	~Hand();
	Hand(const Hand& other);
	Hand& operator=(const Hand& other);
	friend std::ostream& operator<<(std::ostream& os, const Hand& hand);

	void addCard(Card* card);
	void removeCard(Card* card);
	std::vector<Card*> getCards() const;
private:
	std::vector<Card*>* cards;
};

// The pile of cards players draw from.
class Deck {
public:
	Deck();
	~Deck();
	Deck(const Deck& otherDeck);
	Deck& operator=(const Deck& other);
	friend std::ostream& operator<<(std::ostream& os, const Deck& deck);
	void addCard(Card* card);
	void removeCard(Card* card);
	Card* draw(Hand* hand);
private:
	std::vector<Card*>* cards;
};

#endif