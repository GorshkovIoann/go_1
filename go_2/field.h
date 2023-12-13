#pragma once

#include <Graph_lib/Graph.h>

class Field: public Graph_lib::Shape
{
public:
    void draw_lines() const override;
    void move(int dx, int dy) override;

    Field(Graph_lib::Point xy, int len0, int n);
private:
    Graph_lib::Vector_ref<Graph_lib::Line> lines;
};