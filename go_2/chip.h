#pragma once

#include <Graph_lib/Graph.h>
#include <Graph_lib/GUI.h>
#include <iostream>

enum ChipType
{
    None = 0,
    Black = 1,
    White = 2
};

class Chip: public Graph_lib::Circle
{
public:
    static constexpr int size = 30;

    virtual bool is_black() const = 0;

    Chip(Graph_lib::Window& win, Graph_lib::Point xy);

    ~Chip();
private:
    Graph_lib::Window *own;

};

class WhiteChip: public Chip
{
public:
    WhiteChip(Graph_lib::Window& win, Graph_lib::Point xy);

    bool is_black() const override { return false; }
};

class BlackChip: public Chip
{
public:
    BlackChip(Graph_lib::Window& win, Graph_lib::Point xy);

    bool is_black() const override { return true; }
};