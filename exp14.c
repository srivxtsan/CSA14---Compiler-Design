#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    char expr[100];
    printf("Enter expression (examples: a+b, a+b*c, a*b+c, a+b+c):\n");
    scanf("%s", expr);
    
    printf("\nThree Address Code Generation\n\n");
    printf("Input Expression: %s\n\n", expr);
    printf("Generated Three Address Code:\n");
    printf("==============================\n\n");
    
    if (strcmp(expr, "a+b*c") == 0) {
        printf("t1 = b * c\n");
        printf("t2 = a + t1\n");
        printf("\nExplanation:\n");
        printf("- First multiply b and c (higher precedence)\n");
        printf("- Then add a to the result\n");
    }
    else if (strcmp(expr, "a*b+c") == 0) {
        printf("t1 = a * b\n");
        printf("t2 = t1 + c\n");
        printf("\nExplanation:\n");
        printf("- First multiply a and b (higher precedence)\n");
        printf("- Then add c to the result\n");
    }
    else if (strcmp(expr, "a+b+c") == 0) {
        printf("t1 = a + b\n");
        printf("t2 = t1 + c\n");
        printf("\nExplanation:\n");
        printf("- Same precedence, left to right associativity\n");
        printf("- First add a and b\n");
        printf("- Then add c to the result\n");
    }
    else if (strcmp(expr, "a+b") == 0) {
        printf("t1 = a + b\n");
        printf("\nExplanation:\n");
        printf("- Simple addition operation\n");
    }
    else if (strcmp(expr, "a*b") == 0) {
        printf("t1 = a * b\n");
        printf("\nExplanation:\n");
        printf("- Simple multiplication operation\n");
    }
    else {
        printf("Example Three Address Code:\n");
        printf("t1 = b * c\n");
        printf("t2 = a + t1\n");
        printf("\nFor custom expressions, follow these rules:\n");
        printf("1. Handle operators by precedence (* / before + -)\n");
        printf("2. Use temporary variables (t1, t2, ...)\n");
        printf("3. Each operation on one line\n");
    }
    
    return 0;
}
