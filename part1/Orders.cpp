#include "Orders.h"

using namespace std;

// Order 

// Default constructor: not executed yet
Order::Order() {
    this->executed = false;
    this->effect = "";
}

// Copy constructor
Order::Order(const Order& other) {
    this->executed = other.executed;
    this->effect = other.effect;
}

// Destructor
Order::~Order() {
}

// Assignment operator
Order& Order::operator=(const Order& other) {
    if (this != &other) {
        this->executed = other.executed;
        this->effect = other.effect;
    }
    return *this;
}

// Getter: executed
bool Order::isExecuted() const {
    return executed;
}

// Getter: effect
string Order::getEffect() const {
    return effect;
}

// Mark as executed + save effect
void Order::setEffect(string effectText) {
    this->executed = true;
    this->effect = effectText;
}

// Print order, plus effect if executed
ostream& operator<<(ostream& out, const Order& order) {
    out << order.getName() << " order: " << order.describe();
    if (order.isExecuted()) {
        out << " | Effect: " << order.getEffect();
    }
    return out;
}

//Deploy 

// Default constructor (invalid order)
Deploy::Deploy() {
    this->armies = 0;
    this->targetTerritory = "";
}

// Constructor
Deploy::Deploy(int armies, string targetTerritory) {
    this->armies = armies;
    this->targetTerritory = targetTerritory;
}

// Copy constructor (": Order(other)" copies the parent part)
Deploy::Deploy(const Deploy& other) : Order(other) {
    this->armies = other.armies;
    this->targetTerritory = other.targetTerritory;
}

// Destructor
Deploy::~Deploy() {
}

// Assignment operator
Deploy& Deploy::operator=(const Deploy& other) {
    if (this != &other) {
        Order::operator=(other);
        this->armies = other.armies;
        this->targetTerritory = other.targetTerritory;
    }
    return *this;
}

// Valid: armies > 0, territory given. TODO with Player: player owns territory
bool Deploy::validate() const {
    if (armies <= 0) {
        return false;
    }
    if (targetTerritory == "") {
        return false;
    }
    return true;
}

// Execute only if valid
void Deploy::execute() {
    if (validate()) {
        setEffect("Deployed " + to_string(armies) + " armies to " + targetTerritory + ".");
    }
}

// Copy of this order
Order* Deploy::clone() const {
    return new Deploy(*this);
}

// Order type name
string Deploy::getName() const {
    return "Deploy";
}

// Short description
string Deploy::describe() const {
    return "deploy " + to_string(armies) + " armies to " + targetTerritory;
}

// Print (same as Order)
ostream& operator<<(ostream& out, const Deploy& order) {
    const Order& asOrder = order;
    out << asOrder;
    return out;
}

// Advance 

// Default constructor (invalid order)
Advance::Advance() {
    this->armies = 0;
    this->sourceTerritory = "";
    this->targetTerritory = "";
}

// Constructor
Advance::Advance(int armies, string sourceTerritory, string targetTerritory) {
    this->armies = armies;
    this->sourceTerritory = sourceTerritory;
    this->targetTerritory = targetTerritory;
}

// Copy constructor
Advance::Advance(const Advance& other) : Order(other) {
    this->armies = other.armies;
    this->sourceTerritory = other.sourceTerritory;
    this->targetTerritory = other.targetTerritory;
}

// Destructor
Advance::~Advance() {
}

// Assignment operator
Advance& Advance::operator=(const Advance& other) {
    if (this != &other) {
        Order::operator=(other);
        this->armies = other.armies;
        this->sourceTerritory = other.sourceTerritory;
        this->targetTerritory = other.targetTerritory;
    }
    return *this;
}

// Valid: armies > 0, two different territories. TODO with Player/Map: ownership, adjacency
bool Advance::validate() const {
    if (armies <= 0) {
        return false;
    }
    if (sourceTerritory == "" || targetTerritory == "") {
        return false;
    }
    if (sourceTerritory == targetTerritory) {
        return false;
    }
    return true;
}

// Execute only if valid
void Advance::execute() {
    if (validate()) {
        setEffect("Advanced " + to_string(armies) + " armies from " + sourceTerritory
            + " to " + targetTerritory + ".");
    }
}

// Copy of this order
Order* Advance::clone() const {
    return new Advance(*this);
}

// Order type name
string Advance::getName() const {
    return "Advance";
}

