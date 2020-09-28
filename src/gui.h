#ifndef HEADER_GUI
#define HEADER_GUI
/*
Defines the control and message gui elements
*/
class MessageBox {
    std::string lines[HEIGHT/3];
    void draw();
public:
    MessageBox();
    void write(std::string s);
};

#endif // !HEADER_GUI
