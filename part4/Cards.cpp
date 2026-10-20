#include "Cards.h"
#include <algorithm> // std::remove
#include <cstdlib>   // std::rand, std::srand
#include <ctime>     // std::time

//////////////////////////////////////Card class implementation/////////////////////////////////////////////////

Card::Card(CardType type) : type(new CardType(type)) {} //initialize directly with new Cardtype (no intermediate value)

Card::~Card() {
    delete type;
}

// Copy constructor
Card::Card(const Card& other) : type(new CardType(*other.type)) {}

// Assignment operator: copies the other card's type into this card's type.
Card& Card::operator=(const Card& other) {
    *type = *other.type;
    return *this; // so we return the reference of the actual object (Card& determines also that)
}

// Prints the card's type.
std::ostream& operator<<(std::ostream& os, const Card& card) {
    switch (*card.type) {
    case CardType::Bomb:          return os << "bomb";
    case CardType::Reinforcement: return os << "reinforcement";
    case CardType::Blockade:      return os << "blockade";
    case CardType::Airlift:       return os << "airlift";
    case CardType::Diplomacy:     return os << "diplomacy";
    }
    return os;
}

// Returns the card's type.
CardType Card::getType() const {
    return *type;
}

// Plays the card: adds the matching order to the orders list and then moves the
// card from the hand back to the deck.
/*void Card::play(Hand* hand, Deck* deck, OrdersList* orders) {
    switch (*type) {
    case CardType::Bomb:          orders->add(new Bomb()); break;
    case CardType::Reinforcement: orders->add(new Deploy()); break;
    case CardType::Blockade:      orders->add(new Blockade()); break;
    case CardType::Airlift:       orders->add(new Airlift()); break;
    case CardType::Diplomacy:     orders->add(new Negotiate()); break;
    }

    hand->removeCard(this);
    deck->addCard(this);
    std::cout << "Played " << *this << std::endl;
}*/

//////////////////////////////////////Hand class implementation/////////////////////////////////////////////////


 Hand::Hand() : cards(new std::vector<Card*>()) {}
 
 Hand::~Hand() {
     for (Card* card : *cards) delete card; //delete each card in the vector and then delete the vector
     delete cards;
 }

 Hand::Hand(const Hand& other)
 {
	 cards = new std::vector<Card*>();
	 for (Card* card : *other.cards) {
		 cards->push_back(new Card(*card)); //deep copy of each card
	 }
 }

 // Returns the cards in the hand.
 std::vector<Card*> Hand::getCards() const {
     return *cards;
 }

 //deletes this hand's cards, then copies each card of the other hand.
 Hand& Hand::operator=(const Hand& other) {
     if (this != &other) {
         for (Card* card : *cards) delete card;
         cards->clear();
         for (Card* card : *other.cards) cards->push_back(new Card(*card));
     }
     return *this;
 }

 // Prints every card in the hand.
 std::ostream& operator<<(std::ostream& os, const Hand& hand) {
     os << "Hand:";
     for (Card* card : *hand.cards) os << " " << *card;
     return os;
 }

 // Adds a card to the hand.
 void Hand::addCard(Card* card) {
     cards->push_back(card);
 }

 // Takes a card out of the hand without deleting it.
 void Hand::removeCard(Card* card) {
     cards->erase(std::remove(cards->begin(), cards->end(), card), cards->end()); //first removes the card and rearranges the array, then the erase reduces tha array's size
 }

 //////////////////////////////////////Deck class implementation/////////////////////////////////////////////////

// Creates a deck with two cards of each type.
// The deck creates its own cards instead of receiving them.
 Deck::Deck() : cards(new std::vector<Card*>()) {
     std::srand(std::time(nullptr)); // new random draws on each run
     for (CardType type : {CardType::Bomb, CardType::Reinforcement, CardType::Blockade, CardType::Airlift, CardType::Diplomacy}) {
         cards->push_back(new Card(type));
         cards->push_back(new Card(type));
     }
 }

 Deck::~Deck() {
     for (Card* card : *cards) delete card;
     delete cards;
 }

 Deck::Deck(const Deck& otherDeck) {

     cards = new std::vector<Card*>();
     for (Card* card : *otherDeck.cards)
     {
         cards->push_back(new Card(*card));
     }
 }

 Deck& Deck::operator=(const Deck& other)
 { 
     if(this != &other)
     { 
         for (Card* card : *cards) delete card;
         cards->clear();
         for (Card* card : *other.cards) cards->push_back(new Card(*card));
     }

     return *this;
 }

 std::ostream& operator<<(std::ostream& os, const Deck& deck)
 {
     os << "Deck:";
     for (Card* card : *deck.cards) os << " " << * card ;

     return os;
 }

 void Deck::addCard(Card* card)
 {
     cards->push_back(card);
 }

 void Deck::removeCard(Card* card)
 {
     cards->erase(std::remove(cards->begin(), cards->end(), card), cards->end());
 }

 void Deck::draw(Hand* hand)
 {
     if (cards->empty()) {
         std::cout << "The deck is empty" << std::endl;
         return;
     }
     int i = std::rand() % cards->size(); // the modulo keeps it in range of the available indexes of the vector
     Card* cardToDraw = (*cards)[i];
     this->removeCard(cardToDraw);
     hand->addCard(cardToDraw);
 }
