#include <stdio.h>
#include <stdlib.h>

int main() {
    printf("Grammar: S -> AaAb / BbBa, A -> epsilon, B -> epsilon\n\n");
    
    printf("Computing FIRST():\n\n");
    
    printf("FIRST(A):\n");
    printf("  - A -> epsilon\n");
    printf("  - FIRST(A) = {epsilon}\n\n");
    
    printf("FIRST(B):\n");
    printf("  - B -> epsilon\n");
    printf("  - FIRST(B) = {epsilon}\n\n");
    
    printf("FIRST(S):\n");
    printf("  - S -> AaAb\n");
    printf("    - FIRST(A) = {epsilon}, so check next symbol\n");
    printf("    - Add 'a' to FIRST(S)\n");
    printf("  - S -> BbBa\n");
    printf("    - FIRST(B) = {epsilon}, so check next symbol\n");
    printf("    - Add 'b' to FIRST(S)\n");
    printf("  - Both A and B contain epsilon, so S can derive epsilon\n");
    printf("  - FIRST(S) = {a, b, epsilon}\n\n");
    
    printf("RESULT:\n");
    printf("FIRST(S) = {a, b, epsilon}\n");
    printf("FIRST(A) = {epsilon}\n");
    printf("FIRST(B) = {epsilon}\n");
    
    return 0;
}
