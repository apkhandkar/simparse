#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "simparse.h"

int main() 
{
  ASEL * as_top;
  OSEL * os_top;

  char str[100];

  as_top = as_init();
  os_top = os_init();

  printf("Enter expression: ");
  gets(str);
  strcat(str, "$");

  parser(0, 0, str, &as_top, &os_top);
  as_top = processor(as_top, os_top);

  printf("The expression evaluates to: %f\n", as_top->val);

  return 0;
}
