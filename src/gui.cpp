#include "constants.h"
#include "gui.h"
#include <string>
#include <SFML/Graphics.hpp>

// Constructor
MessageBox::MessageBox(sf::Font font, int nlines, int fontsize)
{
    this->font = font;
    this->fontsize = fontsize;
    size = nlines;
    lines = new std::string[size]; // Allocate lines based on size.
    colors = new sf::Color[size]; // Allocate array for storing the color of each line
    defaultColor = sf::Color::White;
}

// Deconstructor function
MessageBox::~MessageBox()
{
    delete[] lines; // This is the proper way to delete arrays. I tried others and it core dumped.
    delete[] colors;
}

// write without color
void MessageBox::write(std::string s)
{
    this->write(s, defaultColor);
}

// write with color
void MessageBox::write(std::string s, sf::Color c)
{
    std::size_t found = s.find("\n");
    if (found!=std::string::npos) {
        write(s.substr(found+1), c);
        s = s.substr(0, found);
    }
    // Shift lines up one index
    for (int i=size-1; i>0; i--) {
        lines[i] = lines[i-1];
        colors[i] = colors[i - 1];
    }
    lines[0] = s; // Add new string
    colors[0] = c; // Add new color
}


void MessageBox::draw(sf::RenderTarget& target, sf::RenderStates state) const
{
    int fontsize = 18; // Fontsize for the drawn text
    
    // Set screenSize to the size of the target. Target will generally be the main window
    sf::Vector2u screenSize = target.getSize();
    
    // Draw lines from the bottom up
    for (int i=0; i<size; i++) {
        sf::Text text(lines[i], font, fontsize); // Allocate text object from font
        // Draw text starting from the bottom of the screen
        text.setPosition(0, screenSize.y - (i + 1) *fontsize - 2);
        // Set text color
        text.setFillColor(colors[i]);
        // draw text object
        target.draw(text);
    }
}

int MessageBox::getHeight()
{
    return size * fontsize + 2; // +2 is for the adjusment added from the bottom
}


