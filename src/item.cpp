/* item.cpp, written by James Gottshall */

#include "item.h"
#include <string>
#include <cstdlib>
#include <cstdio>
#include <sstream>
#include <cctype>
#include <algorithm>
#include <iostream>
#include <vector>
#include "utils.h"

/*
Item(std::string iName, int iPrice, int iChance, int iFluctuation, int iQuantity):
	desc:
		--> creates an item object.
		--> object constructor.
		--> public method.
	inputs:
		--> std::string iName: the name of the item.
		--> int iPrice: the price of the item.
		--> int iChance: chance to spawn out of a hundred.
			* each vendor rolls to spawn items.
			* numbers over a hundred are more likely to be chosen mutliple times.
		--> int iFluctuation: the amount a price can fluctuate by.
		--> int iQuantity: the initial quantity of the item.
*/
Item::Item(std::string iName, int iPrice, int iChance, int iFluctuation, int iQuantity) {
	name = iName;
	chance = iChance;
	fluctuation = iFluctuation;
	quantity = iQuantity;
	srand(time(0));
    basePrice = iPrice;
    realPrice = iPrice;
}

/*
 * Constructor which builds an item from a serial string
 */
Item::Item(std::string serializedItem) {
    this->unserialize(serializedItem);
}

/*
serialize(void):
	desc:
		--> creates a serialized version of the item for printing to the screen.
		--> public method.
*/
std::string Item::serialize() {
	return name + "@" + std::to_string(basePrice) + "@" + std::to_string(chance) + "@" + std::to_string(fluctuation) + "@" 
    + std::to_string(quantity) + "@" + std::to_string(realPrice) + "@";
}

/*
unserialize(istr)
    desc:
        --> Converts a serialized item string into an item object
        --> Overwrites calling item object
        --> public method
        
 */
Item * Item::unserialize(const std::string& istr) {
    // split string into tokens based on the '@' delimiter
    std::vector<std::string> tokens = split(istr, '@');
    // stoi is by far my least favorite implementation of an int parser
    try {
        this->name = tokens[0];
        this->basePrice = std::stoi(tokens[1]);
        this->chance = std::stoi(tokens[2]);
        this->fluctuation = std::stoi(tokens[3]);
        this->quantity = std::stoi(tokens[4]);
        // To keep compatibility with item files made in the old format, ie: without realPrice
        if (tokens.size() > 5) {
            this->realPrice = std::stoi(tokens[5]);
        } else {
            this->realPrice = basePrice;
        }
    } catch (const std::exception& e){
        // I hope I never have to see this error again. stoi is a fickle mistress.
        std::cout << "stoi is being a bitch again: " << e.what() << std::endl;
    }
    return this;
}

/*
genPrice(void):
	desc: 
		--> generates the selling price of an item based on the items base price and the fluctuation.
		--> public method.
	output:
        --> sets realPrice to the fluctuated value
		--> returns an int that is the price for which an item is to be sold at.
*/
int Item::genPrice() {
    // I think there is probably a better function to fluctuate prices. TODO: write better function ;)
	realPrice = (rand() % 2) ? 1 : (-1) * (rand() % fluctuation) + basePrice;
    return realPrice;
}

/*
equals(Item item):
	desc:
		--> determines if two items are equal or not. the criteria is:
			* the items must have the same name.
		--> public method.
	input:
		--> Item item: the item to be compared agaginst.
	outputs:
		--> returns true if the items are the same.
		--> returns false if the items are not the same.
*/
bool Item::equals(Item item) {
	return name == item.name;
}

bool Item::operator==(const Item& b) {
	return this->name == b.name;
}

/*
totalCost(int quantity):
	desc:
		--> calculates the total cost of buy a quantity of item.
		--> can be passed a quantity greater than the actual quantity of the item.
		--> public method.
	input:
		--> int quantity: the quantity of item to calculate to cost of.
	output:
		--> returns the total cost of purchasing the desired quantity of item.
*/
int Item::totalCost(int quantity) {
	return realPrice * quantity;
}

// Adds item quantities together if they have the same name
Item Item::operator+(const Item& b) {
	if (*this == b) {
		this->quantity += b.quantity;
	}
	return *this;
}