// Short description
string Advance::describe() const {
    return "advance " + to_string(armies) + " armies from " + sourceTerritory
        + " to " + targetTerritory;
}

// Print (same as Order)
ostream& operator<<(ostream& out, const Advance& order) {
    const Order& asOrder = order;
    out << asOrder;
    return out;
}

// Bomb 

// Default constructor (invalid order)
Bomb::Bomb() {
    this->targetTerritory = "";
}

// Constructor
Bomb::Bomb(string targetTerritory) {
    this->targetTerritory = targetTerritory;
}

// Copy constructor
Bomb::Bomb(const Bomb& other) : Order(other) {
    this->targetTerritory = other.targetTerritory;
}

// Destructor
Bomb::~Bomb() {
}

Bomb& Bomb::operator=(const Bomb& other) {
    if (this != &other) {
        Order::operator=(other);
        this->targetTerritory = other.targetTerritory;
    }
    return *this;
}


bool Bomb::validate() const {
    if (targetTerritory == "") {
        return false;
    }
    return true;
}

// Execute only if valid
void Bomb::execute() {
    if (validate()) {
        setEffect("Bombed " + targetTerritory + ", destroying half of its armies.");
    }
}

// Copy of this order
Order* Bomb::clone() const {
    return new Bomb(*this);
}

// Order type name
string Bomb::getName() const {
    return "Bomb";
}

// Short description
string Bomb::describe() const {
    return "bomb " + targetTerritory;
}

// Print (same as Order)
ostream& operator<<(ostream& out, const Bomb& order) {
    const Order& asOrder = order;
    out << asOrder;
    return out;
}

//Blockade

// Default constructor (invalid order)
Blockade::Blockade() {
    this->targetTerritory = "";
}

// Constructor
Blockade::Blockade(string targetTerritory) {
    this->targetTerritory = targetTerritory;
}

// Copy constructor
Blockade::Blockade(const Blockade& other) : Order(other) {
    this->targetTerritory = other.targetTerritory;
}

// Destructor
Blockade::~Blockade() {
}

// Assignment operator
Blockade& Blockade::operator=(const Blockade& other) {
    if (this != &other) {
        Order::operator=(other);
        this->targetTerritory = other.targetTerritory;
    }
    return *this;
}

// Valid: territory given. TODO with Player: player owns territory
bool Blockade::validate() const {
    if (targetTerritory == "") {
        return false;
    }
    return true;
}

// Execute only if valid
void Blockade::execute() {
    if (validate()) {
        setEffect("Blockaded " + targetTerritory + ": armies tripled and territory became neutral.");
    }
}

// Copy of this order
Order* Blockade::clone() const {
    return new Blockade(*this);
}

// Order type name
string Blockade::getName() const {
    return "Blockade";
}

// Short description
string Blockade::describe() const {
    return "blockade " + targetTerritory;
}

// Print (same as Order)
ostream& operator<<(ostream& out, const Blockade& order) {
    const Order& asOrder = order;
    out << asOrder;
    return out;
}

// Airlift 

// Default constructor (invalid order)
Airlift::Airlift() {
    this->armies = 0;
    this->sourceTerritory = "";
    this->targetTerritory = "";
}

// Constructor
Airlift::Airlift(int armies, string sourceTerritory, string targetTerritory) {
    this->armies = armies;
    this->sourceTerritory = sourceTerritory;
    this->targetTerritory = targetTerritory;
}

// Copy constructor
Airlift::Airlift(const Airlift& other) : Order(other) {
    this->armies = other.armies;
    this->sourceTerritory = other.sourceTerritory;
    this->targetTerritory = other.targetTerritory;
}

// Destructor
Airlift::~Airlift() {
}

// Assignment operator
Airlift& Airlift::operator=(const Airlift& other) {
    if (this != &other) {
        Order::operator=(other);
        this->armies = other.armies;
        this->sourceTerritory = other.sourceTerritory;
        this->targetTerritory = other.targetTerritory;
    }
    return *this;
}

// Valid: armies > 0, two different territories. TODO with Player: player owns both
bool Airlift::validate() const {
    if (armies <= 0) {
        return false;
    }
    if (sourceTerritory == "" || targetTerritory == "") {
        return false;
    }
    if (sourceTerritory == targetTerritory) {
        return false;
    }
    return true;
}

// Execute only if valid
void Airlift::execute() {
    if (validate()) {
        setEffect("Airlifted " + to_string(armies) + " armies from " + sourceTerritory
            + " to " + targetTerritory + ".");
    }
}

