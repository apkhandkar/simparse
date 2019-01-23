#include "tokeniser.h"

int get_priority(int oper)
{
  int oper_c = (char) oper;
  switch(oper_c) {
    case '^': return 4;
    case '/': return 3;
    case '*': return 2;
    case '+': return 1;
    case '-': return 0;
    default:  return -1;
  }
}

int is_higher_or_eq_prec(int oper1, int oper2)
{
  if(get_priority(oper1) >= get_priority(oper2)) {
    return TRUE; 
  } else {
    return FALSE;
  }
}

token_t * process_operator(int oper, token_t * curr, sel_t ** tos)
{
  int ret;

  while(  (*tos)->bos == FALSE  && 
          (*tos)->val != '('    && 
          is_higher_or_eq_prec((*tos)->val, oper) ) {
#ifdef DEBUG
    printf("Popping symbol: %c\n", (char) (*tos)->val);
#endif 
    POP_STACK(ret, *tos);
    ADD_TOKEN(T_SYM, ret, curr);
  }
  PUSH_STACK(oper, *tos);
#ifdef DEBUG 
  printf("Pushing symbol: %c\n", (char) oper);
#endif
  return curr;
}

token_t * to_postfix(token_t * head) 
{
  token_t * pf_head = init_tokeniser();
  token_t * pf_curr = pf_head;
  sel_t * tos = init_stack();
  int ret;

  head = head->next;

  while(head != NULL) {
    if(head->ttype==T_SYM) {
      // token is symbol
#ifdef DEBUG
      printf("Token contains: %c\n", head->tval);
#endif
      if( head->tval=='+' ||  head->tval=='-' ||
          head->tval=='*' ||  head->tval=='/' ||
          head->tval=='^' ) {
        // token is operator, pop all operators on stack with equal or
        // higher precedence to output then push operator
        pf_curr = process_operator((int)head->tval, pf_curr, &tos);
      } else if(head->tval=='(') {
        // token is left parathesis - push on to stack
        PUSH_STACK(head->tval, tos);
      } else {
        // token is right paranthesis - pop stack till left paranthesis
        // is encountered, and eat left paranthesis
        while(tos->val != '(') {
          POP_STACK(ret, tos);
          ADD_TOKEN(T_SYM, ret, pf_curr);
        }
        POP_STACK(ret, tos);
      }  
    } else {
      // token is argument, push to output
#ifdef DEBUG
      printf("Token contains: %d\n", head->tval);
#endif 
      ADD_TOKEN(T_ARG, head->tval, pf_curr);
    }
    // reached end of token list, empty any remaining stack symbols to 
    // output
    if(head->next==NULL) {
      while(tos->bos == FALSE) {
        POP_STACK(ret, tos);
        ADD_TOKEN(T_SYM, ret, pf_curr);  
      }
    }
    head = head->next;
  }

  return pf_head;
}

/*
int main() 
{
  char * expr = "134/10-(12+15*(6*10/2))-2^20$";
  char * expr2 = "((((1-2))))$";

  token_t * head = init_tokeniser();
  token_t * curr = head;

  curr = tokenise(expr2, curr);
  
  token_t * pf_head = to_postfix(head);

  print_tokens(pf_head);
  return 0;
}
*/
