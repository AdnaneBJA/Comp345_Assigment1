#ifndef ORDERS_H
#define ORDERS_H

#include <iostream>
#include <string>
#include <vector>

// Every data member is a pointer (assignment rule 1): created with new, freed in the destructor.

// Order: abstract parent of every order type
class Order {
public:
    Order();
    Order(const Order& other);
    virtual ~Order();  // deleting an Order* also runs the subclass destructor
    Order& operator=(const Order& other);

    virtual bool validate() const = 0;
    virtual void execute() = 0;
    virtual Order* clone() const = 0;  // copy of the right subclass, used to copy an OrdersList
    virtual std::string getName() const = 0;
    virtual std::string describe() const = 0;

    bool isExecuted() const;
    std::string getEffect() const;

    friend std::ostream& operator<<(std::ostream& out, const Order& order);

protected:
    void setEffect(std::string effectText);

private:
    bool* executed;
    std::string* effect;  // what the order did, set on execute
};

// Deploy armies from the reinforcement pool onto one of the player's territories.
class Deploy : public Order {
public:
    Deploy();
    Deploy(int armies, std::string targetTerritory);
    Deploy(const Deploy& other);
    ~Deploy();
    Deploy& operator=(const Deploy& other);

    bool validate() const;
    void execute();
    Order* clone() const;
    std::string getName() const;
    std::string describe() const;

    friend std::ostream& operator<<(std::ostream& out, const Deploy& order);

private:
    int* armies;
    std::string* targetTerritory;
};

// Advance to move armies to a neighbouring territory attack if enemy-owned)
class Advance : public Order {
public:
    Advance();
    Advance(int armies, std::string sourceTerritory, std::string targetTerritory);
    Advance(const Advance& other);
    ~Advance();
    Advance& operator=(const Advance& other);

    bool validate() const;
    void execute();
    Order* clone() const;
    std::string getName() const;
    std::string describe() const;

    friend std::ostream& operator<<(std::ostream& out, const Advance& order);

private:
    int* armies;
    std::string* sourceTerritory;
    std::string* targetTerritory;
};

// Bomb which destroy half the armies on an enemy territory.
class Bomb : public Order {
public:
    Bomb();
    Bomb(std::string targetTerritory);
    Bomb(const Bomb& other);
    ~Bomb();
    Bomb& operator=(const Bomb& other);

    bool validate() const;
    void execute();
    Order* clone() const;
    std::string getName() const;
    std::string describe() const;

    friend std::ostream& operator<<(std::ostream& out, const Bomb& order);

private:
    std::string* targetTerritory;
};

// Blockade triple armies on own territory, then it becomes neutral.
class Blockade : public Order {
public:
    Blockade();
    Blockade(std::string targetTerritory);
    Blockade(const Blockade& other);
    ~Blockade();
    Blockade& operator=(const Blockade& other);

    bool validate() const;
    void execute();
    Order* clone() const;
    std::string getName() const;
    std::string describe() const;

    friend std::ostream& operator<<(std::ostream& out, const Blockade& order);

private:
    std::string* targetTerritory;
};

// Airlift move armies between any two own territories (irlift card.
class Airlift : public Order {
public:
    Airlift();
    Airlift(int armies, std::string sourceTerritory, std::string targetTerritory);
    Airlift(const Airlift& other);
    ~Airlift();
    Airlift& operator=(const Airlift& other);

    bool validate() const;
    void execute();
    Order* clone() const;
    std::string getName() const;
    std::string describe() const;

    friend std::ostream& operator<<(std::ostream& out, const Airlift& order);

private:
    int* armies;
    std::string* sourceTerritory;
    std::string* targetTerritory;
};

// Negotiate no attacks between two players this turn diplomacy card.
class Negotiate : public Order {
public:
    Negotiate();
    Negotiate(std::string targetPlayer);
    Negotiate(const Negotiate& other);
    ~Negotiate();
    Negotiate& operator=(const Negotiate& other);

    bool validate() const;
    void execute();
    Order* clone() const;
    std::string getName() const;
    std::string describe() const;

    friend std::ostream& operator<<(std::ostream& out, const Negotiate& order);

private:
    std::string* targetPlayer;
};

// OrdersList a player's orders for the turn. Owns its orders and deletes them.
class OrdersList {
public:
    OrdersList();
    OrdersList(const OrdersList& other);
    ~OrdersList();
    OrdersList& operator=(const OrdersList& other);

    void add(Order* order);
    bool remove(int index);         // false if index doesn't exist
    bool move(int from, int to);    // false if either index doesn't exist
    int size() const;
    Order* get(int index) const;    // NULL if index doesn't exist

    friend std::ostream& operator<<(std::ostream& out, const OrdersList& list);

private:
    void deleteAllOrders();
    bool isValidIndex(int index) const;

    std::vector<Order*>* orders;
};

#endif