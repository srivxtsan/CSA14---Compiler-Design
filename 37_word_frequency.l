%{
#include<stdio.h>
#include<string.h>
int count = 0;
char target[] = "compiler";
%}
%%
[a-zA-Z]+ { if(strcasecmp(yytext, target) == 0) count++; }
.|\n ;
%%
int yywrap() { return 1; }
int main() { yylex(); printf("Frequency of '%s': %d\n", target, count); return 0; }