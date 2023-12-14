#include "rules.h"

using namespace std;

bool Rules::ko(Cell &c2)
{
  if (black_turn && first_white_turn)
  {
    white_ko_check = &c2;
    first_white_turn = false;
    return false;
  }
  if (!black_turn && first_black_turn)
  {
    black_ko_check = &c2;
    first_black_turn = false;
    return false;
  }
  if ((black_turn && &c2 == white_ko_check) ||
      (!black_turn && &c2 == black_ko_check))
  {
    black_turn = !black_turn;
    std::cout << "ko";
    return true;
  }
  if (black_turn)
    white_ko_check = &c2;
  if (!black_turn)
    black_ko_check = &c2;
  return false;
}

void Rules::check_rules(Cell &c2)
{

  int a = c2.get_y();
  int b = c2.get_x();
  std::cout << a << b;

  if (black_turn)
  { // был ход белых
    check_around_black(a, b);
    cells_to_eat.clear();
    to_remove_cells.clear();
    if (death_check(a, b, true))
    {
      c2.detach_figure();
    }
    cells_to_eat.clear();
    to_remove_cells.clear();
  }
  else if (!black_turn)
  { // был ход черных
    check_around_white(a, b);
    cells_to_eat.clear();
    to_remove_cells.clear();
    if (death_check(a, b, false))
    {

      c2.detach_figure();
    }
    cells_to_eat.clear();
    to_remove_cells.clear();
  }
}

bool Rules::check(int a, int b)
{
  bool del = true;
  std::cout << "black";
  cells_to_eat.push_back(a * 10 + b);

  if (a - 1 > 0 && !at(a - 1, b).has_figure())
    return false;
  if (a + 1 <= 9 && !at(a + 1, b).has_figure())
    return false;
  if (b + 1 <= 9 && !at(a, b + 1).has_figure())
    return false;
  if (b - 1 > 0 && !at(a, b - 1).has_figure())
    return false;

  if ((a - 1 > 0 &&
       (at(a - 1, b).has_white_figure() == at(a, b).has_white_figure())) &&
      std::count(cells_to_eat.begin(), cells_to_eat.end(), (a - 1) * 10 + b) == 0)
  {
    del = check(a - 1, b) && del;
    std::cout << "utop" << a << b << std::endl;
  }

  if ((a + 1 <= 9 &&
       (at(a + 1, b).has_white_figure() == at(a, b).has_white_figure())) &&
      std::count(cells_to_eat.begin(), cells_to_eat.end(), (a + 1) * 10 + b) == 0)
  {

    del = del && check(a + 1, b);
    std::cout << "udown" << a << b << std::endl;
  }

  if ((b + 1 <= 9 &&
       (at(a, b + 1).has_black_figure() != at(a, b).has_white_figure())) &&
      std::count(cells_to_eat.begin(), cells_to_eat.end(), (a) * 10 + b + 1) == 0)
  {

    del = del && check(a, b + 1);
    std::cout << "uright" << a << b << std::endl;
  }

  if ((b - 1 > 0 &&
       (at(a, b - 1).has_black_figure() != at(a, b).has_white_figure())) &&
      std::count(cells_to_eat.begin(), cells_to_eat.end(), (a) * 10 + b - 1) == 0)
  {

    del = del && check(a, b - 1);
    std::cout << "uleft" << a << b << std::endl;
  }
  if (del)
  {
    to_remove_cells.push_back(at(a, b));
    return true;
  }
  return false;
}

void Rules::check_around_black(int a, int b)
{

  std::cout << "first_black";
  if (a - 1 > 0 && at(a - 1, b).has_black_figure())
  {
    if (check(a - 1, b))
      for (int i = 0; i < to_remove_cells.size(); ++i)
      {
        ++white_count;
        to_remove_cells[i].detach_figure();
      }
    cells_to_eat.clear();
    to_remove_cells.clear();
  }
  if (a + 1 < 10 && at(a + 1, b).has_black_figure())
  {
    if (check(a + 1, b))
      for (int i = 0; i < to_remove_cells.size(); ++i)
      {
        ++white_count;
        to_remove_cells[i].detach_figure();
      }
    cells_to_eat.clear();
    to_remove_cells.clear();
  }
  if (b + 1 < 10 && at(a, b + 1).has_black_figure())
  {
    if (check(a, b + 1))
      for (int i = 0; i < to_remove_cells.size(); ++i)
      {
        ++white_count;
        to_remove_cells[i].detach_figure();
      }
    cells_to_eat.clear();
    to_remove_cells.clear();
  }
  if (b - 1 > 0 && at(a, b - 1).has_black_figure())
  {
    if (check(a, b - 1))
      for (int i = 0; i < to_remove_cells.size(); ++i)
      {
        ++white_count;
        to_remove_cells[i].detach_figure();
      }
    cells_to_eat.clear();
    to_remove_cells.clear();
  }
}

