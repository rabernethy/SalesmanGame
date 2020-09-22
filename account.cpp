/* account.cpp, written by Russell Abernethy */

#include "account.h"
#include "inventory.h"
#include <cstdlib>
#include <cstdio>

using namespace std;

Account::Account(int iBalance, Inventory iInventory) {
    balance = iBalance;
    inv = iInventory;
}

Account::Account(Inventory iInventory) {
    balance = 0;
    inv = iInventory;
}

void Account::add(int value) {
    balance += value;
}

void Account::set(int value) {
    balance = value;
}

int Account::remove(int value) {
    balance -= value;
    return balance;
}

int Account::checkBalance() {
    return balance;
}

bool Account::canBuy(Item item) {
    return canBuy(item, 1);
}

bool Account::canBuy(Item item, int quantity) {
    // you cannot buy a negative number of items, that's called selling.
    if(quantity < 0)
        return false;
    // not enought items to sell
    if(quantity > item.quantity)
        return false;
    // total cost excedes the current balance
    if(balance < item.price * quantity)
        return false;
    return true;    
}

bool Account::transferIn(Account from, Item item, int quantity) {
    // check if the item can be bought.
    if(!canBuy(item, quantity))
        return false;
    // move items from one inventory to another.
    inv.add(item, quantity);
    remove(item.totalCost(quantity));
    from.add(item.totalCost(quantity));
    from.inv.remove(item, quantity);
    return true;
}

bool Account::transferOut(Account to, Item item, int quantity) {
    // check if the receiving account has enought money to buy the item(s).
    if(!to.canBuy(item, quantity))
        return false;
    // move items from one inventory to another.
    to.inv.add(item, quantity);
    to.remove(item.totalCost(quantity));
    add(item.totalCost(quantity));
    inv.remove(item, quantity);
    return true;
}

std::string Account::toString() {
    std::string toReturn = "Balance: " + std::to_string(balance);
    toReturn.append("\nInventory: " + inv.toString());
    return toReturn;
}
