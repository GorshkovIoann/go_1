#include "chip.h"

Chip::Chip(Graph_lib::Window& win, Graph_lib::Point xy)
    : Circle(xy, size)
{
    win.attach(*this);
    own = &win;
}

WhiteChip::WhiteChip(Graph_lib::Window& win, Graph_lib::Point xy)
    : Chip(win, xy)
{
    set_fill_color(Graph_lib::Color::white);
    set_color(Graph_lib::Color::black);
}

BlackChip::BlackChip(Graph_lib::Window& win, Graph_lib::Point xy)
    : Chip(win, xy)
{   
    std::cout << 13 << std::endl;
    set_fill_color(Graph_lib::Color::black);
}

Chip::~Chip()
{
    own->detach(*this);
}