bool Rules::death_check(int a, int b, bool black)
{
  if (black)
    if (check(a, b))
    {
      black_turn = !black_turn;
      return true;
    }
  if (!black)
    if (check(a, b))
    {
      black_turn = !black_turn;
      return true;
    }
  return false;
}

void Rules::check_around_white(int a, int b)
{

  std::cout << "first_w";
  if (a - 1 > 0 && at(a - 1, b).has_white_figure())
  {
    if (check(a - 1, b))
      for (int i = 0; i < to_remove_cells.size(); ++i)
      {
        ++black_count;
        to_remove_cells[i].detach_figure();
      }
    cells_to_eat.clear();
    to_remove_cells.clear();
  }
  if (a + 1 < 10 && at(a + 1, b).has_white_figure())
  {
    if (check(a + 1, b))
      for (int i = 0; i < to_remove_cells.size(); ++i)
      {
        ++black_count;
        to_remove_cells[i].detach_figure();
      }
    cells_to_eat.clear();
    to_remove_cells.clear();
  }
  if (b + 1 < 10 && at(a, b + 1).has_white_figure())
  {
    if (check(a, b + 1))
      for (int i = 0; i < to_remove_cells.size(); ++i)
      {
        ++black_count;
        to_remove_cells[i].detach_figure();
      }
    cells_to_eat.clear();
    to_remove_cells.clear();
  }

  if (b - 1 > 0 && at(a, b - 1).has_white_figure())
  {
    if (check(a, b - 1))
      for (int i = 0; i < to_remove_cells.size(); ++i)
      {
        ++black_count;
        to_remove_cells[i].detach_figure();
      }
    cells_to_eat.clear();
    to_remove_cells.clear();
  }
}

void Rules::check_num_w(int i, int j, int group_num)
{
  if (copyw[i][j] == 0)
  {
    copyw[i][j] = group_num;
    if (i - 1 >= 0)
      check_num_w(i - 1, j, group_num);
    if (i + 1 < 9)
      check_num_w(i + 1, j, group_num);
    if (j - 1 >= 0)
      check_num_w(i, j - 1, group_num);
    if (j + 1 < 9)
      check_num_w(i, j + 1, group_num);
  }
}

void Rules::check_num_bl(int i, int j, int group_num)
{
  if (copybl[i][j] == 0)
  {
    copybl[i][j] = group_num;
    if (i - 1 >= 0)
      check_num_bl(i - 1, j, group_num);
    if (i + 1 < 9)
      check_num_bl(i + 1, j, group_num);
    if (j - 1 >= 0)
      check_num_bl(i, j - 1, group_num);
    if (j + 1 < 9)
      check_num_bl(i, j + 1, group_num);
  }
}

