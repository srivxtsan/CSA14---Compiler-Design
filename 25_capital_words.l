%{
#include<stdio.h>
%}
%%
[A-Z]+ { printf("Capital word: %s\n", yytext); }
[a-zA-Z]+ ;
.|\n ;
%%
int yywrap() { return 1; }
int main() { yylex(); return 0; }