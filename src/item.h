#ifndef HEADER_ITEM
#define HEADER_ITEM
#include <string>
/*
   Defines an item class
   Provides an item generator that reads a .itm file
   Technically defines an itemstack not a single item, since quantity is included
*/
class Item {
	public:
		int basePrice; // item price
		int fluctuation; // An int that represents the amount the price can fluctuate, ie the final price could be any amount +/- this number
		int chance; // Chance to spawn out of a hundred, Each vendor rolls to spawn items and numbers over a hundred are more likely to be chosen mutliple times. Due to chance though items may spawn multiple times even when rare. (Implementation Dependent though, may change)
		int quantity; // number of items
		std::string name; // name of item
		int realPrice; // Price set by fluctuate

		Item(std::string name, int price, int chance, int fluctuation, int quantity); // constructor
        Item(std::string serializedItem); // serialized item constructor
        
		std::string serialize(); // serializes an item.
        Item * unserialize(const std::string& istr); // Unserializes an item string, then returns a pointer to the item
		int genPrice(); // generates the price of the item
		bool equals(Item item); // returns T/F if two items have the same name and price.
		int totalCost(int quantity); // returns the total cost of item based on the quantity passed.

		// Overridden Operators
		bool operator==(const Item& b);
		Item operator+(const Item& b);
	
};

#endif // !HEADER_ITEM