void Rules::check_w_line(int i, int j, int group_num)
{
  from_null_to_line.push_back(i * 10 + j);
  copyw[i][j] = checked_w_fig;
  if (i - 1 >= 0)
  {
    if (copyw[i - 1][j] == w_fig)
      check_w_line(i - 1, j, group_num);
    else if (std::count(territory.begin(), territory.end(),
                        copyw[i - 1][j]) == 0)
      territory.push_back(copyw[i - 1][j]);
  }

  if (i + 1 < 9)
  {
    if (copyw[i + 1][j] == w_fig)
      check_w_line(i + 1, j, group_num);
    else if (std::count(territory.begin(), territory.end(),
                        copyw[i + 1][j]) == 0)
      territory.push_back(copyw[i + 1][j]);
  }

  if (j - 1 >= 0)
  {
    if (copyw[i][j - 1] == w_fig)
      check_w_line(i, j - 1, group_num);
    else if (std::count(territory.begin(), territory.end(),
                        copyw[i][j - 1]) == 0)
      territory.push_back(copyw[i][j - 1]);
  }

  if (j + 1 < 9)
  {
    if (copyw[i][j + 1] == w_fig)
      check_w_line(i, j + 1, group_num);
    else if (std::count(territory.begin(), territory.end(),
                        copyw[i][j + 1]) == 0)
      territory.push_back(copyw[i][j + 1]);
  }
  if (i - 1 >= 0 && j - 1 >= 0)
  {
    if (copyw[i - 1][j - 1] == w_fig)
      check_w_line(i - 1, j - 1, group_num);
    else if (std::count(territory.begin(), territory.end(),
                        copyw[i - 1][j - 1]) == 0)
      territory.push_back(copyw[i - 1][j - 1]);
  }

  if (i + 1 < 9 && j + 1 < 9)
  {
    if (copyw[i + 1][j + 1] == w_fig)
      check_w_line(i + 1, j + 1, group_num);
    else if (std::count(territory.begin(), territory.end(),
                        copyw[i + 1][j + 1]) == 0)
      territory.push_back(copyw[i + 1][j + 1]);
  }
  if (j - 1 >= 0 && i + 1 < 9)
  {
    if (copyw[i + 1][j - 1] == w_fig)
      check_w_line(i + 1, j - 1, group_num);
    else if (std::count(territory.begin(), territory.end(),
                        copyw[i + 1][j - 1]) == 0)
      territory.push_back(copyw[i + 1][j - 1]);
  }
  if (j + 1 < 9 && i - 1 >= 0)
  {
    if (copyw[i - 1][j + 1] == w_fig)
      check_w_line(i - 1, j + 1, group_num);
    else if (std::count(territory.begin(), territory.end(),
                        copyw[i - 1][j + 1]) == 0)
      territory.push_back(copyw[i - 1][j + 1]);
  }
}

void Rules::check_bl_line(int i, int j, int group_num)
{
  from_null_to_line.push_back(i * 10 + j);
  copybl[i][j] = checked_bl_fig;
  if (i - 1 >= 0)
  {
    if (copybl[i - 1][j] == bl_fig)
      check_bl_line(i - 1, j, group_num);
    else if (std::count(territory.begin(), territory.end(),
                        copybl[i - 1][j]) == 0)
      territory.push_back(copybl[i - 1][j]);
  }
  if (i + 1 < 9)
  {
    if (copybl[i + 1][j] == bl_fig)
      check_bl_line(i + 1, j, group_num);
    else if (std::count(territory.begin(), territory.end(),
                        copybl[i + 1][j]) == 0)
      territory.push_back(copybl[i + 1][j]);
  }
  if (j - 1 >= 0)
  {
    if (copybl[i][j - 1] == bl_fig)
      check_bl_line(i, j - 1, group_num);
    else if (std::count(territory.begin(), territory.end(),
                        copybl[i][j - 1]) == 0)
      territory.push_back(copybl[i][j - 1]);
  }

  if (j + 1 < 9)
  {
    if (copybl[i][j + 1] == bl_fig)
      check_bl_line(i, j + 1, group_num);
    else if (std::count(territory.begin(), territory.end(),
                        copybl[i][j + 1]) == 0)
      territory.push_back(copybl[i][j + 1]);
  }
  if (i - 1 >= 0 && j - 1 >= 0)
  {
    if (copybl[i - 1][j - 1] == bl_fig)
      check_bl_line(i - 1, j - 1, group_num);
    else if (std::count(territory.begin(), territory.end(),
                        copybl[i - 1][j - 1]) == 0)
      territory.push_back(copybl[i - 1][j - 1]);
  }

  if (i + 1 < 9 && j + 1 < 9)
  {
    if (copybl[i + 1][j + 1] == bl_fig)
      check_bl_line(i + 1, j + 1, group_num);
    else if (std::count(territory.begin(), territory.end(),
                        copybl[i + 1][j + 1]) == 0)
      territory.push_back(copybl[i + 1][j + 1]);
  }
  if (j - 1 >= 0 && i + 1 < 9)
  {
    if (copybl[i + 1][j - 1] == bl_fig)
      check_bl_line(i + 1, j - 1, group_num);
    else if (std::count(territory.begin(), territory.end(),
                        copybl[i + 1][j - 1]) == 0)
      territory.push_back(copybl[i + 1][j - 1]);
  }
  if (j + 1 < 9 && i - 1 >= 0)
  {
    if (copybl[i - 1][j + 1] == bl_fig)
      check_bl_line(i - 1, j + 1, group_num);
    else if (std::count(territory.begin(), territory.end(),
                        copybl[i - 1][j + 1]) == 0)
      territory.push_back(copybl[i - 1][j + 1]);
  }
}

