%{
#include <stdio.h>
#include <string.h>

char *kw[] = {
"int","char","float","double","if","else","for","while",
"return","void","break","continue","switch","case"
};

int iskey(char *s)
{
    int i;
    for(i=0;i<14;i++)
        if(strcmp(s,kw[i])==0)
            return 1;
    return 0;
}
%}

%%

[a-zA-Z_][a-zA-Z0-9_]* {
    if(iskey(yytext))
        printf("Keyword: %s\n",yytext);
}

[ \t\n]+ ;
. ;

%%

int yywrap()
{
    return 1;
}

int main()
{
    yylex();
    return 0;
}
