#ifndef HEADER_GUI
#define HEADER_GUI
#include <SFML/Graphics.hpp>
/*
Defines the control and message gui elements
*/
class MessageBox : public sf::Drawable {
    sf::RenderWindow win;
    sf::Font font;
    std::string * lines;
protected:
    void draw(sf::RenderTarget& target, sf::RenderStates state) const;
    
public:
    int size;
    // Creates a message box. Takes in a Window object, a Font object, and the amount of lines to display
    MessageBox(sf::Font ifont, int nlines); 
    void write(std::string s);
};

#endif // !HEADER_GUI
