#include "constants.h"
#include <cstdio>
#include <math.h>
#include <SFML/Graphics.hpp>
#include <string>
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
    
    // Setup Inventory to merge into account
    Inventory playerInv;
    playerInv.importFile("item_definitions/player.itm");
    
    // Setup accounts
    Account playerAcc(2500);
    playerAcc.merge(playerInv); // currently merge is the only way to indiscriminately add items to an account
    playerAcc.setPosition(200,50);
    sf::Vector2f velocity(10,6);
    
    // Create clock for delta-time
    sf::Clock deltaClock;
    sf::Time dt = deltaClock.restart(); // dt is delta time
    
    // start game loop
    while (window.isOpen()) {
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
                    velocity = velocity* -1.5f;
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
