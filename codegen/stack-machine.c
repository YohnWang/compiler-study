#include <stdio.h>
#include <stdlib.h>
#include "stack-machine.h"

/////////////////////////////////////
// instructions

void Stack_Instr_print (Stack_Instr_t s)
{
  switch(s->kind){
  case STACK_INSTR_PUSH:{
    Stack_Instr_Push p = (Stack_Instr_Push)s;
    printf ("push %d", p->n);
    break;
  }
  case STACK_INSTR_LOAD:{
    Stack_Instr_Load p = (Stack_Instr_Load)s;
    printf ("load %s", p->x);
    break;
  }
  case STACK_INSTR_STORE:{
    Stack_Instr_Store p = (Stack_Instr_Store)s;
    printf ("store %s", p->x);
    break;
  }
  case STACK_INSTR_ADD:{
    printf ("add");
    break;
  }
  case STACK_INSTR_SUB:{
    printf ("sub");
    break;
  }
  case STACK_INSTR_TIMES:{
    printf ("times\n");
    break;
  }
  case STACK_INSTR_DIV:{
    printf ("div");
    break;
  }
  case STACK_INSTR_PRINTI:{
    printf ("printi");
    break;
  }
  case STACK_INSTR_PRINTB:{
    printf ("printb");
    break;
  }
  default:
    break;
  }
}

// push 
Stack_Instr_t Stack_Instr_Push_new (int n)
{
  Stack_Instr_Push p = malloc (sizeof(*p));
  p->kind = STACK_INSTR_PUSH;
  p->n = n;
  return (Stack_Instr_t)p;
}

// load x
Stack_Instr_t Stack_Instr_Load_new (char *x)
{
  Stack_Instr_Load p = malloc (sizeof(*p));
  p->kind = STACK_INSTR_LOAD;
  p->x = x;
  return (Stack_Instr_t)p;
}

// store x
Stack_Instr_t Stack_Instr_Store_new (char *x)
{
  Stack_Instr_Store p = malloc (sizeof(*p));
  p->kind = STACK_INSTR_STORE;
  p->x = x;
  return (Stack_Instr_t)p;
}

// add
Stack_Instr_t Stack_Instr_Add_new ()
{
  Stack_Instr_Add p = malloc (sizeof(*p));
  p->kind = STACK_INSTR_ADD;
  return (Stack_Instr_t)p;
}

// printi
Stack_Instr_t Stack_Instr_Printi_new ()
{
  Stack_Instr_Printi p = malloc (sizeof(*p));
  p->kind = STACK_INSTR_PRINTI;
  return (Stack_Instr_t)p;
}

// printb
Stack_Instr_t Stack_Instr_Printb_new ()
{
  Stack_Instr_Printb p = malloc (sizeof(*p));
  p->kind = STACK_INSTR_PRINTB;
  return (Stack_Instr_t)p;
}

//add my code of homework

//sub
Stack_Instr_t Stack_Instr_Sub_new()
{
  Stack_Instr_Sub p=malloc(sizeof(*p));
  p->kind=STACK_INSTR_SUB;
  return (Stack_Instr_t)p;
}

//mul
Stack_Instr_t Stack_Instr_Times_new()
{
  Stack_Instr_Times p=malloc(sizeof(*p));
  p->kind=STACK_INSTR_TIMES;
  return (Stack_Instr_t)p;
}

//div
Stack_Instr_t Stack_Instr_Div_new()
{
  Stack_Instr_Div p=malloc(sizeof(*p));
  p->kind=STACK_INSTR_DIV;
  return (Stack_Instr_t)p;
}

//and
Stack_Instr_t Stack_Instr_And_new()
{
  Stack_Instr_And p=malloc(sizeof(*p));
  p->kind=STACK_INSTR_AND;
  return (Stack_Instr_t)p;
}

//or
Stack_Instr_t Stack_Instr_Or_new()
{
  Stack_Instr_Or p=malloc(sizeof(*p));
  p->kind=STACK_INSTR_OR;
  return (Stack_Instr_t)p;
}



///////////////////////////////////////
// prog
Stack_Prog_t Stack_Prog_new (List_t ids, List_t instrs)
{
  Stack_Prog_t p = malloc (sizeof (*p));
  p->ids = ids;
  p->instrs = instrs;
  return p;
}

void Stack_Prog_print (Stack_Prog_t prog)
{
  List_t ids = prog->ids;
  printf ("{\n");
  while (ids){
    char *id = (char *)ids->data;
    printf ("  .int %s\n", id);
    ids = ids->next;
  }

  printf ("\n");

  List_t instrs = prog->instrs;
  while (instrs){
    Stack_Instr_t s = (Stack_Instr_t)instrs->data;
    printf ("  ");
    Stack_Instr_print (s);
    printf ("\n");
    instrs = instrs->next;
  }
  printf ("}\n");
  return;
}


