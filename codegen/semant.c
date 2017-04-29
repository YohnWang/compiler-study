#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "semant.h"

#define TODO()\
  do{\
  printf ("TODO: add your code at file: \"%s\", line: %d\n", __FILE__, __LINE__);\
}while(0)

//////////////////////////////////////
// the symbol table
List_t table = 0;

// lookup an "id" in the symbol table.
// return "type" on success; and -1 for failure
Type_t Table_lookup (char *id)
{
  List_t p = table;
  while (p){
    Dec_t d = (Dec_t)p->data;
    if (strcmp(d->id, id)==0)
      return d->type;
    p = p->next;
  }
  return -1;
}

void Table_insert (Dec_t dec)
{
  
  if (Table_lookup (dec->id) != -1){
    fprintf (stderr, "Error: the variable "
	     "\"%s\" has been declared!\n", dec->id);
    exit (0);
  }
  table = List_new (dec, table);
  return;
}

//////////////////////////////////////////
// dec
void check_dec(Dec_t d)
{
  Table_insert (d);
}

void check_decs(List_t decs)
{
  while (decs){
    Dec_t d = (Dec_t)decs->data;
    check_dec(d);
    decs = decs->next;
  }
  return;
}

////////////////////////////////////////
// exp

// Your job:
Type_t check_exp (Exp_t exp)
{
  //TODO();
  switch(exp->kind)
  {
  case EXP_INT: return TYPE_INT;
  case EXP_TRUE: return TYPE_BOOL;
  case EXP_FALSE: return TYPE_BOOL;
  case EXP_ID: 
  {
  	Type_t t=Table_lookup(((Exp_Id)exp)->id);
  	if(t==-1)
  	{
  		fprintf(stderr,"error: '%s' undeclared\n",((Exp_Id)exp)->id);
  		exit(0);
  	}
  	return t;
  }
  case EXP_ADD:
  case EXP_SUB:
  case EXP_TIMES:
  case EXP_DIVIDE:
  {
  	Type_t l=check_exp(((Exp_Add)exp)->left);
  	Type_t r=check_exp(((Exp_Add)exp)->right);
  	if(l!=TYPE_INT || r!=TYPE_INT)
  	{
  		fprintf(stderr,"Error: invalid operands ,int\n");
  		exit(0);
  	}
  	return TYPE_INT;
  }
  case EXP_AND:
  case EXP_OR:
  {
  	Type_t l=check_exp(((Exp_And)exp)->left);
  	Type_t r=check_exp(((Exp_And)exp)->right);
  	if(l!=TYPE_BOOL || r!=TYPE_BOOL)
  	{
  		fprintf(stderr,"Error: invalid operands ,bool\n");
  		exit(0);
  	}
  	return TYPE_BOOL;
  }
  }
}

////////////////////////////////////////
// stm

// Your job:
void check_stm (Stm_t stm)
{
  //TODO();
  switch (stm->kind)
  {
  case STM_ASSIGN:
  {
  	Stm_Assign t=(Stm_Assign)stm;
  	Type_t l=Table_lookup(t->id);
  	Type_t r=check_exp(t->exp);
  	if(l==-1)
  	{
  		fprintf(stderr,"error: '%s' undeclared \n",t->id);
  		exit(0);
  	}
  	if(l!=r)
  	{
  		fprintf(stderr,"error: incompatiable type when assign\n");
  		exit(0);
  	}
  	return ;
  }
  case STM_PRINTI:
  {
  	Stm_Printi t=(Stm_Printi)stm;
  	Type_t i=check_exp(t->exp);
  	if(i!=TYPE_INT)
  	{
  		fprintf(stderr,"incompatiable type when print int\n");
  		exit(0);
  	}
  	return ;
  }
  case STM_PRINTB:
  {
  	Stm_Printb t=(Stm_Printb)stm;
  	Type_t b=check_exp(t->exp);
  	if(b!=TYPE_BOOL)
  	{
  		fprintf(stderr,"incompatiable type when print bool\n");
  		exit(0);
  	}
  	return ;
  }
  }
}

void check_stms(List_t stms)
{
  while (stms){
    Stm_t s = (Stm_t)stms->data;
    check_stm(s);
    stms = stms->next;
  }
  return;
  TODO();
}


void Semant_check(Prog_t prog)
{
  // create table
  check_decs(prog->decs);
  // check stm
  check_stms(prog->stms);
  return;
}
