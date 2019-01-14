#include "simparse.h"

float process(float arg1, float arg2, OPER op)
{
  switch(op) {
    case add: return (arg2+arg1);
    case sub: return (arg2-arg1);
    case mul: return (arg2*arg1);
    case dvd: return (arg2/arg1);
    default:  return 0;
  }
}
