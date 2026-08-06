#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    char input[100];
    printf("Enter expression: ");
    fgets(input, sizeof(input), stdin);
    
    char validOps[] = {'+', '-', '*', '/'};
    
    for (int i = 0; input[i] != '\0'; i++) {
        for (int j = 0; j < 4; j++) {
            if (input[i] == validOps[j]) {
                printf("Valid operator found: %c\n", input[i]);
            }
        }
    }
    
    return 0;
}
