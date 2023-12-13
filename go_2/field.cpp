#include "field.h"

Field::Field (Graph_lib::Point xy, int len0, int n)
    : Shape()
{
    xy.x += len0;
    xy.y += len0;
    for (int i = 0; i < n; i++)
        lines.push_back(new Graph_lib::Line(
            {xy.x + len0 * i, xy.y},
            {xy.x + len0 * i, xy.y + len0 * (n - 1)}
        ));

    for (int i = 0; i < n; i++)
        lines.push_back(new Graph_lib::Line(
            {xy.x, xy.y + len0 * i},
            {xy.x + len0 * (n - 1), xy.y + len0 * i}
        ));
    set_color(Graph_lib::Color::black);
    set_fill_color(Graph_lib::Color::black);
}

void Field::draw_lines() const
{
    for (int i = 0; i < lines.size(); i++)
        lines[i].draw();
}

void Field::move(int dx, int dy)
{
    for (int i = 0; i < lines.size(); i++)
        lines[i].move(dx, dy);
}