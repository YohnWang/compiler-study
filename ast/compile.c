#include <stdio.h>
#include <stdlib.h>
#include "ast.h"


#define TODO()                                  \
  do{                                                           \
    printf ("\nAdd your code here: file \"%s\", line %d\n",     \
            __FILE__, __LINE__);                                \
  }while(0)

#ifdef UNDDFINED_STRUCT
///////////////////////////////////////////////
// Data structures for the Sum language.
enum Exp_Kind_t {EXP_INT, EXP_SUM};
struct Exp_t
{
  enum Exp_Kind_t kind;
};

struct Exp_Int
{
  enum Exp_Kind_t kind;
  int i;
};

struct Exp_Sum
{
  enum Exp_Kind_t kind;
  struct Exp_t *left;
  struct Exp_t *right;
};

// "constructors"
struct Exp_t *Exp_Int_new (int i)
{
  struct Exp_Int *p = malloc (sizeof(*p));
  p->kind = EXP_INT;
  p->i = i;
  return (struct Exp_t *)p;
}

struct Exp_t *Exp_Sum_new (struct Exp_t *left, struct Exp_t *right)
{
  struct Exp_Sum *p = malloc (sizeof(*p));
  p->kind = EXP_SUM;
  p->left = left;
  p->right = right;
  return (struct Exp_t *)p;
}

// "printer"
void Exp_print (struct Exp_t *exp)
{
  switch (exp->kind){
  case EXP_INT:{
    struct Exp_Int *p = (struct Exp_Int *)exp;
    printf ("%d", p->i);
    break;
  }
  case EXP_SUM:{
    struct Exp_Sum *p = (struct Exp_Sum *)exp;
    Exp_print (p->left);
    printf ("+");
    Exp_print (p->right);
    break;
  }
  default:
    break;
  }
}
#endif

//////////////////////////////////////////////
// Data structures for the Stack language.
enum Stack_Kind_t {STACK_ADD, STACK_PUSH ,STACK_SUB ,STACK_DIV,STACK_TIMES};
struct Stack_t
{
  enum Stack_Kind_t kind;
};

struct Stack_Add
{
  enum Stack_Kind_t kind;
};

struct Stack_Push
{
  enum Stack_Kind_t kind;
  int i;
};

//add structures of sub and div (stack)
struct Stack_Times
{
	enum Stack_Kind_t kind;
};


struct Stack_Sub
{
	enum Stack_Kind_t kind;
	
};

struct Stack_Div
{
	enum Stack_Kind_t kind;

};


// "constructors"
struct Stack_t *Stack_Add_new ()
{
  struct Stack_Add *p = malloc (sizeof(*p));
  p->kind = STACK_ADD;
  return (struct Stack_t *)p;
}

struct Stack_t *Stack_Push_new (int i)
{
  struct Stack_Push *p = malloc (sizeof(*p));
  p->kind = STACK_PUSH;
  p->i = i;
  return (struct Stack_t *)p;
}

struct Stack_t *Stack_Sub_new()
{
	struct Stack_Sub *p = malloc (sizeof(*p));
  	p->kind = STACK_SUB;
  	return (struct Stack_t *)p;
}

struct Stack_t *Stack_Times_new()
{
	struct Stack_Times *p = malloc (sizeof(*p));
 	p->kind = STACK_TIMES;
  	return (struct Stack_t *)p;
}

struct Stack_t *Stack_Div_new()
{
	struct Stack_Div *p = malloc (sizeof(*p));
 	p->kind = STACK_DIV;
  	return (struct Stack_t *)p;
}



/// instruction list
struct List_t
{
  struct Stack_t *instr;
  struct List_t *next;
};

struct List_t *List_new (struct Stack_t *instr, struct List_t *next)
{
  struct List_t *p = malloc (sizeof (*p));
  p->instr = instr;
  p->next = next;
  return p;
}

