/* item.cpp, written by James Gottshall */

#include "item.h"
#include <string>
#include <cstdlib>
#include <cstdio>

// Implementation of item.h
using namespace std;

Item::Item(std::string iname, int iprice, int ichance, int ifluctuation, int iquantity) {
	name = iname;
	price = iprice;
	chance = ichance;
	fluctuation = ifluctuation;
	quantity = iquantity;
	srand(time(0));
}

std::string Item::serialize() {
	return name + "@" + to_string(price) + "@" + to_string(chance) + "@" + to_string(fluctuation);
}

// Generates the price based on the fluctuation
int Item::genPrice() {
	return (rand()%2) ? (1):(-1) * (rand() % fluctuation) + price;
}

bool Item::equals(Item item) {
	if(name != item.name)
		return false;
	return true;
}

int Item::totalCost(int quantity) {
	return price * quantity;
}