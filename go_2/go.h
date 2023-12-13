#pragma once

#include <Graph_lib/GUI.h>
#include <Graph_lib/Graph.h>

#include "GameManager.h"
#include "field.h"
#include <iostream>

enum class State
{
    white,
    black,
    end_game,
};

class GO : public Graph_lib::Window
{
public:
    static constexpr int N = 9;
    static constexpr int width = (N + 1) * Cross::size;
    static constexpr int height = (N + 1) * Cross::size;
    const int x, y;

    GO(Graph_lib::Point p);

private:
    Graph_lib::Text w_score{Graph_lib::Point{40, 20}, "White score = 6.5"};
    Graph_lib::Text b_score{Graph_lib::Point{590, 20}, "BLack score = 0"};
    std::pair<int, int> last_white{-1, -1};
    std::pair<int, int> last_black{-1, -1};
    Crosses crosses;
    State state{State::black};
    Field field;
    Pass pass_button;
    bool was_pass{false};
    Game game_manager;

    void wait()
    {
        while (Fl::wait() && state != State::end_game)
        {
            Fl::redraw();
        }
        std::cout << "end";
    }

    static void cb_clicked(Graph_lib::Address, Graph_lib::Address widget)
    {
        auto &btn = Graph_lib::reference_to<Cross>(widget);
        dynamic_cast<GO &>(btn.window()).clicked(btn);
    }
    static void cb_pass(Graph_lib::Address, Graph_lib::Address widget)
    {
        auto &btn = Graph_lib::reference_to<Pass>(widget);
        dynamic_cast<GO &>(btn.window()).pass(btn);
    }
    void clicked(Cross &c);
    void pass(Pass &c);

    void hide_crosses();

    void delete_chips();
};