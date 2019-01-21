#ifndef TOKENISER_H
#define TOKENISER_H

#define ADD_ATOKEN(c,v) c = add_atoken(c,v);
#define ADD_OTOKEN(c,v) c = add_otoken(c,v);

#define TOKENISE_CASE_NUM 1
#define TOKENISE_CASE_SYM 2
#define TOKENISE_CASE_EOE 3
#define TOKENISE_CASE_ERR 4

typedef enum tok_type {
  arg,
  sym
} TOK_TYPE;

typedef enum sym {
  add,
  sub,
  mul,
  dvd,
  rtp,
  ltp
} SYM;

typedef struct token {
  int is_head;
  TOK_TYPE type;
  float arg;
  SYM sym;
  struct token *next;
} TOKEN;

TOKEN * init_tokeniser();
TOKEN * add_atoken(TOKEN * curr, float val);
TOKEN * add_otoken(TOKEN * curr, SYM val);
int chr_2_int(char c);
TOKEN * push_arg(int i_end, int i_sta, char * str, TOKEN * curr_top);
void tokenise(int cur_pos, int l_mark, char * str, TOKEN ** curr_top);

#endif
