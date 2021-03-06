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
        // Inventory inv;
        void add(int value); // add funds to balance.
        void set(int value); // sets the account balance to the passed double.
        int remove(int value); // remove funds from balance.
        bool moveIn(Account &from, Item item, int quantity); // helper method to move items into current account. Always returns true.
        bool moveOut(Account &to, Item item, int quantity); // helper method to move items into a different account. Always returns true.
        u_int offset; // offset in the list, for display purposes
        int selected; // Selected inventory space. Set to -1 for none.
        
        // This is protected since the window management system does some funky stuff with this. IDK RTFM.
protected:
    void draw(sf::RenderTarget& target, sf::RenderStates state) const;
    int balance;

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
        bool populate(Inventory genList, int iterations = 10); // picks itemStacks from genList based on the random Inventory item function, and populates the list with as many itemStacks specified by iterations
        
        // Display related members
        sf::Font font; // Leaving this public incase someone wants to edit, but it'll be our default font (CNR) unless changed
        u_int numLines; // amount of lines of items to draw - default: 12
        u_int fontsize; // Fontsize to draw the inventory items - default: 16
        bool shiftUp(); // Moves offset up
        bool shiftDown(); // Moves offset down
        int select(int index); // select item, returns the actual index selected
};

class Vendor: public Account {
public:
    sf::Vector2i location;
    Vendor(std::string name, sf::Vector2i location);
    Vendor(std::string name, int balance = 0);
    std::string name;
    bool generate(Inventory genList, int iterations = 10, int maxdist = 50); // runs Account::populate and generates a random vector location
    int dist(Vendor v); // get distance to vendor
    int dist(sf::Vector2i v); //get distance to vector
    void newLocation(int maxdist); // generate a new Vector with a maximum distance from [0,0]
    std::string getLocation(); // returns string of location, for debug purposes
};

#endif // !HEADER_ACCOUNT
