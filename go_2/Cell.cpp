#include "Cell.h"

int Cell::big_id = 0;

void Cell::attach_figure(ChipType _type)
{
    type = _type;
    //cross->attach_chip1(type);
}
void Cell::detach_figure()
{
    type = None;
    cross->detach_chip();
}
bool Cell::has_white_figure() const
{
  if (has_figure())
  {
    return is_white();
  }
  return false;
}
bool Cell::has_black_figure() const
{
  if (has_figure())
  {
    return is_black();
  }
  return false;
}