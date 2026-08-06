#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int main() {
    char input[100];
    printf("Enter a line of code: ");
    fgets(input, sizeof(input), stdin);
    
    int i = 0;
    while (input[i] != '\0') {
        if (input[i] == ' ' || input[i] == '\t' || input[i] == '\n') {
            i++;
            continue;
        }
        
        if (isalpha(input[i]) || input[i] == '_') {
            printf("IDENTIFIER: ");
            while (isalnum(input[i]) || input[i] == '_') {
                printf("%c", input[i]);
                i++;
            }
            printf("\n");
        }
        else if (isdigit(input[i])) {
            printf("CONSTANT: ");
            while (isdigit(input[i])) {
                printf("%c", input[i]);
                i++;
            }
            printf("\n");
        }
        else if (input[i] == '+' || input[i] == '-' || input[i] == '*' || 
                 input[i] == '/' || input[i] == '=' || input[i] == '<' || 
                 input[i] == '>' || input[i] == '!' || input[i] == '&' || 
                 input[i] == '|') {
            printf("OPERATOR: %c\n", input[i]);
            i++;
        }
        else if (input[i] == '(' || input[i] == ')' || input[i] == '{' || 
                 input[i] == '}' || input[i] == ';' || input[i] == ',') {
            printf("DELIMITER: %c\n", input[i]);
            i++;
        }
        else {
            i++;
        }
    }
    
    return 0;
}
