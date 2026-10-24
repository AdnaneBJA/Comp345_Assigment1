//
// Part 4 driver: creates a deck with every kind of card, fills a hand by drawing
// from it then plays every card in the hand.
//

#include "Cards.h"

int main() {
    std::cout << "=== 1. Create a deck with every kind of card ===" << std::endl;
    Deck deck;
    std::cout << deck << std::endl;
 
    std::cout << "\n=== 2. Create a hand and fill it by drawing 5 cards from the deck ===" << std::endl;
    Hand hand;
    for (int i = 0; i < 5; i++) deck.draw(&hand);
    std::cout << hand << std::endl;
    std::cout << deck << std::endl;
 
    std::cout << "\n=== 3. Play every card in the hand ===" << std::endl;
    OrdersList orders;
    for (Card* card : hand.getCards()) card->play(&hand, &deck, &orders);
 
    std::cout << "\n=== 4. Result ===" << std::endl;
    std::cout << hand << "   <- empty, every card was played" << std::endl;
    std::cout << deck << "   <- the played cards are back in the deck" << std::endl;
    std::cout << "Orders created by the cards: \n" << orders << std::endl;
 
    return 0;
}
 