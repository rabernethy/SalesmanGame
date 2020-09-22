#ifndef HEADER_ACCOUNT
#define HEADER_ACCOUNT 
#include "inventory.h"
/*
Account stores the amount of money a trader has
As well it provides helper functions for withdrawing and depositing
cash between accounts
*/

class Account: public Inventory {
    private:
        int balance;
        Inventory inv;
    public:
        // constructors for different possiblities.
        Account(int iBalance, Inventory iInventory);
        Account(int iBalance);
        Account(Inventory iInventory);
        Account(); // initilizes an empty account
        std::string toString(); // returns a string representation of the account.
        void add(int value); // add funds to balance.
        void set(int value); // sets the account balance to the passed double.
        int remove(int value); // remove funds from balance.
        int checkBalance(); // returns the current balance.
        bool canBuy(Item item, int quantity); // returns T/F if there is enough currency to buy the desired number of items.
        bool canBuy(Item item); // returns T/F if there is enough currency to buy one of the passed item.
        bool transferIn(Account from, Item item, int quantity); // moves item(s) from another account to the current account if possible.
        bool transferOut(Account dest, Item item, int quantity); // moves item(s) from current account to another account if possible.
};
#endif // !HEADER_ACCOUNT
