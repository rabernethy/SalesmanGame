#ifndef HEADER_INVENTORY
#define HEADER_INVENTORY
#include <vector>
#include <string>
#include "item.h"
/*
Manages a list of items, as well as provides inventory helper functions
*/
class Inventory {
    protected:
        std::vector<Item> inv; // vector to keep track of items.
    private:
        int cap; // max num items allowed in an inventory.
        int size; // num items in the inventory.
    public:
        Inventory(); // constructor for bottomless inventory.
        Inventory(int maxCapacity); // constructor for limited inventory.
        int numItems(); // returns the number of items in the inventory.
        void setCapacity(int newCapacity); // changes the capacity to the passed in.
        bool add(Item item); // adds an item to the inventory.
        bool add(Item item, int quantity); // adds mutiple items to an inventory.
        bool remove(Item item); // removes an item from the inventory.
        bool remove(Item item, int quantity); // removes multiple items from an inventory.
        int contains(Item item); // returns the index of the item or -1 if not found.
        std::string toString(); // returns a string representation of the inventory.
};
#endif // !HEADER_INVENTORY
