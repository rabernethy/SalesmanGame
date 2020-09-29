#include "constants.h"
#include "gui.h"
#include <string>
#include <SFML/Graphics.hpp>

MessageBox::MessageBox(sf::Font ifont, int nlines)
{
    font = ifont;
    size = nlines;
    lines = new std::string[size];
}

void MessageBox::write(std::string s)
{
    for (int i=size-1; i>0; i--) {
        lines[i] = lines[i-1];
    }
    lines[0] = s;
}

void MessageBox::draw(sf::RenderTarget& target, sf::RenderStates state) const
{
    int fontsize = 18;
    sf::Vector2u screenSize = target.getSize();
    for (int i=0; i<size; i++) {
        sf::Text text(lines[i], font, fontsize);
        text.setPosition(0, screenSize.y - (i + 1) *fontsize - 2);
        target.draw(text);
    }
}

