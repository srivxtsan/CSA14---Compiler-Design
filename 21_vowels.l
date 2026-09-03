%{
#include<stdio.h>
int v=0;
%}
%%
[aeiouAEIOU] { v++; }
.|\n ;
%%
int yywrap() { return 1; }
int main() { yylex(); printf("Vowels: %d\n", v); return 0; }