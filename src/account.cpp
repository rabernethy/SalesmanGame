/* account.cpp, written by Russell Abernethy */
/* Improved by James Gottshall :) */

#include "account.h"
#include "inventory.h"
#include <cstdlib>
#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cmath>

using namespace std;
/*
Account(int iBalance, Inventory iInventory):
    desc:
        --> MASTER CONSTRUCTOR
        --> creates an account object with an initial balance and inventory.
        --> object constructor.
        --> public method.
    inputs:
        --> int iBalance: the initial account balance.
    README: Account used to have an inventory variable but account, IS an inventory so it does not need a variable for one as well. This will likely break things.
*/
Account::Account(int iBalance) {
    balance = iBalance;
    
    // Set/load defaults
    if (!font.loadFromFile("assets/cnr.otf")) // Should probably replace this with a constant, as in the font path
        throw "Font File Not Found!";
    numLines = 12;
    fontsize = 16;
    selected = -1; // None selected by default
}

// This syntax is strange, not sure if I like it
Account::Account() : Account{0} {}


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
    return canBuy(item, item.quantity);
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
    return (quantity < 0) ? false : (quantity > item.quantity) ? false : (balance < item.basePrice * quantity) ? false : true;
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
bool Account::transferIn(Account &from, Item item, int quantity) {
    return (from.contains(item) == -1) ? false : (!canBuy(item, quantity)) ? false : moveIn(from, item, quantity);
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
bool Account::transferOut(Account &to, Item item, int quantity) {
    return (contains(item) == -1) ? false : (!to.canBuy(item, quantity)) ? false : moveOut(to, item, quantity);
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
    toReturn.append("\nInventory: " + Inventory::toString());
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
// TODO: add(Item, quantity) is deprecated
bool Account::moveIn(Account &from, Item item, int quantity) {
    Inventory::add(item, quantity);
    remove(item.totalCost(quantity));
    from.add(item.totalCost(quantity));
    Inventory::remove(item, quantity);
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
// TODO: @Russell add(Item, quantity) is deprecated
bool Account::moveOut(Account &to, Item item, int quantity) {
    Inventory::add(item, quantity);
    to.remove(item.totalCost(quantity));
    add(item.totalCost(quantity));
    Inventory::remove(item, quantity);
    return true;
}

/*
merge(Account &toCombine):
    desc:
        --> merges the funds and inventories of two accounts.
        --> public method.
    input: 
        -->Account &toCombine: the account to merge into the current account.
    outputs:
        --> returns true if successful.
        --> returns false if the merge wasn't possible.
*/
// NOTE: please do not destroy or edit other things in functions, pretty sure that's what's causing these bugs
bool Account::merge(Account toCombine) {
    if(!Inventory::merge(toCombine))
        return false;
    add(toCombine.balance);
    //toCombine.set(0); Wonder if this helps...
    return true;
} 

// Inventory merge
bool Account::merge(Inventory toCombine)
{
    return Inventory::merge(toCombine);
}


/*
 * Setters for offset
 */
// Shifts offset "up" if it is greater then 0
bool Account::shiftUp() {
    if (offset == 0) {
        return false;
    }
    offset--;
    return true;
}

// Shifts the offset down if there is room to be shifted
bool Account::shiftDown()
{
    if (offset >= Inventory::inv.size()) {
        return false;
    }
    offset++;
    return true;
}

// draw function. I'm curious to see how easily I can move this object around in testing.
// Future Jimmy - I played around with moving the accounts and needless to say it was pretty awesome
void Account::draw(sf::RenderTarget& target, sf::RenderStates state) const
{
    // apply the entity's transform
    state.transform *= getTransform();
    // Draw the entire item
    for (int i=0; i < std::min((int)numLines, getSlots()); i++) {
        // Create Text
        sf::Text txt(inv[i].name + " x" + std::to_string(inv[i].quantity), font, fontsize);
        // Position text
        txt.setPosition(0, i * fontsize);
        // If selected element then draw selection rectangle
        if (selected == i){
            sf::Rect<float> lb = txt.getLocalBounds();
            // txt.getLocalBounds() returns a rect object that apparently can't be drawn as a rectangle
            // Very frustrating
            sf::RectangleShape selRec(sf::Vector2f(lb.width + 4, lb.height));
            selRec.setPosition(-1, i * fontsize + lb.height / 2); // set position so the rectangle actually draws behind the text
            selRec.setFillColor(sf::Color::Red); // Set selector color
            target.draw(selRec, state); // Draw the Rectangle
        }
        // draw text
        target.draw(txt, state);
    }
}

bool Account::populate(Inventory genList, int iterations)
{
    // Add items to self
    for (int i=0; i<iterations; i++) {
        if (!Inventory::add(genList.randItem())) {
            // cerr, probably easier to use this then implement some fancy pants logging
            std::cerr << "Failed to Add item when populating Account" << std::endl;
            return false;
        }
    }
    return true;
}


// Vendor just stores a representation of a Vendor
Vendor::Vendor(std::string name, sf::Vector2i location)
{
    this->name = name;
    this->location = location;
}

Vendor::Vendor(std::string name)
{
    this->name = name;
}

// wrapper function to generate Vendor data
bool Vendor::generate(Inventory genList, int iterations, int maxdist)
{
    newLocation(maxdist);
    return populate(genList, iterations);
}

// Distance between Vendor and given vector
int Vendor::dist(sf::Vector2i v)
{
    return sqrt(pow(v.x-location.x, 2) + pow(v.y-location.y,2));
}

// Distance between self and another Vendor
int Vendor::dist(Vendor v)
{
    return dist(v.location);
}

// generate new location within maxdist from [0,0]
void Vendor::newLocation(int maxdist)
{
    sf::Vector2i zero(0,0);
    // Generate random vectors bounded by maxdist until one is within the maxdist range, hopefully this doesn't hang
    do {
        location = sf::Vector2i(rand() % maxdist, rand() % maxdist);
    } while (dist(zero) > maxdist);
}



