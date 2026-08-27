%{
#include <stdio.h>

int v = 0, c = 0;
%}

%%

[aeiouAEIOU]    { v++; }
[a-zA-Z]        { c++; }
.               ;

%%

int yywrap()
{
    return 1;
}

int main()
{
    printf("Enter a string: ");
    yylex();

    printf("Vowels = %d\n", v);
    printf("Consonants = %d\n", c);

    return 0;
}
