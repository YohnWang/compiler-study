%{
#include<stdio.h>
int yylex();
void yyerror();
%}
%token dig
%left '+' '-'
%left '*' '/'
%right NEG
%nonassoc '(' ')'


%%
lines: line 
	| line lines
	;

line: '\n' {printf("None!\n");}
	| exp '\n' {printf("result=%d\n",$1);}
	;
exp: exp '+' exp {$$=$1+$3;}
	|exp '-' exp {$$=$1-$3;}
	|exp '*' exp {$$=$1*$3;}
	|exp '/' exp {$$=$1/$3;}
	|'(' exp ')' {$$=$2;}
	|'-' exp %prec NEG {$$=-$2;}
	|dig		 {$$=$1;}
	;

%%

int yylex()
{
	int c;
	c=getchar();
	if(c>='0' && c<='9')
	{
		c=c-'0';
		yylval=c;
		return dig;
	}
	return c;
}
void yyerror(char *s)
{
	fprintf(stderr,"%s\n",s);
}
int main()
{
	yyparse();
	return 0;
}

