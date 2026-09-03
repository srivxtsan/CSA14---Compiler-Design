%{
#include<stdio.h>
%}
%%
int|float|char|void|if|else|while|for|return { printf("Keyword: %s\n", yytext); }
[a-zA-Z_][a-zA-Z0-9_]* { printf("Identifier: %s\n", yytext); }
[0-9]+ { printf("Constant: %s\n", yytext); }
[+\-*/=] { printf("Operator: %s\n", yytext); }
[(){};,] { printf("Punctuation: %s\n", yytext); }
.|\n ;
%%
int yywrap() { return 1; }
int main() { yylex(); return 0; }