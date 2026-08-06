#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    char input[200];
    printf("Enter a line: ");
    fgets(input, sizeof(input), stdin);
    
    int i = 0;
    while (input[i] != '\0' && input[i] != '\n') {
        if (input[i] == '/' && input[i+1] == '/') {
            printf("Found single-line comment: ");
            i += 2;
            while (input[i] != '\0' && input[i] != '\n') {
                printf("%c", input[i]);
                i++;
            }
            printf("\n");
            return 0;
        }
        else if (input[i] == '/' && input[i+1] == '*') {
            printf("Found multi-line comment: ");
            i += 2;
            while (input[i] != '\0') {
                if (input[i] == '*' && input[i+1] == '/') {
                    printf("%c%c\n", input[i], input[i+1]);
                    return 0;
                }
                printf("%c", input[i]);
                i++;
            }
            printf("\nWarning: Unclosed comment!\n");
            return 0;
        }
        i++;
    }
    printf("No comments found\n");
    
    return 0;
}
