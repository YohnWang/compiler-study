#ifndef AST_H
#define AST_H

//add 'sub and div'
enum Exp_Kind_t{
  EXP_INT,
  EXP_ADD,
  EXP_TIMES,
  EXP_SUB,
  EXP_DIV,};

/*
   E -> n
      | E + E
      | E * E
*/
typedef struct Exp_t *Exp_t;
struct Exp_t{
  enum Exp_Kind_t kind;
};
// all operations on "Exp"
void Exp_print (Exp_t exp);
int Exp_numNodes (Exp_t exp);

typedef struct Exp_Int *Exp_Int;
struct Exp_Int{
  enum Exp_Kind_t kind;
  int n;
};
Exp_t Exp_Int_new (int n);

typedef struct Exp_Add *Exp_Add;
struct Exp_Add{
  enum Exp_Kind_t kind;
  Exp_t left;
  Exp_t right;
};
Exp_t Exp_Add_new (Exp_t left, Exp_t right);

typedef struct Exp_Times *Exp_Times;
struct Exp_Times{
  enum Exp_Kind_t kind;
  Exp_t left;
  Exp_t right;
};
Exp_t Exp_Times_new (Exp_t left, Exp_t right);

//add 'structure of sub and div'
typedef struct Exp_Sub *Exp_Sub;
struct Exp_Sub{
  enum Exp_Kind_t kind;
  Exp_t left;
  Exp_t right;
};
Exp_t Exp_Sub_new(Exp_t left,Exp_t right);

typedef struct Exp_Div *Exp_Div;
struct Exp_Div{
  enum Exp_Kind_t kind;
  Exp_t left;
  Exp_t right;
};
Exp_t Exp_Div_new(Exp_t left,Exp_t right);

#endif
