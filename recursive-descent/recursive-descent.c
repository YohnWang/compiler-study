#include<stdio.h>
#include<ctype.h>
char *str;
int i=0;
int sum=0;
int mul=1;

int prase_F()
{
    if(isdigit(str[i]))
    {
        i++;
        return str[i-1]-'0';
    }
    printf("Error\n");
}

int prase_T()
{
    mul=1;
    mul*=prase_F();
    while(str[i]=='*')
    {
        i++;
        mul*=prase_F();
    }
    return mul;

}

int prase_E(char *e)
{
    str=e;
    i=0;
    sum=0;
    sum+=prase_T();
    while(str[i]=='+')
    {
        i++;
        sum+=prase_T();
    }
    if(str[i]=='\0')
        return sum;
    printf("Error\n");
    return -1;
}

int main(int argc,char *argv[])
{
    char *e="3+4*3*2";
    printf("%d\n",prase_E(e));
    e="2+3+4";
    printf("%d\n",prase_E(e));
    e="2*3*4";
    printf("%d\n",prase_E(e));
    e="1+2*3*4+5";
    printf("%d\n",prase_E(e));
}
