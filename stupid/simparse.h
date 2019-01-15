#ifndef SIMPARSE_H
#define SIMPARSE_H

#define AS_PUSH(t,x) t=as_push(x,t);
#define AS_POP(t,r) t=as_pop(t,r);
#define OS_PUSH(t,x) t=os_push(x,t);
#define OS_POP(t,r) t=os_pop(t,r);

typedef enum bool {
  true,
  false
} BOOL;

typedef enum oper {
  add,
  sub,
  mul,
  dvd 
} OPER;

typedef struct asel {
  BOOL bos;
  float val;
  struct asel * next;
} ASEL;

typedef struct osel {
  BOOL bos;
  OPER op;
  struct osel * next;
} OSEL;

float process_sym (float arg1, float arg2, OPER op);
ASEL * as_init();
ASEL * as_push(float val, ASEL * top);
ASEL * as_pop(ASEL * curr_top, float * ret);
OSEL * os_init();
OSEL * os_push(OPER  op, OSEL * top);
OSEL * os_pop(OSEL * curr_top, OPER * ret);
char * op_literal(OPER op);

#endif
