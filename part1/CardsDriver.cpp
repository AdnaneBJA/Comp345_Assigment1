//
// Part 4 driver: creates a deck with every kind of card, gives a player a hand
// filled by drawing cards from the deck, then plays every card in the hand.
// Each play creates an order in the player's list of orders and returns the card
// to the deck.
//

#include "Cards.h"
#include "Player.h"

// Runs the deck/hand demonstration.
int main() {
    std::cout << "=== 1. Create a deck with every kind of card ===" << std::endl;
    Deck deck;
    std::cout << deck << std::endl;

    std::cout << "\n=== 2. Fill the player's hand by drawing 5 cards from the deck ===" << std::endl;
    Player player("Bob");
    for (int i = 0; i < 5; i++) {
        Card* drawn = deck.draw(player.getHand());
        if (drawn != nullptr) {
            std::cout << "draw() returned: " << *drawn << std::endl;
        }
    }
    std::cout << *player.getHand() << std::endl;
    std::cout << deck << "   <- the drawn cards were removed from the deck" << std::endl;

    std::cout << "\n=== 3. Play every card in the player's hand ===" << std::endl;
    for (Card* card : player.getHand()->getCards()) card->play(&player, &deck);

    std::cout << "\n=== 4. Result ===" << std::endl;
    std::cout << *player.getHand() << "   <- empty, every card was played" << std::endl;
    std::cout << deck << "   <- the played cards are back in the deck" << std::endl;
    std::cout << "Orders created in the player's list of orders:" << std::endl << *player.getOrders();

    return 0;
}