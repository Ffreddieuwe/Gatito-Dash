#include "Vector.h"
#include <math.h>

void Vector::normalise()
{
  float magnitude = sqrt((x*x) + (y*y));

  x = x/magnitude;
  y = y/magnitude;
}