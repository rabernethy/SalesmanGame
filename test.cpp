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

	Inventory inv1(2);
	inv1.add(a, 1);
	inv1.add(b, 1);

	Inventory inv2;
	inv2.add(a, 1);

	// Account tests:
	Account acc1(10000, inv1);
	Account acc2(10000, inv2);

	printf("\nBefore Transfer:\n");
	printf("Account 1: \n%s\n", acc1.toString().c_str());
	printf("Account 2: \n%s\n\n", acc2.toString().c_str());

	acc1.merge(acc2);
	// if(acc1.transferOut(acc2, b, 1))
	// 	printf("here\n");
	
	printf("\nAfter Transfer:\n");
	printf("Account 1: \n%s\n", acc1.toString().c_str());
	printf("Account 2: \n%s\n", acc2.toString().c_str());

	// Check if item addition works
	a = a + a;
	cout << "Item addition test: A="<< a.serialize() << endl;

	//Exit peacefully
	printf("\n\n\n");
	return 0;
}
