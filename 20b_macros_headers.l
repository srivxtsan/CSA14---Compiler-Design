%{
#include<stdio.h>
int macros=0, headers=0;
%}
%%
^#define.* { macros++; }
^#include.* { headers++; }
.|\n ;
%%
int yywrap() { return 1; }
int main() { 
    yylex(); 
    printf("Macros: %d\nHeaders: %d\n", macros, headers); 
    return 0; 
}