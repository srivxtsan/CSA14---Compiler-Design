#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int main() {
    char identifier[100];
    printf("Enter identifier: ");
    scanf("%s", identifier);
    
    if (!isalpha(identifier[0]) && identifier[0] != '_') {
        printf("Invalid: Identifier must start with letter or underscore\n");
        return 0;
    }
    
    for (int i = 1; identifier[i] != '\0'; i++) {
        if (!isalnum(identifier[i]) && identifier[i] != '_') {
            printf("Invalid: Identifier contains invalid character '%c'\n", identifier[i]);
            return 0;
        }
    }
    
    printf("Valid identifier\n");
    
    return 0;
}
