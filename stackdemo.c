#include <stdio.h>
#include <stdlib.h>
#include "simparse.h"

int main() 
{
  float got_val;
  OPER got_op;

  ASEL * as_top = as_init();
  OSEL * os_top = os_init();

  AS_PUSH(as_top, 1);
  AS_PUSH(as_top, 2);
  AS_PUSH(as_top, 3);
  AS_PUSH(as_top, 4);
  AS_PUSH(as_top, 5);
  AS_PUSH(as_top, 6);

  OS_PUSH(os_top, add); 
  OS_PUSH(os_top, sub); 
  OS_PUSH(os_top, mul); 
  OS_PUSH(os_top, dvd); 
  OS_PUSH(os_top, add); 

  while(as_top->bos==false) {
    AS_POP(as_top, &got_val);
    printf("Popped value from argument stack: %f\n", got_val);
  }

  while(os_top->bos==false) {
    OS_POP(os_top, &got_op); 
    printf("Popped value from operator stack: %s\n", op_literal(got_op));
  }

  return 0;
}
