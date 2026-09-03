%{
#include<stdio.h>
#include<string.h>
int max_len = 0;
char longest[100];
%}
%%
[a-zA-Z]+ { 
    if(yyleng > max_len) { 
        max_len = yyleng; 
        strcpy(longest, yytext); 
    } 
}
.|\n ;
%%
int yywrap() { return 1; }
int main() { yylex(); printf("Longest word: %s\n", longest); return 0; }