#include <iostream>
#include <string>
#include <cstdlib>
#include "item.h"

using namespace std;

int main(int argc, char ** argv) {
	printf("Running Tests");
	
	Item a ("Stick", 10, 250, 4);
	Item b ("Pouch", 25, 80, 10);

	cout << a.serialize() << endl;
	cout << b.serialize() << endl;
	for (int i=0; i<6; i++){
		printf("Item %s generated price: %d\n", a.name.c_str(), a.genPrice());
		printf("Item %s generated price: %d\n", b.name.c_str(), b.genPrice());
	}

	//Exit peacefully
	printf("\n\n\n");
	return 0;
}
