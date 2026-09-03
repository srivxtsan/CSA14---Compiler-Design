%{
#include<stdio.h>
%}
%%
(http|https):\/\/[a-zA-Z0-9.-]+\.[a-zA-Z]{2,}.* { printf("Valid URL\n"); }
.+ { printf("Invalid URL\n"); }
\n ;
%%
int yywrap() { return 1; }
int main() { yylex(); return 0; }