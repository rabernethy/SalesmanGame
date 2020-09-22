/* inventory.cpp, written by Russell Abernethy */

#include "inventory.h"
#include "item.h"
#include <cstdlib>
#include <vector>

using namespace std;

Inventory::Inventory() {
    size = 0;
}
Inventory::Inventory(int maxCapacity) {
    cap = maxCapacity;
    size = 0;
}

int Inventory::numItems() {
    return size;
}

void Inventory::setCapacity(int newCapacity) {
    cap = newCapacity;
}

bool Inventory::add(Item item) {
    return add(item, item.quantity);
}
bool Inventory::add(Item item, int quantity) {
    if(cap && numItems() + quantity >= cap)
        return false;
    // if the item already exists in inv, change quantity insead of adding the item.
    if(contains(item) != -1) {
        inv[contains(item)].quantity += quantity;
        return true;
    }
    inv.push_back(item);
    size += quantity;
    return true;
}

bool Inventory::remove(Item item) {
    return remove(item, 1);
}

bool Inventory::remove(Item item, int quantity) {
    int j = 0;
    for(auto i = inv.begin(); i != inv.end(); i++, j++) {
        if(inv[j].equals(item)) {
            if(quantity - item.quantity > 0)
                item.quantity -= quantity;
            else
                inv.erase(i);    
            size -= item.quantity;
            return true;
        }
    }
    return false;
}

int Inventory::contains(Item item) {
    for(int i = 0; i < inv.size(); i++) {
        if(inv[i].equals(item))
            return i;
    }
    return -1;
}

std::string Inventory::toString() {
    if(inv.size() == 0)
        return "[ ]";
    std::string toReturn = "[";
    for(int i = 0; i < inv.size() - 1; i++)
        toReturn.append(inv[i].name + ", ");
    toReturn.append(inv[inv.size()-1].name);
    return toReturn + "]";
}