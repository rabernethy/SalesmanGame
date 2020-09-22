/* account.cpp, written by Russell Abernethy */

#include "account.h"
#include "inventory.h"
#include <cstdlib>
#include <cstdio>

using namespace std;
/*
Account(int iBalance, Inventory iInventory):
    desc:
        --> creates an account object with an initial balance and inventory.
        --> object constructor.
        --> public method.
    inputs:
        --> int iBalance: the initial account balance.
        --> Inventory iInventory: the initial account inventory.
            * when passing, ensure you pass the right type of inventory (one with or without a max capacity).
            * it is ok if the initial inventory is empty.
*/
Account::Account(int iBalance, Inventory &iInventory) {
    balance = iBalance;
    inv = iInventory;
}

/*
Account(Inventory iInventory):
    desc:
        --> creates an account object with an initial inventory.
        --> the account's balance defaults to zero if not specified upon creation.
        --> object constructor.
        --> public method.
    input:
        --> Inventory iInventory: the initial account inventory.
            * when passing, ensure you pass the right type of inventory (one with or without a max capacity).
            * it is ok if the initial inventory is empty.
*/
Account::Account(Inventory &iInventory) {
    balance = 0;
    inv = iInventory;
}

/*
add(int value):
    desc:
        --> increases the account balance by the passed value.
        --> overloads the add method from the inventory class.
        --> private method.
    input:
        --> int value: the amount of money to be added to the account balance.
*/
void Account::add(int value) {
    balance += value;
}

/*
set(int value):
    desc:
        --> sets the account balance to the passed value.
        --> private method.
    input:
        --> int value: the amount of money
*/
void Account::set(int value) {
    balance = value;
}

/*
remove(int value):
    desc:
        --> decreases the account balance by the passed value.
        --> overloads the remove method from the inventory class.
        --> private method.
    input:
        --> int value: the amount of money to be removed from the account balance.
    output:
        --> returns the new account balance.
*/
int Account::remove(int value) {
    return balance -= value;
}

/*
checkBalance(void):
    desc:
        --> checks the current account balance.
        --> public method.
    output:
        --> returns the current account balance.
*/
int Account::checkBalance() {
    return balance;
}

/*
canBuy(Item item):
    desc:
        --> determines whether a single unit of an item can be bought.
        --> public method.
    input: 
        --> Item item: the item to be checked if it can be bought.
    outputs:
        --> returns true if the item can be bought.
        --> returns false if the item cannot be bought.
*/
bool Account::canBuy(Item item) {
    return canBuy(item, 1);
}

/*
canBuy(Item item, int quantity):
    desc:
        --> public method.
        --> determines whether the passed quantity of item can be purchased by the current account.
        --> overloaded method.
    inputs: 
        --> Item item: the item to be checked if it can be bought.
        --> int quantity: the desired number of item to be bought.
    outputs:
        --> returns true if the desired quantity of item can be bought.
        --> returns false if any of the following conditions are met:
            * the quantity passed is negative.
            * the quantity of item is less than the desired quantity to be bought.
            * the current account balance is less that the required amount to purchase the full number of items.
*/
bool Account::canBuy(Item item, int quantity) {
    return (quantity < 0) ? false : (quantity > item.quantity) ? false : (balance < item.price * quantity) ? false : true;
}

/*
transferIn(Account &from, Item &item, int quantity):
    desc:
        --> transfers item(s) from a forign account into the current account.
        --> public method.
    inputs:
        --> Account &from: the account where the item(s) are coming from.
        --> Item &item: the item to be transfered into the current account.
        --> int quantity: the desired quantity of the passed item to be transfered into the current account.
    outputs:
        --> returns true when the transefer is successful.
        --> returns false if the transfer could not take place for any of the following reasons:
            * the item does not exist in the from account.
            * the current account does not have the funds to buy the item(s).
            * the current account does not have enough space to buy the item(s).
*/
bool Account::transferIn(Account &from, Item &item, int quantity) {
    return (from.inv.contains(item) == -1) ? false : (!canBuy(item, quantity)) ? false : moveIn(from, item, quantity);
}

/*
transferOut(Account &to, Item &item, int quantity):
    desc:
        --> transefers item(s) from the current account into a foreign account.
        --> public method.
    inputs:
        --> Account &to: the account where the item(s) are going to.
        --> Item &item: the item to be transfered out of the current account.
        --> int quantity: the desired quantity of the passed item to be transfered out of the current account.
    outputs:
        --> returns true when the transfer is successful.
        --> returns false if the transefer could not take place for any of the following reasons:
            * the item does not exist in the current account.
            * the to account does not have the funds the buy the item(s).
            * the to account does not have enough space to buy the item(s).
*/
bool Account::transferOut(Account &to, Item &item, int quantity) {
    return (inv.contains(item) == -1) ? false : (!to.canBuy(item, quantity)) ? false : moveOut(to, item, quantity);
}

/*
toString(void):
    desc: 
        --> creates a string representation of the account.
        --> public method.
    output:
        --> returns string that contains relevant infomation about the account including:
            * the balance of the account.
            * the current inventory in the account.
*/
std::string Account::toString() {
    std::string toReturn = "Balance: " + std::to_string(balance);
    toReturn.append("\nInventory: " + inv.toString());
    return toReturn;
}

/*
moveIn(Account &from, Item &item, int quantity):
    desc:
        --> moves item(s) into an account from a foreign account.
        --> changes the balances of both accounts to reflect the transaction.
        --> private method.
    inputs:
        --> Account &from: the account where the item(s) are coming from.
        --> Item &item: the item to be transfered into the current account.
        --> int quantity: the desired quantity of the passed item to be transfered into the current account.
    output:
        --> returns true.
*/
bool Account::moveIn(Account &from, Item &item, int quantity) {
    inv.add(item, quantity);
    remove(item.totalCost(quantity));
    from.add(item.totalCost(quantity));
    from.inv.remove(item, quantity);
    return true;
}

/*
moveOut(Account &to, Item &item, int quantity)
    desc:
        --> move item(s) from the current account into a foreign account.
        --> changes the balance of both accounts to reflect the transaction.
        --> private method.
    inputs:
        --> Account &to: the account where the item(s) are going to.
        --> Item &item: the item to be transfered from the current account.
        --> int quantity: the desired quantity of the passed item to be transfered into the current account.
    output:
        --> returns true.
*/
bool Account::moveOut(Account &to, Item &item, int quantity) {
    to.inv.add(item, quantity);
    to.remove(item.totalCost(quantity));
    add(item.totalCost(quantity));
    inv.remove(item, quantity);
    return true;
}