// "printer"
void List_reverse_print (struct List_t *list)
{
  //TODO();
    if(list==NULL)
        return ;
    else
    {
        List_reverse_print(list->next);
        if(list->instr->kind == STACK_ADD)
            printf("add\n");
        else if(list->instr->kind==STACK_SUB)
        	printf("sub\n");
        else if(list->instr->kind==STACK_TIMES)
        	printf("mul\n");
        else if(list->instr->kind==STACK_DIV)
        	printf("div\n");
        else
        {
            struct Stack_Push *p=(void*)list->instr;
            printf("push %d\n",p->i);
        }
    }
}

//////////////////////////////////////////////////
// a compiler from Sum to Stack
struct List_t *all = 0;

void emit (struct Stack_t *instr)
{
  all = List_new (instr, all);
}

#define IF_OPTIMIZED (1)
void compile (struct Exp_t *exp)
{
  switch (exp->kind){
  case EXP_INT:{
    struct Exp_Int *p = (struct Exp_Int *)exp;
    emit (Stack_Push_new (p->n));
    break;
  }
  case EXP_ADD:{
    //TODO();
    struct Exp_Add *p=(struct Exp_Add*)exp;
    struct Exp_Int *pp,*tt ;
    if(IF_OPTIMIZED&&p->left->kind == EXP_INT && p->right->kind == EXP_INT)
    {
        pp=(void*)p->left;
        tt=(void*)p->right;
        emit(Stack_Push_new(pp->n+tt->n));
    }
    else
    {
        compile(p->left);
        compile(p->right);
        emit(Stack_Add_new());
    }
    break;
  }
  case EXP_SUB:
  {
  	struct Exp_Sub *p=(struct Exp_Sub*)exp;
    struct Exp_Int *pp,*tt ;
    if(IF_OPTIMIZED&&p->left->kind == EXP_INT && p->right->kind == EXP_INT)
    {
        pp=(void*)p->left;
        tt=(void*)p->right;
        emit(Stack_Push_new(pp->n-tt->n));
    }
    else
    {
        compile(p->left);
        compile(p->right);
        emit(Stack_Sub_new());
    }
    break;
  }
  case EXP_TIMES:
  {
  	struct Exp_Times *p=(struct Exp_Times*)exp;
    struct Exp_Int *pp,*tt ;
    if(IF_OPTIMIZED&&p->left->kind == EXP_INT && p->right->kind == EXP_INT)
    {
        pp=(void*)p->left;
        tt=(void*)p->right;
        emit(Stack_Push_new(pp->n*tt->n));
    }
    else
    {
        compile(p->left);
        compile(p->right);
        emit(Stack_Times_new());
    }
    break;
  }
  case EXP_DIV:
  {
  	struct Exp_Div *p=(struct Exp_Div*)exp;
    struct Exp_Int *pp,*tt ;
    if(IF_OPTIMIZED&&p->left->kind == EXP_INT && p->right->kind == EXP_INT)
    {
        pp=(void*)p->left;
        tt=(void*)p->right;
        emit(Stack_Push_new(pp->n/tt->n));
    }
    else
    {
        compile(p->left);
        compile(p->right);
        emit(Stack_Div_new());
    }
    break;
  }
  default:
    break;
  }
}

#ifdef USE_MAIN

//////////////////////////////////////////////////
// program entry
int main()
{
  printf("Compile starting\n");
  /*
  // build an expression tree:
  //            +
  //           / \
  //          +   4
  //         / \
  //        2   3
  */
  struct Exp_t *exp = Exp_Sum_new (Exp_Sum_new(Exp_Int_new (2)
                                               , Exp_Sum_new(Exp_Int_new (2),Exp_Int_new (4)))
                                   , Exp_Int_new (4));
  // print out this tree:
  printf ("the expression is:\n");
  Exp_print (exp);printf("\n");
  // compile this tree to Stack machine instructions
  compile (exp);

  // print out the generated Stack instructons:
  List_reverse_print (all);

  printf("\nCompile finished\n");
  return 0;
}
#endif

