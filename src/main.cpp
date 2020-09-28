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
    
    // start game loop
    while (window.isOpen()) {
        // Process Events
        sf::Event event;
        while (window.pollEvent(event))
        {
            // Close window: exit
            if (event.type == sf::Event::Closed)
                window.close();
        }
        
        // Clear screen
        window.clear();
        
        // Draw the string
        window.draw(text);
        
        // Update Window
        window.display();
    }
    
    return EXIT_SUCCESS;
}
