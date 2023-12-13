#pragma once

#include "rules.h"

class Game
{
public:
    Game();
    void clicked(int id);
    void set_stones(Crosses &crosse);
    Rules &get_board() { return board; };
    int pass_count;

private:
    Rules board;
    Graph_lib::Vector_ref<Cell> stones;
};