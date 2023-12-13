#pragma once

#include "chip.h"

class My_button : public Fl_Button
{
public:
    My_button(int x, int y, int width, int height) : Fl_Button{x, y, width, height} {}
    void draw() override {}
};

class Pass : public Graph_lib::Button
{
public:
    Pass(Graph_lib::Point xy, int w, int h, const std::string label, Graph_lib::Callback cb) : Button{xy, w, h, label, cb} {}

    void change_color(bool black) // true - если ход у черных, false - у белых
    {
        if (black)
            pw->color(FL_BLACK), pw->labelcolor(FL_WHITE);
        else
            pw->color(FL_WHITE), pw->labelcolor(FL_BLACK);
    }
};

class Cross : public Graph_lib::Widget
{
public:
    const int x, y;
    static int constexpr size = 75;

    Cross(Graph_lib::Point xy, Graph_lib::Callback cb, int i, int j);

    void attach(Graph_lib::Window& win) override;
    void attach_chip (Chip& _chip);
    void attach_chip1 (ChipType type);
    void detach_chip ();

    int get_state() const;
    int get_id() {return 2*x + 34*y - 36;};

private:
    Chip* chip{nullptr};

};

class Crosses : public Graph_lib::Widget
{
public:
    Crosses(Graph_lib::Point xy, int len0, int n, Graph_lib::Callback cb);

    void attach(Graph_lib::Window& win) override;
    void hide(std::vector<std::vector<bool>>);

    std::vector<std::vector<int>> get_state() const;

    void destroy(std::vector<std::vector<bool>>); 

    Graph_lib::Vector_ref<Cross>& get_crosses(){return crosses;};
private:
    const int n;
    Graph_lib::Vector_ref<Cross> crosses;
};