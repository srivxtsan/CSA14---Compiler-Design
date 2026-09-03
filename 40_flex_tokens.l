%{
#include<stdio.h>
%}
%%
int|float|char|void|if|else|while|for|return { printf("FLEX Keyword: %s\n", yytext); }
[a-zA-Z_][a-zA-Z0-9_]* { printf("FLEX Identifier: %s\n", yytext); }
.|\n ;
%%
int yywrap() { return 1; }
int main() { yylex(); return 0; }