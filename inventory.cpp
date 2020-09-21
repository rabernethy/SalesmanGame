/* inventory.cpp, written by Russell Abernethy */

#include "inventory.h"
#include "item.h"
#include <cstdlib>
#include <vector>

using namespace std;

Inventory::Inventory() {}
Inventory::Inventory(int maxCapacity) {
    cap = maxCapacity;
}

void Inventory::setCapacity(int newCapacity) {
    cap = newCapacity;
}

bool Inventory::add(Item item) {
    if(cap && inv.size() >= cap)
        return false;
    
    inv.push_back(item);
    return true;
}

bool Inventory::remove(Item item) {
    int j;
    for(auto i = inv.begin(); i != inv.end(); i++, j++) {
        if(inv[j].equals(item)) {
            inv.erase(i);
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
    std::string toReturn = "[";
    for(int i = 0; i < inv.size() - 1; i++)
        toReturn.append(inv[i].name + ", ");
    toReturn.append(inv[inv.size()-1].name + "]");
    return toReturn;
}