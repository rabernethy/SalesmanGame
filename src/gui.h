#ifndef HEADER_GUI
#define HEADER_GUI
#include <SFML/Graphics.hpp>
#include "constants.h"
/*
Defines the control and message gui elements
*/

class MessageBox : public sf::Drawable {
    sf::RenderWindow win;
    sf::Font font;
    std::string * lines;
    sf::Color * colors; // Line colors
    int size;
protected:
    void draw(sf::RenderTarget& target, sf::RenderStates state) const;
    
public:
    int fontsize;
    sf::Color defaultColor; // The default color to draw text. Defaults to white.
    // Creates a message box. Takes in a Font object, the amount of lines to display, and the fontsize
    MessageBox(sf::Font ifont, int nlines, int ifontsize);
    ~MessageBox(); // Destructor Function
    
    void write(std::string s);
    void write(std::string s, sf::Color c);
    int getHeight();
};

#endif // !HEADER_GUI