// Copy of this order
Order* Airlift::clone() const {
    return new Airlift(*this);
}

// Order type name
string Airlift::getName() const {
    return "Airlift";
}

// Short description
string Airlift::describe() const {
    return "airlift " + to_string(armies) + " armies from " + sourceTerritory
        + " to " + targetTerritory;
}

// Print (same as Order)
ostream& operator<<(ostream& out, const Airlift& order) {
    const Order& asOrder = order;
    out << asOrder;
    return out;
}

// Negotiate 

// Default constructor (invalid order)
Negotiate::Negotiate() {
    this->targetPlayer = "";
}

// Constructor
Negotiate::Negotiate(string targetPlayer) {
    this->targetPlayer = targetPlayer;
}

// Copy constructor
Negotiate::Negotiate(const Negotiate& other) : Order(other) {
    this->targetPlayer = other.targetPlayer;
}

// Destructor
Negotiate::~Negotiate() {
}

// Assignment operator
Negotiate& Negotiate::operator=(const Negotiate& other) {
    if (this != &other) {
        Order::operator=(other);
        this->targetPlayer = other.targetPlayer;
    }
    return *this;
}

// Valid: player given. 
bool Negotiate::validate() const {
    if (targetPlayer == "") {
        return false;
    }
    return true;
}

// Execute only if valid
void Negotiate::execute() {
    if (validate()) {
        setEffect("Negotiated with " + targetPlayer + ": no attacks between the two players this turn.");
    }
}

// Copy of this order
Order* Negotiate::clone() const {
    return new Negotiate(*this);
}

// Order type name
string Negotiate::getName() const {
    return "Negotiate";
}

// Short description
string Negotiate::describe() const {
    return "negotiate with " + targetPlayer;
}

// Print (same as Order)
ostream& operator<<(ostream& out, const Negotiate& order) {
    const Order& asOrder = order;
    out << asOrder;
    return out;
}

// OrdersList 

// Default constructor: empty list
OrdersList::OrdersList() {
    this->orders = new vector<Order*>();
}

// Copy constructor: deep copy (each order cloned)
OrdersList::OrdersList(const OrdersList& other) {
    this->orders = new vector<Order*>();
    for (int i = 0; i < other.size(); i++) {
        orders->push_back(other.get(i)->clone());
    }
}

// Destructor: delete orders, then the vector
OrdersList::~OrdersList() {
    deleteAllOrders();
    delete orders;
}

// Assignment operator: delete own orders, then deep copy
OrdersList& OrdersList::operator=(const OrdersList& other) {
    if (this != &other) {
        deleteAllOrders();
        for (int i = 0; i < other.size(); i++) {
            orders->push_back(other.get(i)->clone());
        }
    }
    return *this;
}

// Add at the end
void OrdersList::add(Order* order) {
    if (order != nullptr) {
        orders->push_back(order);
    }
}

// Delete order at index
bool OrdersList::remove(int index) {
    if (!isValidIndex(index)) {
        return false;
    }
    delete orders->at(index);                 // free the order
    orders->erase(orders->begin() + index);   // remove its slot
    return true;
}

// Move order from one index to another
bool OrdersList::move(int from, int to) {
    if (!isValidIndex(from) || !isValidIndex(to)) {
        return false;
    }
    Order* orderToMove = orders->at(from);
    orders->erase(orders->begin() + from);
    orders->insert(orders->begin() + to, orderToMove);
    return true;
}

// Number of orders (cast: vector size isn't an int)
int OrdersList::size() const {
    return static_cast<int>(orders->size());
}

// Order at index, or nullptr
Order* OrdersList::get(int index) const {
    if (!isValidIndex(index)) {
        return nullptr;
    }
    return orders->at(index);
}

// Delete every order, empty the vector
void OrdersList::deleteAllOrders() {
    for (int i = 0; i < size(); i++) {
        delete orders->at(i);
    }
    orders->clear();
}

// Index in range?
bool OrdersList::isValidIndex(int index) const {
    if (index < 0 || index >= size()) {
        return false;
    }
    return true;
}

// Print each order on its own line
ostream& operator<<(ostream& out, const OrdersList& list) {
    if (list.size() == 0) {
        out << "  (empty)" << endl;
        return out;
    }
    for (int i = 0; i < list.size(); i++) {
        out << "  [" << i << "] " << *list.get(i) << endl;
    }
    return out;
}