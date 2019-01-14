#include <stdio.h>
#include <stdlib.h>
#include "simparse.h"

ASEL *  processor(ASEL * as_top, OSEL * os_top)
{
  float arg1, arg2, res;
  OPER op;

  if(os_top->bos==true)
    return as_top;

  AS_POP(as_top, &arg1);
  AS_POP(as_top, &arg2);
  OS_POP(os_top, &op);

  res = process(arg1, arg2, op);
  AS_PUSH(as_top, res);
  return processor(as_top, os_top);
}
