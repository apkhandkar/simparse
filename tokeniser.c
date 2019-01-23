#include "tokeniser.h"

token_t * init_tokeniser()
{
  token_t * tok = (token_t *)malloc(sizeof(token_t));

  tok->next = NULL;

  return tok;
}

token_t * add_token(int ttype, int tval, token_t * curr)
{
  token_t * tok = (token_t *)malloc(sizeof(token_t));

  tok->ttype = ttype;
  tok->tval = tval;
  tok->next = NULL;
  curr->next = tok;

  return tok;
}

sel_t * init_stack()
{
  sel_t * el = (sel_t *)malloc(sizeof(sel_t));

  el->bos = TRUE;

  return el;
}

sel_t * push_stack(int val, sel_t * tos)
{
  sel_t * el = (sel_t *)malloc(sizeof(sel_t));

  el->bos = FALSE;
  el->val = val;
  el->next = tos;

  return el;
}

sel_t * pop_stack(int * val, sel_t * tos)
{
  *val = tos->val;
  
  sel_t * new_tos = tos->next;
  free(tos);

  return new_tos;
}

sel_t * add_argtok(sel_t * tos, token_t ** head)
{
  if(tos->bos==TRUE) {
    // nothing to add here
    return tos;
  } else {
    // add argument to token list, empty the stack
    int ret = 0;
    int p = 0;
    int arg = 0;
    while(tos->bos != TRUE) {
      POP_STACK(ret, tos);
      arg += ret * pow(10,p);
      p++;
    }
    ADD_TOKEN(T_ARG, arg, *head);
    return tos;
  }
}

token_t * tokenise(char * expr, token_t * head)
{
  sel_t * tos = init_stack();

  for(int i=0; i<strlen(expr); i++) {
    switch(expr[i]) {
      // encountered a digit, push it on the 'to-be-added' argstack
      case '0': case '1': case '2':
      case '3': case '4': case '5':
      case '6': case '7': case '8':
      case '9': PUSH_STACK((expr[i]-'0'), tos);
                break;
      // encountered a symbol, add any arguments on the 'to-be-added' stack that haven't 
      // beeen added yet to token list. Then, add the symbol to the token list 
      case '+': case '-': case '*':
      case '/': case '^': case '(':
      case ')': tos = add_argtok(tos, &head);
                head = add_token(T_SYM, expr[i], head);
                break;
      // encountered end of string - add any arguments on the 'to-be-added' stack that
      // haven't been added to the token list
      case '$': tos = add_argtok(tos, &head);
                break;
      // encountered some invalid character
      default:  fprintf(stderr, "ERROR: Encountered invalid symbol %c (%d)\n", expr[i], expr[i]);
                exit(-1);
    }
  }
  
  return head;
}


#ifdef DEBUG
void print_tokens(token_t * head)
{
  head = head->next;

  while(head!=NULL) {
    if(head->ttype==T_SYM) {
      switch(head->tval) {
        case S_ADD:   printf("Symbol: +\n");
                      break;
        case S_SUB:   printf("Symbol: -\n");
                      break;
        case S_MUL:   printf("Symbol: *\n");
                      break;
        case S_DIV:   printf("Symbol: /\n");
                      break;
        case S_POW:   printf("Symbol: ^\n");
                      break;
        case S_LTP:   printf("Symbol: (\n");
                      break;
        case S_RTP:   printf("Symbol: )\n");
                      break;
        default:      printf("Unrecognised symbol\n");
      }
    } else if(head->ttype==T_ARG) {
      printf("Argument: %d\n", head->tval);
    } else {
      printf("Unrecognised token type\n");
    }
    head = head->next;
  }
}

sel_t * empty_stack(sel_t * tos)
{
  int val;
  
  while(tos->bos != TRUE) {
    POP_STACK(val, tos);
    printf("Popped value: %d\n", val);
  }

  return tos;
}
#endif

/*
int main()
{
  token_t * head = init_tokeniser();
  token_t * curr = head;

  char * expr = "12*(12^10)+10-9*((54+20)/10)$";

  curr = tokenise(expr, curr); 
#ifdef DEBUG
  print_tokens(head);
#endif

  return 0;
}
*/
