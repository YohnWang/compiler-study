#include "ast.h"
#include<stdio.h>

struct List_t
{
  struct Stack_t *instr;
  struct List_t *next;
};

extern Exp_t tree;
void yyparse ();
extern void compile (struct Exp_t *exp);
extern void List_reverse_print (struct List_t *list);
extern struct List_t *all;

int main (int argc, char **argv)
{
  yyparse();
  Exp_print (tree);
  printf("\n");
  compile(tree);
  List_reverse_print(all);
  return 0;
}
