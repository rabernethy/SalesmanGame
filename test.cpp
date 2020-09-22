#include <iostream>
#include <string>
#include <cstdlib>
#include "item.h"
#include "inventory.h"
#include "account.h"


using namespace std;

int main(int argc, char ** argv) {
	printf("Running Tests\n");
	
	// Item tests:

	Item a ("Stick", 10, 250, 4, 1);
	Item b ("Pouch", 25, 80, 10, 1);

	cout << a.serialize() << endl;
	cout << b.serialize() << endl;
	
	// Inventory tests:

	Inventory inv;
	inv.add(a, 1);
	inv.add(b, 1);

	// Account tests:
	Account acc1(10000, inv);
	Account acc2(1000);

	printf("Account 1: \n%s\n", acc1.toString().c_str());
	printf("Account 2: \n%s\n", acc2.toString().c_str());


	//Exit peacefully
	printf("\n\n\n");
	return 0;
}