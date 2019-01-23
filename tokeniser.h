#ifndef TOKENISER_H
#define TOKENISER_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#define FALSE 0
#define TRUE  1

#define T_SYM 0
#define T_ARG 1
#define S_ADD 43
#define S_SUB 45
#define S_MUL 42
#define S_DIV 47
#define S_POW 94
#define S_LTP 40
#define S_RTP 41

#define ADD_TOKEN(t,v,c) c = add_token(t,v,c)
#define PUSH_STACK(v,t) t = push_stack(v,t)
#define POP_STACK(v,t) t = pop_stack(&v,t)
#define STACK_IS_EMPTY(t) t->bos==1

typedef struct token {
  int ttype;
  int tval;
  struct token * next;
} token_t;

typedef struct sel {
  int bos;
  int val;
  struct sel * next;
} sel_t;

token_t * init_tokeniser(void);
token_t * add_token(int ttype, int tval, token_t * curr);
sel_t * init_stack(void);
sel_t * push_stack(int val, sel_t * tos);
sel_t * pop_stack(int * val, sel_t * tos);
sel_t * add_argtok(sel_t * tos, token_t ** head);
token_t * tokenise(char * expr, token_t * head);
#ifdef DEBUG
void print_tokens(token_t * head);
sel_t * empty_stack(sel_t * tos);
#endif

#endif
