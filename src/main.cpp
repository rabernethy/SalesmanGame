#include "constants.h"
#include <cstdio>
#include <SFML/Graphics.hpp>
#include <string>
#ifdef WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif
#include "gui.h"

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
                if (event.mouseButton.button == sf::Mouse::Left)
                    mb.write("Click at x: " + std::to_string(event.mouseButton.x) + " y: " + std::to_string(600 - event.mouseButton.y), sf::Color(event.mouseButton.x/3,100,50));
            }
        }
        
        // Clear screen
        window.clear();
        
        // Draw the string
        window.draw(mb);
        
        // Update Window
        window.display();
    }
    
    return EXIT_SUCCESS;
}
