/* inventory.cpp, written by Russell Abernethy */

#include "inventory.h"
#include "item.h"
#include <cstdlib>
#include <vector>

using namespace std;

/*
Inventory(void):
    desc:
        --> creates an inventory object with no maximum capacity.
        --> object constructor.
        --> public method.
*/
Inventory::Inventory() {
    size = 0;
}

/*
Inventory(int maxCapacity):
    desc:
        --> creates an inventory object with a maximum capacity.
        --> object constructor.
        --> public method.
    input: 
        --> int maxCapacity: the maximum number of individual items that can be stored in the inventory.
            * if passed a number less < zero, the inventory will default to a maxCapacity of one.
*/
Inventory::Inventory(int maxCapacity) {
    (maxCapacity < 1) ? cap = 1 : cap = maxCapacity;
    size = 0;
}

/*
numItems(void):
    desc:
        --> checks the number of items in the inventory.
        --> public method.
    output:
        --> returns the number of items in the inventory.
            * this number is the sum of the quantities of each item in the inventory.
*/
int Inventory::numItems() {
    return size;
}

/*
setCapacity(int newCapacity):
    desc:
        --> changes the capacity of an inventory.
        --> public method.
    input:
        --> int newCapacity: the new capacity of the inventory.
            * newCapacity cannot be < zero, otherwise it will not be changed.
*/
void Inventory::setCapacity(int newCapacity) {
    (newCapacity > 0) ? cap = newCapacity : true;
}

/*
add(Item item):
    desc: 
        --> adds one of an item to the inventory.
        --> there must be adequate space in the inventory to add an item.
        --> public method.
    input: 
        --> Item item: the item to be added to the inventory.
    outputs:
        --> returns true if the item was successfully added.
        --> returns false if the item could not be added to the inventory.
*/
bool Inventory::add(Item item) {
    return add(item, 1);
}

/*
add(Item item, int quantity):
    desc:
        --> adds the quantity of item to the inventory.
        --> if the item already exists in the inventory, just change the quantity of that item.
        --> there must be adequate space in the inventory to add an item.
        --> public method.
    inputs:
        --> Item item: the item to be added to the inventory.
        --> int quantity: the quantity of the item to be added to the inventory.
    outputs:
        --> returns true if the item was successfully added to the inventory.
        --> returns false if the item could not be added to the inventory.
*/
bool Inventory::add(Item item, int quantity) {
    if(cap && size + quantity > cap)
        return false;
    else if(contains(item) != -1)
        inv[contains(item)].quantity += quantity;
    else
        inv.push_back(item);
    size += quantity;
    return true;
}

/*
remove(Item item):
    desc:
        --> removes one of an item from the inventory.
        --> public method.
    input:
        --> Item item: the item to be removed from the inventory.
    outputs:
        --> returns true if the item was removed from the inventory.
        --> returns false if the item could not be removed from the inventory.
*/
bool Inventory::remove(Item item) {
    return remove(item, 1);
}

/*
removeAll(Item item):
    desc:
        --> removes all of an item from an inventory.
    input:
        --> Item item: the item to be removed entirely from an inventory.
    output:
        --> return true if the item was completely removed from the inventory.
        --> return false if the item could not completely be removed from the inventory.
*/
bool Inventory::removeAll(Item item) {
    return remove(item, item.quantity);
}

/*
remove(Item item, int quantity):
    desc:
        --> removes the quantity of item from the inventory.
        --> public method.
    inputs:
        --> Item item: the item to be removed from the inventory.
        --> int quantity: the quantity of item to remove from the inventory.
    outputs:
        --> returns true if the quantity of item was removed from the inventory.
        --> returns false if the quantity of item could not be removed from the inventory.
*/
bool Inventory::remove(Item item, int quantity) {
    for(int i = 0; i < inv.size(); i++) {
        if(inv[i].equals(item)) {
            if(quantity - item.quantity > 0)
                item.quantity -= quantity;
            else
                inv.erase(inv.begin() + i);    
            size -= item.quantity;
            return true;
        }
    }
    return false;
}

/*
contatins(Item item):
    desc:
        --> searches the inventory for the passed item.
        --> public method.
    input:
        --> Item item: the item to be searched for in the inventory.
    outputs:
        --> returns the index of the item in the inventory.
        --> returns -1 if the item could not be found in the inventory.
*/
int Inventory::contains(Item item) {
    for(int i = 0; i < inv.size(); i++) {
        if(inv[i].equals(item))
            return i;
    }
    return -1;
}

/*
toString(void):
    desc:
        --> creates a string representation of the inventory.
        --> public method.
    output: 
        --> returns a string that contatins the following information about the inventory:
            * the item's name.
*/
std::string Inventory::toString() {
    if(inv.size() == 0)
        return "[ ]";
    std::string toReturn = "[";
    for(int i = 0; i < inv.size() - 1; i++)
        toReturn.append(inv[i].name + ", ");
    toReturn.append(inv[inv.size()-1].name);
    return toReturn + "]";
}

/*
merge(Inventory &toCombine):
    desc: 
        --> combines two inventories together.
        --> public method.
    input:
        --> Inventory &toCombine: the inventory to be combined into the inventory.
    outputs:
        --> returns true if the merge was sucessful.
        --> returns false if the merge was unsuccessful.
*/
bool Inventory::merge(Inventory &toCombine) {
    if(cap && size + toCombine.size > cap)
        return false;
    while (toCombine.size != 0) {
        add(toCombine.inv.back());
        toCombine.removeAll(toCombine.inv.back());
    }
    return true;
}