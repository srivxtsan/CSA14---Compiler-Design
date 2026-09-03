%{
#include<stdio.h>
int pos=0, neg=0;
%}
%%
[-][0-9]+(\.[0-9]+)? { neg++; }
[+]?[0-9]+(\.[0-9]+)? { pos++; }
.|\n ;
%%
int yywrap() { return 1; }
int main() { yylex(); printf("Positive: %d, Negative: %d\n", pos, neg); return 0; }