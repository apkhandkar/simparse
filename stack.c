#include <stdio.h>
#include <stdlib.h>
#include "simparse.h"

ASEL * as_init() 
{
  ASEL * el = (ASEL *) malloc (sizeof(ASEL));

  el->bos = true;
  el->val = 0;
  el->next = NULL;

  return el;
}

ASEL * as_push(float val, ASEL * top)
{
  ASEL * el = (ASEL *) malloc (sizeof(ASEL));
  
  el->bos = false;
  el->val = val;
  el->next = top;

  return el;
}

ASEL * as_pop(ASEL * curr_top, float * ret)
{
  *ret = curr_top->val;
  ASEL * new_top = curr_top->next;
  free(curr_top);

  return new_top;
}

OSEL * os_init() 
{
  OSEL * el = (OSEL*) malloc (sizeof(OSEL));
  
  el->bos = true;
  el->op = add;
  el->next = NULL;

  return el;
}

OSEL * os_push(OPER op, OSEL * top)
{
  OSEL * el = (OSEL *) malloc (sizeof(OSEL));

  el->bos = false;
  el->op = op;
  el->next = top;

  return el;
}

OSEL * os_pop(OSEL * curr_top, OPER * ret)
{
  *ret = curr_top->op;
  OSEL * new_top = curr_top->next;
  free(curr_top);

  return new_top;
}

char * op_literal(OPER op)
{
  switch(op) {
    case add: return "add";
    case sub: return "sub";
    case mul: return "mul";
    case dvd: return "dvd";
    default:  return "err";
  }
}
