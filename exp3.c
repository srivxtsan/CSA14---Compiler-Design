#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    char input[200];
    printf("Enter code: ");
    fgets(input, sizeof(input), stdin);
    
    char output[200];
    int j = 0;
    
    for (int i = 0; input[i] != '\0'; i++) {
        if (input[i] == ' ' || input[i] == '\t' || input[i] == '\n') {
            continue;
        }
        if (input[i] == '/' && input[i+1] == '/') {
            while (input[i] != '\0' && input[i] != '\n') i++;
            continue;
        }
        if (input[i] == '/' && input[i+1] == '*') {
            i += 2;
            while (input[i] != '\0') {
                if (input[i] == '*' && input[i+1] == '/') {
                    i += 2;
                    break;
                }
                i++;
            }
            i--;
            continue;
        }
        output[j++] = input[i];
    }
    output[j] = '\0';
    
    printf("Cleaned output: %s\n", output);
    
    return 0;
}
