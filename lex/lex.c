#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>


int isI(char c)
{
    if(c=='i')
        return 1;
    return 0;
}

int isF(char c)
{
    if(c=='f')
        return 1;
    return 0;
}

int isletter(char c)
{
    if(isalpha(c)||c=='_')
        return 1;
    return 0;
}

int is_blank(char c)
{
    if(c==' '||c=='\n'||c=='\t')
        return 1;
    return 0;
}

enum{NONE=255,ID,IF,NUM,ENDL};//yystatus
enum{LEXI=0,LEXF,LETTER,DIGIT,BLANK};

int status_table[5][5]=
{
    {1,3,3,4,0},
    {3,2,3,3,ID},
    {3,3,3,3,IF},
    {3,3,3,3,ID},
    {-1,-1,-1,4,NUM},
};

static int yyline=1;
static int lexlinecnt=0;
static int yybegin;
static int yylength=0;
static char yytext[1024];
static int yystatus=0;

int nextstatus()
{
    static char c;
    if(c=='\n')
    {
        yyline++;
        lexlinecnt=0;
    }

    c=getchar();
    lexlinecnt++;
    if(!is_blank(c))
        yytext[yylength++]=c;

    if(isI(c))
        yystatus=status_table[yystatus][LEXI];
    else if(isF(c))
        yystatus=status_table[yystatus][LEXF];
    else if(isletter(c))
        yystatus=status_table[yystatus][LETTER];
    else if(isdigit(c))
        yystatus=status_table[yystatus][DIGIT];
    else if(is_blank(c))
        yystatus=status_table[yystatus][BLANK];
    else
        yystatus=ENDL;
    return yystatus;
}

int yylex()
{
    yylength=0;

    for(;;)
    {
        switch(nextstatus())
        {
        case ID:
            yytext[yylength]='\0';
            goto END;
            break;
        case IF:
            yytext[yylength]='\0';
            goto END;
            break;
        case NUM:
            yytext[yylength]='\0';
            goto END;
            break;
        case ENDL:
            goto END;
            break;
        case -1:
            fprintf(stderr,"error!\n");
            exit(0);
            break;
        default:

            break;
        }
    }

END:
    yybegin=lexlinecnt-yylength;
    int r=yystatus;
    yystatus=0; //notic status must set zero.
    return r;
}

int main(int argc,char *argv[])
{
    int s;
    while((s=yylex())!=ENDL)
    {
        if(s==ID)
        {
            printf("ID(%s)(%d,%d)\n",yytext,yyline,yybegin);
        }
        else if(s==IF)
        {
            printf("IF   (%d,%d)\n",yyline,yybegin);
        }
        else if(s==NUM)
        {
            printf("NUM(%s)(%d,%d)\n",yytext,yyline,yybegin);
        }
    }
}
