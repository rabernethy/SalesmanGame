#ifndef HEADER_ITEM
#define HEADER_ITEM
#include <string>
/*
   Defines an item class
   Provides an item generator that reads a .itm file
*/
class Item {
	public:
	int price;
	int fluctuation; // An int that represents the amount the price can fluctuate, ie the final price could be any amount +/- this number
	int chance; // Chance to spawn out of a hundred, Each vendor rolls to spawn items and numbers over a hundred are more likely to be chosen mutliple times. Due to chance though items may spawn multiple times even when rare. (Implementation Dependent though, may change)
	std::string name;

	Item(std::string name, int price, int chance, int fluctuation);
	std::string serialize();
	int genPrice();
	bool equals(Item item);
};

#endif // !HEADER_ITEM
