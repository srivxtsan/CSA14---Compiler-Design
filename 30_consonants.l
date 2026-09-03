%{
#include<stdio.h>
int c=0;
%}
%%
[bcdfghjklmnpqrstvwxyzBCDFGHJKLMNPQRSTVWXYZ] { c++; }
.|\n ;
%%
int yywrap() { return 1; }
int main() { yylex(); printf("Consonants: %d\n", c); return 0; }