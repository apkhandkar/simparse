#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "tokeniser.h"

TOKEN * init_tokeniser()
{
  TOKEN * tok = (TOKEN *)malloc(sizeof(TOKEN));
  tok->is_head = 1;
  tok->next = NULL;
  
  return tok;
}

TOKEN * add_atoken(TOKEN * curr, float val)
{
  TOKEN * tok = (TOKEN *)malloc(sizeof(TOKEN));

  tok->is_head = 0;
  tok->type = arg;
  tok->arg = val;
  curr->next = tok;
  tok->next = NULL;

#ifdef DEBUG
  printf("Added (argument) token: %f\n", tok->arg);
#endif

  return tok;
}

TOKEN * add_otoken(TOKEN * curr, SYM val)
{
  TOKEN * tok = (TOKEN *)malloc(sizeof(TOKEN));

  tok->is_head = 0;
  tok->type = sym;
  tok->sym = val;
  curr->next = tok;
  tok->next = NULL;

  return tok;
}


int chr_2_int(char c)
{
  switch(c) {
    case '0': return 0; case '1': return 1;
    case '2': return 2; case '3': return 3;
    case '4': return 4; case '5': return 5;
    case '6': return 6; case '7': return 7;
    case '8': return 8; case '9': return 9;
    default:  fprintf(stderr, "Invalid symbol"); exit(-1);
  }
}


TOKEN * push_arg(int i_end, int i_sta, char * str, TOKEN * curr_top)
{
  int numlen = (i_end-i_sta);
  int arg = 0;

  if( str[i_sta]=='-' ||  str[i_sta]=='+' ||
      str[i_sta]=='*' ||  str[i_sta]=='/' ||
      str[i_sta]=='(' ||  str[i_sta]==')' ) {
    fprintf(stderr, "ERROR: Parser encountered unexpected symbol %c\n", str[i_sta]);
    fprintf(stderr, "Halting Execution\n");
    exit(-1);
  }

  for(int i=i_sta; i<=i_end; i++) {
    printf("pusher... %c\n", str[i]);
    arg += (pow(10,numlen) * chr_2_int(str[i]));
    numlen--;
  }

  ADD_ATOKEN(curr_top, arg);
  return curr_top;
}

void tokenise(int cur_pos, int l_mark, char * str, TOKEN ** curr_top) 
{
  SYM got_sym;
  int dec; 

  switch(str[cur_pos]) {
    case '0': case '1': case '2':
    case '3': case '4': case '5':
    case '6': case '7': case '8':
    case '9': dec = TOKENISE_CASE_NUM; 
              break;
    case '+': dec = TOKENISE_CASE_SYM;
              got_sym = add;
              break;
    case '-': dec = TOKENISE_CASE_SYM;
              got_sym = sub;
              break;
    case '*': dec = TOKENISE_CASE_SYM;
              got_sym = mul;
              break;
    case '/': dec = TOKENISE_CASE_SYM;
              got_sym = dvd;
              break;
    case '(': dec = TOKENISE_CASE_SYM;
              got_sym = ltp;
              break;
    case ')': dec = TOKENISE_CASE_SYM;
              got_sym = rtp;
              break;
    case '$': dec = TOKENISE_CASE_EOE;
              break;
    default:  dec = TOKENISE_CASE_ERR;
              break;
  }

  if(dec==TOKENISE_CASE_NUM) { 
    tokenise((cur_pos+1), l_mark, str, curr_top);
  } else if(dec==TOKENISE_CASE_SYM) {
    *curr_top = push_arg((cur_pos-1), l_mark, str, *curr_top);
    ADD_OTOKEN(*curr_top, got_sym);
    tokenise((cur_pos+1), (cur_pos+1), str, curr_top);
  } else if(dec==TOKENISE_CASE_EOE) {
    *curr_top = push_arg((cur_pos-1), l_mark, str, *curr_top);
  } else if(dec==TOKENISE_CASE_ERR) {
    fprintf(stderr, "ERROR: Parser Encountered unexpected symbol: %c (%d)\n", str[cur_pos], str[cur_pos]);
    fprintf(stderr, "Halting Execution\n");
    exit(-1);
  } else {
    fprintf(stderr, "ERROR: Parser couldn't read symbol\n");
    fprintf(stderr, "Halting Execution\n");
    exit(-1);
  }

  return;
}

