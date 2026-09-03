%{
#include<stdio.h>
%}
%%
^[0-9]+$ { printf("Is a digit\n"); }
.+ { printf("Not a digit\n"); }
\n ;
%%
int yywrap() { return 1; }
int main() { yylex(); return 0; }