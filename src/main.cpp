#include "constants.h"
#include <cstdio>
#include <math.h>
#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>
#ifdef WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif
#include "gui.h"
#include "account.h"
#include "inventory.h"

int main(int argc, char** argv)
{
	// Create the main window
    sf::RenderWindow window(sf::VideoMode(800, 600), "Traveling Salesman");
    
    // Create a font
    sf::Font font;
    if (!font.loadFromFile("assets/cnr.otf"))
        return EXIT_FAILURE;
    sf::Text text("To Be Continued...", font, 50);
    
    // Create MessageBox
    MessageBox mb(font, 10, 16);
    mb.write("Hello World");
    mb.write("Lorem Ipsum");
    mb.write("MessageBox Height Is: " + std::to_string(mb.getHeight()));
    
    // Initialize Vendor List
    Inventory baselist;
    baselist.importFile("item_definitions/base.itm");
    std::vector<Vendor> vendors;
    vendors.push_back(Vendor("John"));
    vendors.push_back(Vendor("Paul"));
    vendors.push_back(Vendor("George"));
    vendors.push_back(Vendor("Ringo"));
    // So glad C++11 added a foreach
    // ^^^ This comment is now ironic, as the foreach loop apparently makes temporary references of some sort to classes so you can't change their data.
    // Oops, that was pretty dumb, but like also kinda sucks
    for (u_int16_t i=0; i<vendors.size(); i++) {
        vendors[i].generate(baselist);
    }
    
    std::cerr << "name: " << vendors[1].name;
    
    // Setup Inventory to merge into account
    Inventory playerInv;
    playerInv.importFile("item_definitions/player.itm");
    
    // Setup accounts
    Vendor playerAcc("player", 2500);
    playerAcc.merge(playerInv); // currently merge is the only way to indiscriminately add items to an account
    playerAcc.setPosition(200,50);
    playerAcc.numLines = 3;
    sf::Vector2f velocity(5, 0);
    
    // Create clock for delta-time
    sf::Clock deltaClock;
    sf::Time dt = deltaClock.restart(); // dt is delta time
    bool running = true;
    int selector = -1;
    
    // start game loop
    while (window.isOpen() && running) {
        // Process Events
        sf::Event event;
        while (window.pollEvent(event))
        {
            // Close window: exit
            if (event.type == sf::Event::Closed)
                window.close();
            // If mouse button is pressed, log the click location
            if (event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    mb.write("Click at x: " + std::to_string(event.mouseButton.x) + " y: " + std::to_string(600 - event.mouseButton.y), sf::Color(event.mouseButton.x/3,100,50));
                    velocity = velocity* -1.0f;
                }
            }
            // Handle key press events
            if (event.type == sf::Event::KeyPressed) {
                switch (event.key.code) {
                    case sf::Keyboard::W:
                        selector--;
                        selector = playerAcc.select(selector);
                        break;
                    case sf::Keyboard::S:
                        selector++;
                        selector = playerAcc.select(selector);
                        break;
                    case sf::Keyboard::V:
                        for (Vendor v: vendors) {
                            mb.write("Distance to " + v.name + " is " + std::to_string(v.dist(playerAcc)));
                            mb.write("\t to string: " + v.toString());
                        }
                        break;
                    case sf::Keyboard::L:
                        for (Vendor v: vendors)
                            mb.write(v.name + " is at " + v.getLocation());
                        break;
                    case sf::Keyboard::Q:
                        running = false;
                        break;
                    default:
                        // Compiler will complain if there isn't a default case.
                        break;
                }
            }
        }
        
        // Clear screen
        window.clear();
        
        // Draw the MessageBox and Account
        window.draw(mb);
        window.draw(playerAcc);
        // use delta time as seconds to move the length of the vector over a second
        playerAcc.move(velocity*dt.asSeconds());
        
        // Update Window
        window.display();
        dt = deltaClock.restart();
    }
    
    return EXIT_SUCCESS;
}
