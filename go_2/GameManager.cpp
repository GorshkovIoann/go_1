#include "GameManager.h"

void Game::clicked(int id)
{
  Cell &c2 = stones[id];
  if (c2.has_figure())
  {
    return;
  }
  // if (c2.get_id() == board.get_pass())
  //{
  //   ++pass_count;
  //   board.set_black_turn(!board.is_black_turn());
  //   board.reset_pass_color(board.is_black_turn() ? 56
  //                                                : 255);  // черный белый
  //   if (pass_count == 2)
  //   {
  //     // exit(0);
  //
  //     board.recount();
  //     Fl::redraw();
  //   }
  //   return;
  // }
  if (board.is_black_turn())
  {
    pass_count = 0;
    board.set_black_turn(false);
    if (!board.ko(c2))
    {
      c2.attach_figure(Black);
      board.check_rules(c2);
    }
    else
    {
      c2.detach_figure();
    }
  }
  else
  {
    pass_count = 0;
    board.set_black_turn(true);

    if (!board.ko(c2))
    {
      c2.attach_figure(White);
      board.check_rules(c2);
    }
    else
    {
      c2.detach_figure();
    }
  }
  // board.reset_pass_color(board.is_black_turn() ? 56 : 255);
}

void Game::set_stones(Crosses &crosses)
{
  int t = 0;
  // stones.push_back(*(new Cell()));
  // board.cells.push_back(*(new Cell()));
  for (int i = 0; i < 17; ++i)
  {
    for (int j = 0; j < 17; ++j)
    { // заполняется по строкам начиная с нижней левой
      // if(i%2==0 && j%2 == 0)
      if ((i % 2 == 0) && (j % 2 == 0))
      {
        stones.push_back(*(new Cell(&crosses.get_crosses()[t])));
        stones[stones.size() - 1].set_position(j / 2 + 1, i / 2 + 1);
        board.get_cells().push_back(stones[stones.size() - 1]);
        ++t;
        // std::cout << crosses.get_crosses()[i+1 + j * 17] << std::endl;
      }
      else
      {
        stones.push_back(*(new Cell()));
        board.get_cells().push_back(stones[stones.size() - 1]);
      }
    }
  }
}

Game::Game()
{
  board = Rules();
}