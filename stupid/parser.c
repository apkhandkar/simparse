#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "simparse.h"

int chr_2_int(char c)
{
  switch(c) {
    case '0': return 0;
    case '1': return 1;
    case '2': return 2;
    case '3': return 3;
    case '4': return 4;
    case '5': return 5;
    case '6': return 6;
    case '7': return 7;
    case '8': return 8;
    case '9': return 9;
    default:  fprintf(stderr, "Invalid symbol"); exit(-1);
  }
}


ASEL * push_arg(int i_end, int i_sta, char * str, ASEL * top)
{
  int numlen = (i_end-i_sta);
  int arg = 0;
  for(int i=i_sta; i<=i_end; i++) {
    arg += (pow(10,numlen) * chr_2_int(str[i]));
    numlen--;
  }
  AS_PUSH(top, arg);
  return top;
}

OSEL * push_op(int pos, char * str, OSEL * top)
{
  OPER op;
  switch(str[pos]) {
    case '+': op = add; break;
    case '-': op = sub; break;
    case '*': op = mul; break;
    case '/': op = dvd; break;
    default:  op = add;
  }
  OS_PUSH(top, op);
  return top;
}

void parser(int cur_pos, int l_mark, char * str, ASEL ** as_top, OSEL ** os_top) {
  switch(str[cur_pos]) {
    case '0': case '1': case '2':
    case '3': case '4': case '5':
    case '6': case '7': case '8':
    case '9':
      parser((cur_pos+1), l_mark, str, as_top, os_top);
      return;
    case '+': case '-':
    case '/': case '*':
      *as_top = push_arg((cur_pos-1), l_mark, str, *as_top);
      *os_top = push_op(cur_pos, str, *os_top);
      parser((cur_pos+1), (cur_pos+1), str, as_top, os_top);
      return;
    case '$':
      *as_top = push_arg((cur_pos-1), l_mark, str, *as_top);
      return;
    default:
#ifdef VERBOSE
      fprintf(stderr, "Invalid symbol: %c\n", str[cur_pos]);
#endif
      exit(-1);
  }
}

