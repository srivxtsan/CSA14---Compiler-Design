%{
#include<stdio.h>
%}
%%
"oldword" { printf("newword"); }
. ECHO;
\n ECHO;
%%
int yywrap() { return 1; }
int main() { yylex(); return 0; }