%{
#include<stdio.h>
%}
%%
[6-9][0-9]{9} { printf("Valid Mobile Number\n"); }
.+ { printf("Invalid Mobile Number\n"); }
\n ;
%%
int yywrap() { return 1; }
int main() { yylex(); return 0; }