void Rules::recount()
{

  for (int x = 0; x < cells.size(); ++x)
  {
    if (cells[x].get_x() != -1)
    {
      if (cells[x].has_black_figure())
      {
        num_cells[cells[x].get_y() - 1][cells[x].get_x() - 1] = bl_fig;
      }
      if (cells[x].has_white_figure())
      {
        num_cells[cells[x].get_y() - 1][cells[x].get_x() - 1] = w_fig;
      }
      if (!cells[x].has_figure())
        num_cells[cells[x].get_y() - 1][cells[x].get_x() - 1] = no_fig;
    }
  }
  recount_black();
  recount_white();
  recount_territory();
}
void Rules::recount_white()
{
  group_num = 5;
  for (int i = 0; i < 9; ++i)
  {
    for (int j = 0; j < 9; ++j)
    {
      copyw[i][j] = num_cells[i][j];
      if (copyw[i][j] == bl_fig)
        copyw[i][j] = no_fig;
    }
  }

  for (int i = 0; i < 9; ++i)
  {
    for (int j = 0; j < 9; ++j)
    {
      check_num_w(i, j, group_num);
      group_num++;
    }
  }

  for (int i = 0; i < 9; ++i)
  {
    for (int j = 0; j < 9; ++j)
    {
      if (copyw[i][j] == w_fig)
      {
        check_w_line(i, j, w_line_num);
        if (territory.size() > 2 &&
            std::count(territory.begin(), territory.end(), w_fig) == 0)
        {
          for (int x : from_null_to_line)
          {
            copyw[x / 10][x % 10] = w_line_num;
          }
          for (int x : territory)
          {
            std::cout << x << std::endl;
            if (x != checked_w_fig)
              w_territory.push_back(x);
          }
        }
        from_null_to_line.clear();
        territory.clear();
        w_line_num++;
      }
    }
  }
}
void Rules::recount_black()
{
  for (int i = 0; i < 9; ++i)
  {
    for (int j = 0; j < 9; ++j)
    {
      copybl[i][j] = num_cells[i][j];
      if (copybl[i][j] == w_fig)
        copybl[i][j] = no_fig;
    }
  }

  for (int i = 0; i < 9; ++i)
  {
    for (int j = 0; j < 9; ++j)
    {
      check_num_bl(i, j, group_num);
      group_num++;
    }
  }
  for (int i = 0; i < 9; ++i)
  {
    for (int j = 0; j < 9; ++j)
    {
      if (copybl[i][j] == bl_fig)
      {
        check_bl_line(i, j, bl_line_num);
        if (territory.size() > 2 &&
            std::count(territory.begin(), territory.end(), bl_fig) == 0)
        {
          for (int x : from_null_to_line)
          {
            copybl[x / 10][x % 10] = bl_line_num;
          }
          for (int x : territory)
          {
            std::cout << x << std::endl;
            if (x != checked_bl_fig)
              bl_territory.push_back(x);
          }
        }
        from_null_to_line.clear();
        territory.clear();
        bl_line_num++;
      }
    }
  }
}
void Rules::recount_territory()
{
  for (int i = 0; i < 9; ++i)
    for (int j = 0; j < 9; ++j)
    {
      if (copyw[i][j] >= 100)
      {
        int t = copybl[i][j];
        for (int i = 0; i < 9; ++i)
          for (int j = 0; j < 9; ++j)
            if (copybl[i][j] == t)
              copybl[i][j] = 99;
      }
      if (copybl[i][j] >= 100)
      {
        int t = copyw[i][j];
        for (int i = 0; i < 9; ++i)
          for (int j = 0; j < 9; ++j)
            if (copyw[i][j] == t)
              copyw[i][j] = 99;
      }
    }
  for (int i = 0; i < 9; ++i)
    for (int j = 0; j < 9; ++j)
    {
      if (copybl[i][j] >= 100 || copyw[i][j] >= 100)
        ;
      else if (copybl[i][j] == checked_bl_fig)
        check_along_black(i, j);
      else if (copyw[i][j] == checked_w_fig)
        check_along_white(i, j);
      else if (copyw[i][j] != w_fig && copybl[i][j] != bl_fig)
      {
        if (std::count(w_territory.begin(), w_territory.end(),
                       copyw[i][j]) > 0 &&
            std::count(bl_territory.begin(), bl_territory.end(),
                       copybl[i][j]) == 0)
          white_count++;
        if (std::count(w_territory.begin(), w_territory.end(),
                       copyw[i][j]) == 0 &&
            std::count(bl_territory.begin(), bl_territory.end(),
                       copybl[i][j]) > 0)
          black_count++;
      }
    }
}
bool Rules::check_along_black(int i, int j)
{
  copybl[i][j] = bl_fig;
  bool flg = false;
  if (i - 1 >= 0)
  {
    if (copybl[i - 1][j] == checked_bl_fig && check_along_black(i - 1, j))
      flg = true;
    if (copybl[i - 1][j] > checked_bl_fig && copybl[i - 1][j] < 100 && std::count(w_territory.begin(), w_territory.end(), copyw[i - 1][j]) > 0 &&
        std::count(bl_territory.begin(), bl_territory.end(),
                   copybl[i - 1][j]) == 0)
      flg = true;
  }

  if (i + 1 <= 9)
  {
    if (copybl[i + 1][j] == checked_bl_fig && check_along_black(i + 1, j))
      flg = true;
    if (copybl[i + 1][j] > checked_bl_fig && copybl[i + 1][j] < 100 && std::count(w_territory.begin(), w_territory.end(), copyw[i + 1][j]) > 0 &&
        std::count(bl_territory.begin(), bl_territory.end(),
                   copybl[i + 1][j]) == 0)
      flg = true;
  }

  if (j - 1 >= 0)
  {
    if (copybl[i][j - 1] == checked_bl_fig && check_along_black(i, j - 1))
      flg = true;
    if (copybl[i][j - 1] > checked_bl_fig && copybl[i][j - 1] < 100 && std::count(w_territory.begin(), w_territory.end(), copyw[i][j - 1]) > 0 &&
        std::count(bl_territory.begin(), bl_territory.end(),
                   copybl[i][j - 1]) == 0)
      flg = true;
  }
  if (j + 1 <= 9)
  {
    if (copybl[i][j + 1] == checked_bl_fig && check_along_black(i, j + 1))
      flg = true;
    if (copybl[i][j + 1] > checked_bl_fig && copybl[i][j + 1] < 100 && std::count(w_territory.begin(), w_territory.end(), copyw[i][j + 1]) > 0 &&
        std::count(bl_territory.begin(), bl_territory.end(),
                   copybl[i][j + 1]) == 0)
      flg = true;
  }
  if (flg == true)
    white_count = white_count + 2;
  return flg;
}

