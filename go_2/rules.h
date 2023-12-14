#pragma once

#include "Cell.h"

#include <vector>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <utility>
class Rules // класс отвечает за правила игры
{
public:
  Rules() = default;
  static constexpr int N =
      17;                     //= 9 черных клеток, 8 перегородок размером с клетку
  Cell &at(int i, int c);     // клетка из массива по у и х
  bool ko(Cell &c2);          // проверка правила ко до того как фишка поставлена
  void check_rules(Cell &c2); // проверка всех правил после того как фишка поставлена

  bool is_black_turn() { return black_turn; } // сейчас черный ход?

  void set_black_turn(bool bl_turn) { black_turn = bl_turn; } // установить чей ход
  Graph_lib::Vector_ref<Cell> &get_cells() { return cells; }

  void recount(); // метод пересчета захваченной территории

  double white_count = 6.5;
  double black_count = 0.;

private:
  int group_num = 5;
  int bl_line_num = 100;
  int w_line_num = 200;
  int bl_fig = 2;
  int w_fig = 1;
  int checked_bl_fig = bl_fig + 2;
  int checked_w_fig = w_fig + 2;
  int no_fig = 0;
  int num_cells[9][9];
  int copybl[9][9];
  int copyw[9][9];
  std::vector<int> bl_territory;
  std::vector<int> w_territory;
  std::vector<int> territory;
  std::vector<int> cells_to_eat;
  std::vector<int> from_null_to_line;
  void recount_white();                            // тут считается территория прилегающая  к белым линиям
  void recount_black();                            // тут считается территория прилегающая  к черным линиям
  void recount_territory();                        // тут подводится итог пересчета территории в очках
  void check_num_bl(int i, int j, int group_num);  // присваеваем группе не черных клеток номер
  void check_num_w(int i, int j, int group_num);   // присваеваем группе не белых клеток номер
  void check_bl_line(int i, int j, int group_num); // проверка клетки на принадлежность черной линии
  void check_w_line(int i, int j, int group_num);  // проверка клетки на принадлежность белой линии
  bool check_along_black(int i, int j);            // проверка на пленение черной фишки
  bool check_along_white(int i, int j);            // проверка на пленение белой фишки
  bool black_turn = true;

  bool first_black_turn = true;
  bool first_white_turn = true;

  bool death_check(int a, int b, bool black); // проверка смертельный для игрока ход
  void check_around_white(int a, int b);      // после поставленной белой фишки проверяем что она сьела
  void check_around_black(int a, int b);      // после поставленной черной фишки проверяем что она сьела
  bool check(int y, int x);                   // сьела ли фишка группу фишек. Проход по группе
  Graph_lib::Vector_ref<Cell> cells;
  Graph_lib::Vector_ref<Cell> to_remove_cells;

  Cell *white_ko_check{nullptr}; // позиция последнего белого камня
  Cell *black_ko_check{nullptr}; // позиция последнего черного камня
};