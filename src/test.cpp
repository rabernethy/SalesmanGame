#include <iostream>
#include <string>
#include <cstdlib>
#include "item.h"
#include "inventory.h"
#include "account.h"
#include "constants.h"


using namespace std;

void testSerial() {
    cout << "Running Serialization Tests" << endl;
    Item a ("Clock", 32, 48, 3, 6);
    cout << "Serialized: " << a.serialize() << endl;
    Item b (a.serialize());
    cout << "Item b, made with unserialize: " << b.serialize() << endl;
    cout << "ending serialization tests" << endl;
}

int main(int argc, char ** argv) {
	printf("Running Tests\n");
	
	// Item tests:

	Item a ("Stick", 10, 250, 4, 1);
	Item b ("Pouch", 25, 80, 10, 1);

	cout << a.serialize() << endl;
	cout << b.serialize() << endl;
	testSerial();
    
	// Inventory tests:

	Inventory inv1;
	inv1.add(a);
	inv1.add(b);

	Inventory inv2;
	inv2.add(a);
    
    // Is it Inventory or account making problems?
    cout << "Inventory 1: " << inv1.toString() << ", Inventory 2: " << inv2.toString() << endl;
    
    // Try an inventory merge to see if that's where the issue is
    inv1.merge(inv2);
    cout << "Merge test: " << inv1.toString() << endl;

    // Import test
    Inventory invImport;
    if (!invImport.importFile("base.itm"))
        cout << "Import Failed" << endl;
    cout << "Imported Inventory: " << invImport.toString() << endl;
    cout << "Inventory size: " << invImport.numItems() << endl;
    
	// Account tests:
	Account acc1(10000);
	Account acc2(10000);
    
    // Because of inheritance this should work to initialize inventories
    acc1.merge(inv1);
    acc2.merge(inv2);

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

    inv1.exportFile("base.itm");
    
	//Exit peacefully
	printf("\n\n\n");
	return 0;
}