bool Rules::check_along_white(int i, int j)
{
  copyw[i][j] = w_fig;
  bool flg = false;
  if (i - 1 >= 0)
  {
    if (copyw[i - 1][j] == checked_w_fig && check_along_white(i - 1, j))
      flg = true;
    if (copyw[i - 1][j] > checked_bl_fig && copyw[i - 1][j] < 100 && std::count(w_territory.begin(), w_territory.end(), copyw[i - 1][j]) == 0 &&
        std::count(bl_territory.begin(), bl_territory.end(),
                   copybl[i - 1][j]) > 0)
      flg = true;
  }

  if (i + 1 <= 9)
  {
    if (copyw[i + 1][j] == checked_w_fig && check_along_white(i + 1, j))
      flg = true;
    if (copyw[i + 1][j] > checked_bl_fig && copyw[i + 1][j] < 100 && std::count(w_territory.begin(), w_territory.end(), copyw[i + 1][j]) == 0 &&
        std::count(bl_territory.begin(), bl_territory.end(),
                   copybl[i + 1][j]) > 0)
      flg = true;
  }

  if (j - 1 >= 0)
  {
    if (copyw[i][j - 1] == 3 && check_along_white(i, j - 1))
      flg = true;
    if (copyw[i][j - 1] > checked_bl_fig && copyw[i][j - 1] < 100 && std::count(w_territory.begin(), w_territory.end(), copyw[i][j - 1]) == 0 &&
        std::count(bl_territory.begin(), bl_territory.end(),
                   copybl[i][j - 1]) > 0)
      flg = true;
  }
  if (j + 1 <= 9)
  {
    if (copyw[i][j + 1] == 3 && check_along_white(i, j + 1))
      flg = true;
    if (copyw[i][j + 1] > checked_bl_fig && copyw[i][j + 1] < 100 && std::count(w_territory.begin(), w_territory.end(), copyw[i][j + 1]) == 0 &&
        std::count(bl_territory.begin(), bl_territory.end(),
                   copybl[i][j + 1]) > 0)
      flg = true;
  }
  if (flg)
    black_count = black_count + 2;
  return flg;
}

Cell &Rules::at(int i, int c) // строка и столбец
{
  return cells[(i - 1) * 2 * N + (c - 1) * 2];
}
