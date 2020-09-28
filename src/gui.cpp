#include "constants.h"
#include "gui.h"
#include <string>

MessageBox::MessageBox()
{
    for (u_int i=0; i<lines->size(); i++) {
        lines[i] = "";
    }
}

void MessageBox::draw()
{
    return;
}

void MessageBox::write(std::string s)
{
   return;
}


