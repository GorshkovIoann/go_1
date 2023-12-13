#pragma once

#include "cross.h"

class Cell
{
public:
  static int big_id; // numbers of Cells
  Cell(Cross *_cross) : id{big_id},
                        cross(_cross),
                        type{None} { ++big_id; };
  Cell() : id{big_id},
           cross{nullptr},
           type{None}
  {
    ++big_id;
    x = -1;
  };
  bool is_black() const { return type == Black; }
  bool is_white() const { return type == White; }

  void attach_figure(ChipType type);
  void detach_figure();

  bool has_figure() const { return type != None; }

  bool has_white_figure() const;

  bool has_black_figure() const;

  int get_id() { return id; }

  int get_x() { return x; }

  int get_y() { return y; }

  int get_position()
  {
    return y * 10 + x;
  } // вернет число:первая цифрa столбец,вторая строка

  void set_position(int a, int b)
  {
    x = a;
    y = b;
  }

private:
  Cross *cross;
  ChipType type;
  int id = 0;
  int x = 0;
  int y = 0;
};