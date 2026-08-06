#include <stdio.h>
#include <stdlib.h>

int main() {
    printf("Top-Down Parsing (LL(1) Predictive Parser)\n\n");
    
    printf("Grammar:\n");
    printf("E -> TE'\n");
    printf("E' -> +TE' / epsilon\n");
    printf("T -> FT'\n");
    printf("T' -> *FT' / epsilon\n");
    printf("F -> (E) / id\n\n");
    
    printf("LL(1) Parsing Table:\n");
    printf("========================================\n");
    printf("Non-T | id      | +      | *      | (      | )      | $\n");
    printf("------+---------+--------+--------+--------+--------+---\n");
    printf("E     | TE'     | -      | -      | TE'    | -      | -\n");
    printf("E'    | -       | +TE'   | -      | -      | eps    | eps\n");
    printf("T     | FT'     | -      | -      | FT'    | -      | -\n");
    printf("T'    | -       | eps    | *FT'   | -      | eps    | eps\n");
    printf("F     | id      | -      | -      | (E)    | -      | -\n");
    printf("========================================\n\n");
    
    printf("Where:\n");
    printf("- eps = epsilon (empty production)\n");
    printf("- - = error/invalid\n\n");
    
    printf("Parsing Process for 'a+b*c':\n");
    printf("1. Start with E (top of stack)\n");
    printf("2. Look at input 'a', use E -> TE' (from table)\n");
    printf("3. Continue matching and applying productions\n");
    printf("4. If all input consumed and stack empty, ACCEPT\n\n");
    
    printf("Advantages of Top-Down Parsing:\n");
    printf("- No backtracking needed\n");
    printf("- Efficient for LL(1) grammars\n");
    printf("- Easy to implement\n");
    
    return 0;
}
