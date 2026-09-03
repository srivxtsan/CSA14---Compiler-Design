%{
#include<stdio.h>
%}
%%
[0-9]+(\.[0-9]+)? { printf("Constant: %s\n", yytext); }
.|\n ;
%%
int yywrap() { return 1; }
int main() { yylex(); return 0; }