#ifndef HEADER_ACCOUNT
#define HEADER_ACCOUNT 
#include "inventory.h"
#include <SFML/Graphics.hpp>
/*
Account stores the amount of money a trader has
As well it provides helper functions for withdrawing and depositing
cash between accounts
*/

class Account: protected Inventory, public sf::Drawable, public sf::Transformable {
    private:
        int balance;
        // Inventory inv;
        void add(int value); // add funds to balance.
        void set(int value); // sets the account balance to the passed double.
        int remove(int value); // remove funds from balance.
        bool moveIn(Account &from, Item item, int quantity); // helper method to move items into current account. Always returns true.
        bool moveOut(Account &to, Item item, int quantity); // helper method to move items into a different account. Always returns true.
        u_int offset; // offset in the list, for display purposes

        // This is protected since the window management system does some funky stuff with this. IDK RTFM.
protected:
    void draw(sf::RenderTarget& target, sf::RenderStates state) const;

public:
        Account(int iBalance); // constructor when there is
        Account(); // constructs an account with a balance of zero.
        std::string toString(); // returns a string representation of the account.
        int checkBalance(); // returns the current balance.
        bool canBuy(Item item, int quantity); // returns T/F if there is enough currency to buy the desired number of items.
        bool canBuy(Item item); // returns T/F if there is enough currency to buy one of the passed item.
        bool transferIn(Account &from, Item item, int quantity); // moves item(s) from another account to the current account if possible.
        bool transferOut(Account &to, Item item, int quantity); // moves item(s) from current account to another account if possible.
        bool merge(Account toCombine); //merges two accounts together if possible.
        bool merge(Inventory toCombine); // merges inventory with account using inventory merge function
        
        // Display related members
        sf::Font font; // Leaving this public incase someone wants to edit, but it'll be our default font (CNR) unless changed
        u_int numLines; // amount of lines of items to draw - default: 12
        u_int fontsize; // Fontsize to draw the inventory items - default: 16
        bool shiftUp(); // Moves offset up
        bool shiftDown(); // Moves offset down
        int selected; // Selected inventory space. Set to -1 for none.
};

class Vendor: public Account {
public:
    Vendor(std::string name, sf::Vector2i location);
    Vendor(std::string name);
    sf::Vector2i location;
    std::string name;
};

#endif // !HEADER_ACCOUNT
