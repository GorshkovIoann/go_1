#pragma once

// #include "std_lib_facilities.h"
#include "Cell.h"

#include <vector>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <utility>

// std::vector<std::vector<bool>> move(std::vector<std::vector<int>> st, bool black, std::pair<int, int> last);

class Rules
{
public:
  Rules() = default;
  static constexpr int N =
      17; //= 9 черных клеток, 8 перегородок размером с клетку
  Cell &at(int i, int c);
  bool ko(Cell &c2);
  void check_rules(Cell &c2);

  bool is_black_turn() { return black_turn; }

  void set_black_turn(bool bl_turn) { black_turn = bl_turn; }
  Graph_lib::Vector_ref<Cell> &get_cells() { return cells; }

  bool death_check(int a, int b, bool black);
  void check_around_white(int a, int b);
  void check_around_black(int a, int b);
  bool check(int y, int x);
  void recount();
  // bool is_on_black_territory (int a, int b);
  // bool is_on_white_territory (int a, int b);
  // int get_pass ();
  void check_num_bl(int i, int j, int group_num);
  void check_num_w(int i, int j, int group_num);
  void check_bl_line(int i, int j, int group_num);
  void check_w_line(int i, int j, int group_num);

  double white_count = 6.5;
  double black_count = 0.;

private:
  int copy1[9][9];
  int copy2[9][9];
  std::vector<int> bl_territory;
  std::vector<int> w_territory;
  std::vector<int> territory;
  std::vector<int> nums;
  std::vector<int> from_null_to_line;

  // Graph_lib::Text w_score{Graph_lib::Point{40, 20}, "White score = 6.5"};
  // Graph_lib::Text b_score{Graph_lib::Point{450, 20}, "BLack score = 0"};

  bool black_turn = true;

  bool first_black_turn = true;
  bool first_white_turn = true;

  static constexpr int margin = 30;

  Graph_lib::Vector_ref<Cell> cells;
  Graph_lib::Vector_ref<Cell> to_remove_cells;
  bool check_along_black(int i, int j);
  bool check_along_white(int i, int j);
  Cell *white_ko_check{nullptr}; // позиция последнего белого камня
  Cell *black_ko_check{nullptr}; // позиция последнего черного камня
};