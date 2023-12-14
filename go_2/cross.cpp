#include "cross.h"
#include <iostream>
Cross::Cross(Graph_lib::Point xy, Graph_lib::Callback cb, int i, int j)
    : Widget({xy.x - size/4, xy.y - size/4}, size/2, size/2, "", cb),
    x{i},
    y{j}
{
}

void Cross::attach(Graph_lib::Window& win)
{
    pw = new My_button{loc.x, loc.y, width, height};
    pw->callback(reinterpret_cast<Fl_Callback*>(do_it), this);  // pass this widget
    own = &win;
    show();
}
void Cross::attach_chip (Chip& _chip)
{
    chip = &_chip;
    hide();
}
void Cross::attach_chip1 (ChipType type)
{   
    std::cout << 8 << std::endl;
    if (type == Black)
    {
        if (this->own)
        {
            std::cout << "sdklfkl";
        }
        chip = new BlackChip(*own, {loc.x+size/4, loc.y+size/4});
        std::cout << 10 << std::endl;
    }
    if (type == White)
    {
        chip = new WhiteChip(this->window(), {this->loc.x+Cross::size/4, this->loc.y+Cross::size/4});
    }
    
    hide();
}

void Cross::detach_chip ()
{
    delete chip;
    chip = nullptr;
    show();
}

Crosses::Crosses(Graph_lib::Point xy, int len0, int _n, Graph_lib::Callback cb)
    : Widget(xy, 0, 0, "", nullptr),
    n{_n}
{
    xy.x += len0;
    xy.y += 9 * len0;
    for (int i = 0; i < n; i++)
    for (int j = 0; j < n; j++)
    {
        crosses.push_back(new Cross({xy.x+i*len0, xy.y-j*len0}, cb, j+1, i+1));
    }
}

void Crosses::attach(Graph_lib::Window& win)
{
    for (int i = 0; i < crosses.size(); i++)
    {
        crosses[i].attach(win);
    }
    own = &win;
}

void Crosses::hide(std::vector<std::vector<bool>> h)
{
    for (int i = 0; i < n; i++)
    for (int j = 0; j < n; j++)
    {
        if (!h[i][j]) crosses[i*n+j].hide();
        else crosses[i*n+j].show(); 
    }
}

int Cross::get_state() const
{
    if (chip == nullptr)
        return 0;
    else
        return chip->is_black() ? 1 : 2;
}

void Crosses::destroy(std::vector<std::vector<bool>> d)
{
    for(int i = 0; i < n; i++)
    for(int j = 0; j < n; j++)
    {
        if (d[i][j]) crosses[i*n+j].detach_chip();
    }
}

std::vector<std::vector<int>> Crosses::get_state() const
{
    std::vector<std::vector<int>> a(n, std::vector<int>(n, 0));

    for (int i = 0; i < n; i++)
    for (int j = 0; j < n; j++)
    {
        a[i][j] = crosses[i*n+j].get_state();
    }

    return a;
}
