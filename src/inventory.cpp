/* inventory.cpp, written by Russell Abernethy & James Gottshall */

#include "inventory.h"
#include "item.h"
#include <cstdlib>
#include <vector>
#include <iostream>
#include <fstream>

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
    Inventory();
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
    // TODO: Re-add size check
    if (contains(item) != -1) {
        inv[contains(item)].quantity += item.quantity;
    } else {
        inv.push_back(item);
    }
    size += item.quantity;
    return true;
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

// DEPRECATED
bool Inventory::add(Item item, int quantity) {
    if((cap != 0) && ((size + quantity) > cap))
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
    for(int i = 0; i < (int)inv.size(); i++) {
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
    for(int i = 0; i < (int)inv.size(); i++) {
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
    for(int i = 0; i < (int)inv.size() - 1; i++)
        toReturn.append(inv[i].name +" x"+ std::to_string(inv[i].quantity) +", ");
    toReturn.append(inv[inv.size()-1].name + " x" + std::to_string(inv[inv.size()-1].quantity));
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
bool Inventory::merge(Inventory& toCombine) { 
    // Changed toCombine to be pass by value, hopefully this fixes the "phantom bug"
    //if(cap && (size + toCombine.getSize() > cap))
    //   return false; // Commented out while searching for phantom bug - BINGO
    // Earlier issues seem to have come from above, we need logging badly for failed attempts @Russell
    
    // I've taken the liberty to rewrite this, sorry not sorry - Jimmy
    for (int i=0; i < toCombine.getSlots(); i++) {
        Item newItem = toCombine.inv[i]; // Copy constructor
        add(newItem);
        // toCombine.removeAll(toCombine.inv.back()); BAD @Russell -- I have a feeling this kinda thing is what's killing us
    }
    return true;
}

// exports inventory description as a file, useful for saving Inventory states between sessions
bool Inventory::exportFile(std::string filename) {
    ofstream ofile;
    ofile.open(filename);
    if (!ofile.is_open()) {return false;}
    // For each item in the inventory, serialize it and write to ofile
    for (int i=0; i < (int)inv.size(); i++) {
        ofile << inv[i].serialize() << "\n";
    }
    ofile.close();
    return true;
}

// imports inventory from a file. Useful for creating merchant item tables
bool Inventory::importFile(std::string filename) {
    std::string line;
    ifstream ifile (filename);
    if (!ifile.is_open()) { 
        std::cerr << "Could Not Open File: " << filename << std::endl;
        return false; 
    }
    
    // for every line in ifile, add item to inventory
    while (getline(ifile, line)) {
        if (line.length() > 5) { // Dumb check to see if it's a valid line since valid lines have at least 5 characters
            Item itm = Item(line);
            if (!add(itm)) { // Changed this to use the non-deprecated add
                std::cerr << "Failed to add item: " << itm.name << " x" << itm.quantity << std::endl; // should be replaced with logging
            }
        }
    }
    ifile.close();
    
    return true;
}

int Inventory::getSize() const
{
    return size;
}

int Inventory::getSlots() const
{
    return inv.size();
}

Item Inventory::randItem()
{
    long totWeight = 0; // Totes weight, lol.
    for (u_int16_t i=0; i < inv.size(); i++) {
        totWeight += inv[i].chance;
    }
    // This is a cool algorithm for weighted random
    long weight = rand() % totWeight;
    for (u_int16_t i=0; i < inv.size(); i++) {
        weight -= inv[i].chance;
        if (weight <= 0) {
            return inv[i];
        }
    }
    return inv[0]; // This better not happen lol
}


