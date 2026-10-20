// Part 3 (Cards)

#ifndef COMP345_ASSIGNMENT1_CARDS_H
#define COMP345_ASSIGNMENT1_CARDS_H
#include <iostream>
#include <vector>

enum class CardType{ Bomb, Reinforcement, Blockade, Airlift, Diplomacy };

class Card {
public:
	Card(CardType type);
	Card(const Card& otherCard);
	~Card();
	Card& operator=(const Card& other);
	friend std::ostream& operator<<(std::ostream& os, const Card& card);
	CardType getType() const;
	void setType(CardType type);
	void play();
private:
	CardType* type;
};

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

class Deck {
public:
	Deck();
	~Deck();
	Deck(const Deck& otherDeck);
	Deck& operator=(const Deck& other);
	friend std::ostream& operator<<(std::ostream& os, const Deck& deck);
	void addCard(Card* card);
	void removeCard(Card* card);
	void draw(Hand* hand);
private:
	std::vector<Card*>* cards;
};

#endif //COMP345_ASSIGNMENT1_CARDS_H
