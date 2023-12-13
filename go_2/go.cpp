#include <iostream>

#include "go.h"

GO::GO(Graph_lib::Point xy)
    : Graph_lib::Window(width, height, "GO"),
      field{xy, Cross::size, N},
      crosses{Crosses(xy, Cross::size, N, cb_clicked)},
      x{xy.x + Cross::size},
      y{xy.y + Cross::size},
      pass_button{{width / 2 - Cross::size / 2, Cross::size / 4}, Cross::size, Cross::size / 2, "pass", cb_pass},
      game_manager{Game()}
{
    game_manager.set_stones(crosses);
    pass_button.attach(*this);
    attach(pass_button);
    attach(w_score);
    attach(b_score);
    pass_button.change_color(true);

    crosses.attach(*this);
    attach(crosses);

    color(fl_rgb_color(char(255), char(222), char(173)));
    this->attach(field);

    // Fl::redraw();
    // wait();
}

void GO::clicked(Cross &c)
{
    // Здесь будет код, запрашивающий у GameManager'а разрешение поменять поле
    // c.attach_chip(*(new WhiteChip(*window, {c.loc.x+Cross::size/4, c.loc.y+Cross::size/4})));
    // он считает, что делать и у себя меняет положение
    switch (state)
    {
    case State::white:
    {
        //        c.attach_chip(White);
        c.attach_chip(*(new WhiteChip(*this, {c.loc.x + Cross::size / 4, c.loc.y + Cross::size / 4})));
        // game_manager.cells[c.get_id()].
        break;
    }
    case State::black:
    {
        //        c.attach_chip(Black);
        c.attach_chip(*(new BlackChip(*this, {c.loc.x + Cross::size / 4, c.loc.y + Cross::size / 4})));
        break;
    }
    default:
    {
        break;
    }
    }
    game_manager.clicked(c.get_id());
    std::ostringstream oss;
    oss << "White score = " << game_manager.get_board().white_count;
    w_score.set_label(oss.str());
    std::ostringstream oss2;
    oss2 << "Black score = " << game_manager.get_board().black_count;
    b_score.set_label(oss2.str());
    if (game_manager.get_board().is_black_turn())
    {
        state = State::black;
        pass_button.change_color(true);
        last_white = {c.x, c.y};
    }
    else
    {
        state = State::white;
        pass_button.change_color(false);
        last_black = {c.x, c.y};
    }
    hide_crosses();
    was_pass = false;
}

void GO::pass(Pass &c)
{
    ++game_manager.pass_count;

    game_manager.get_board().set_black_turn(!game_manager.get_board().is_black_turn());
    if (game_manager.get_board().is_black_turn())
    {
        state = State::black;
        pass_button.change_color(true);
    }
    else
    {
        state = State::white;
        pass_button.change_color(false);
    }
    // game_manager.get_board().reset_pass_color(game_manager.get_board().is_black_turn() ? 56
    //                                              : 255);  // черный белый
    if (game_manager.pass_count == 2)
    {
        // exit(0);

        game_manager.get_board().recount();
        std::ostringstream oss;
        oss << "White score = " << game_manager.get_board().white_count;
        w_score.set_label(oss.str());
        std::ostringstream oss2;
        oss2 << "Black score = " << game_manager.get_board().black_count;
        b_score.set_label(oss2.str());

        crosses.hide(std::vector<std::vector<bool>> (N, std::vector<bool> (N, false)));
        pass_button.hide();

        Fl::redraw();
    }
    return;
}

void GO::hide_crosses()
{

    switch (state)
    {
    case State::black:
    {
        // crosses.hide(move(crosses.get_state(), true, last_black));
        break;
    }
    case State::white:
    {
        // crosses.hide(move(crosses.get_state(), false, last_white));
        break;
    }
    default:
    {
        break;
    }
    }
}
