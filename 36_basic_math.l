%{
#include<stdio.h>
%}
%%
[0-9]+ { printf("Number: %s\n", yytext); }
[+\-*/] { printf("Operator: %s\n", yytext); }
.|\n ;
%%
int yywrap() { return 1; }
int main() { yylex(); return 0; }