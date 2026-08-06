#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

char *input_str;
int pos = 0;

int parseE();
int parseEPrime();
int parseT();
int parseTPrime();
int parseF();

int parseE() {
    if (!parseT()) return 0;
    if (!parseEPrime()) return 0;
    return 1;
}

int parseEPrime() {
    if (input_str[pos] == '+') {
        pos++;
        if (!parseT()) return 0;
        if (!parseEPrime()) return 0;
    }
    return 1;
}

int parseT() {
    if (!parseF()) return 0;
    if (!parseTPrime()) return 0;
    return 1;
}

int parseTPrime() {
    if (input_str[pos] == '*') {
        pos++;
        if (!parseF()) return 0;
        if (!parseTPrime()) return 0;
    }
    return 1;
}

int parseF() {
    if (input_str[pos] == '(') {
        pos++;
        if (!parseE()) return 0;
        if (input_str[pos] == ')') {
            pos++;
        } else return 0;
    }
    else if (isalpha(input_str[pos])) {
        pos++;
    }
    else return 0;
    return 1;
}

int main() {
    char input[100];
    printf("Enter expression (use single letters for identifiers, +*() operators):\n");
    printf("Example: a+b*c or (a+b)*c\n");
    printf("Enter: ");
    scanf("%s", input);
    
    input_str = input;
    pos = 0;
    
    printf("\nParsing expression: %s\n", input);
    printf("Grammar:\n");
    printf("E -> TE'\n");
    printf("E' -> +TE' / epsilon\n");
    printf("T -> FT'\n");
    printf("T' -> *FT' / epsilon\n");
    printf("F -> (E) / id\n\n");
    
    if (parseE() && input_str[pos] == '\0') {
        printf("Result: Expression is VALID!\n");
    } else {
        printf("Result: Expression is INVALID!\n");
        printf("Parsing stopped at position %d\n", pos);
    }
    
    return 0;
}
