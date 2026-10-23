#include "Orders.h"

#include <iostream>

using namespace std;

// Demo for create, validate, move, remove, copy, execute
void testOrdersLists() {
    cout << "===== Part 3: Orders list =====" << endl << endl;

    // Create: one of each kind + invalid + extra 
    OrdersList list;
    list.add(new Deploy(5, "Quebec"));
    list.add(new Advance(3, "Quebec", "Ontario"));
    list.add(new Bomb("Alaska"));
    list.add(new Blockade("Greenland"));
    list.add(new Airlift(4, "Quebec", "Alberta"));
    list.add(new Negotiate("Player 2"));
    list.add(new Deploy(0, "Ontario"));             // invalid because of 0, cant deploy anything that is 0
    list.add(new Advance(2, "Ontario", "Quebec"));  // extra, removed below

    cout << "Orders list after adding one order of each kind, one invalid order and one extra order:" << endl;
    cout << list << endl;

    // Validate
    cout << "Validating every order:" << endl;
    for (int i = 0; i < list.size(); i++) {
        Order* order = list.get(i);
        cout << "  [" << i << "] " << order->getName() << " -> ";
        if (order->validate()) {
            cout << "valid" << endl;
        }
        else {
            cout << "INVALID" << endl;
        }
    }
    cout << endl;

    // Move
    cout << "Moving order 5 (Negotiate) to position 0:" << endl;
    list.move(5, 0);
    cout << list << endl;

    // Remove
    cout << "Removing order 7 (the extra Advance):" << endl;
    list.remove(7);
    cout << list << endl;

    // Bad indices: rejected, no crash
    cout << "Trying to move order 42 and to remove order -1:" << endl;
    if (list.move(42, 0)) {
        cout << "  move(42, 0) returned true" << endl;
    }
    else {
        cout << "  move(42, 0) returned false" << endl;
    }
    if (list.remove(-1)) {
        cout << "  remove(-1) returned true" << endl;
    }
    else {
        cout << "  remove(-1) returned false" << endl;
    }
    cout << endl;

    // copy constructor
    OrdersList copiedList(list);  
    OrdersList assignedList;
    assignedList = list;          
    copiedList.remove(0);

    cout << "Copy made with the copy constructor, then its first order removed:" << endl;
    cout << copiedList << endl;
    cout << "Copy made with the assignment operator (unchanged):" << endl;
    cout << assignedList << endl;
    cout << "Original list (unchanged by the copies):" << endl;
    cout << list << endl;

    // Execute: valid ones get an effect, invalid ones do nothing
    cout << "Executing every order in the original list:" << endl;
    for (int i = 0; i < list.size(); i++) {
        Order* order = list.get(i);
        order->execute();
        if (!order->isExecuted()) {
            cout << "  [" << i << "] " << order->getName() << " order is invalid and was not executed." << endl;
        }
    }
    cout << endl;

    cout << "Orders list after execution (executed orders show their effect):" << endl;
    cout << list << endl;

    // << on a single order
    Deploy singleDeploy(2, "Nunavut");
    singleDeploy.execute();
    cout << "Stream insertion on a single Deploy object:" << endl;
    cout << "  " << singleDeploy << endl;
}

// Entry point
int main() {
    testOrdersLists();
    return 0;
}