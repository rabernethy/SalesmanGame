#ifndef HEADER_ITEM
#define HEADER_ITEM
#include <string>
/*
   Defines an item class
   Provides an item generator that reads a .itm file
*/
class Item {
	public:
		int price; // item price
		int fluctuation; // An int that represents the amount the price can fluctuate, ie the final price could be any amount +/- this number
		int chance; // Chance to spawn out of a hundred, Each vendor rolls to spawn items and numbers over a hundred are more likely to be chosen mutliple times. Due to chance though items may spawn multiple times even when rare. (Implementation Dependent though, may change)
		int quantity; // number of items
		std::string name; // name of item

		Item(std::string name, int price, int chance, int fluctuation, int quantity); // constructor
		std::string serialize(); // serializes an item.
		int genPrice(); // generates the price of the item
		bool equals(Item item); // returns T/F if two items have the same name and price.
		int totalCost(int quantity); // returns the total cost of item based on the quantity passed.
};

#endif // !HEADER_ITEM
