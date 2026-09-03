%{
#include<stdio.h>
%}
%%
(0[1-9]|[12][0-9]|3[01])[-/](0[1-9]|1[012])[-/](19|20)[0-9]{2} { printf("Valid DOB\n"); }
.+ { printf("Invalid DOB\n"); }
\n ;
%%
int yywrap() { return 1; }
int main() { yylex(); return 0; }