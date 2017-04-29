#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"stack-machine.h"

static FILE *fp;
static const char *str=
"\
#include<stdio.h>\n\
#include<stdlib.h>\n\
static char stack[1000];\
static char memory[10000];\
static int sp=-4;\
\
void push(int x)\
{\
    sp+=4;\
    int *p=(int*)(stack+sp);\
    *p=x;\
}\
\
void load(int addr)\
{\
    int *xp=(int*)(memory+addr);\
    push(*xp);\
}\
\
void store(int addr)\
{\
    int *p=(int*)(stack+sp);\
    int *xp=(int*)(memory+addr);\
    *xp=*p;\
    sp-=4;\
}\
\
void add()\
{\
    int sum;\
    sum=*(int*)(stack+sp)+*(int*)(stack+sp-4);\
    sp-=8;\
    push(sum);\
}\
\
void sub()\
{\
    int dif;\
    dif=*(int*)(stack+sp-4)-*(int*)(stack+sp);\
    sp-=8;\
    push(dif);\
}\
\
void mul()\
{\
    int pro;\
    pro=*(int*)(stack+sp-4) * *(int*)(stack+sp);\
    sp-=8;\
    push(pro);\
}\
\
void divide()\
{\
    int quo;\
    quo=*(int*)(stack+sp-4) / *(int*)(stack+sp);\
    sp-=8;\
    push(quo);\
}\
void and()\
{\
    int x=*(int*)(stack+sp-4) && *(int*)(stack+sp);\
    sp-=8;\
    push(x);\
}\
void or()\
{\
    int x=*(int*)(stack+sp-4) || *(int*)(stack+sp);\
    sp-=8;\
    push(x);\
}\
\
void printi()\
{\
    int x=*(int*)(stack+sp);\
    sp-=4;\
    printf(\"%%d\",x);\
    putchar(10);\
}\
\
void printb()\
{\
    int x=*(int*)(stack+sp);\
    sp-=4;\
    if(x)\
        printf(\"true\");\
    else\
        printf(\"false\");\
    putchar(10);\
}\
\
int main(int argc,char *argv[])\
{\n\
";

struct Table
{
	int addr;
	char *s;
};
static struct Table table[1000];
static int table_n=0;

static int find(char *id)
{
	for(int i=0;i<table_n;i++)
	{
		if(strcmp(id,table[i].s)==0)
			return table[i].addr;
	}
	return -1;
}

static void dispatch(char *id)
{
	if(find(id)==-1)
	{
		table[table_n].s=id;
		table[table_n].addr=table_n * 4;
		table_n++;
	}
}

static void gen_c_ids(List_t ids)
{
	while(ids)
	{
		dispatch(ids->data);
		ids=ids->next;
	}
}

static void gen_c_instr (Stack_Instr_t s)
{
	switch(s->kind)
	{
	case STACK_INSTR_PUSH:
	{
		Stack_Instr_Push p = (Stack_Instr_Push)s;
		fprintf (fp, "\tpush(%d);\n", p->n);
		break;
	}
	case STACK_INSTR_LOAD:
	{
		Stack_Instr_Load p = (Stack_Instr_Load)s;
		fprintf (fp, "\tload(%d);\n", find(p->x));
		break;
	}
	case STACK_INSTR_STORE:
	{
		Stack_Instr_Store p = (Stack_Instr_Store)s;
		fprintf (fp, "\tstore(%d);\n", find(p->x));
		break;
	}
	case STACK_INSTR_ADD:
	{
		fprintf (fp, "\tadd();\n");
		break;
	}
	case STACK_INSTR_SUB:
	{
		fprintf (fp, "\tsub();\n");
		break;
	}
	case STACK_INSTR_TIMES:
	{
		fprintf (fp, "\tmul();\n");
		break;
	}
	case STACK_INSTR_DIV:
	{
		fprintf (fp, "\tdivide();\n");
		break;
	}
	case STACK_INSTR_PRINTI:
	{
		fprintf (fp, "\tprinti();\n");
		break;
	}
	case STACK_INSTR_PRINTB:
	{
		fprintf (fp, "\tprintb();\n");
		break;
	}
	case STACK_INSTR_AND:
	{
		fprintf(fp,"\tand();\n");
		break;
	}
	case STACK_INSTR_OR:
	{
		fprintf(fp,"\tor();\n");
		break;
	}
	default:
		break;
	}
}

static void gen_c_instrs(List_t l)
{
	while(l)
	{
		gen_c_instr(l->data);
		l=l->next;
	}
}

void stack_c_print(Stack_Prog_t p)
{
	fp=fopen("temp.c","w");
	if(fp==NULL)
	{
		fprintf(stderr,"error in open file\n");
		exit(0);
	}
	fprintf(fp,str);
	gen_c_ids(p->ids);
	gen_c_instrs(p->instrs);
	
	fprintf(fp,"}");
	fclose(fp);
}
