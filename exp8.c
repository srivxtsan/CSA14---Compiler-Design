#include <stdio.h>
#include <stdlib.h>

int main() {
    printf("Grammar: S -> AaAb / BbBa, A -> epsilon, B -> epsilon\n\n");
    
    printf("Computing FOLLOW():\n\n");
    
    printf("FOLLOW(S):\n");
    printf("  - S is the start symbol\n");
    printf("  - FOLLOW(S) = {$} (end marker)\n\n");
    
    printf("FOLLOW(A):\n");
    printf("  - From S -> AaAb: 'a' follows A\n");
    printf("  - From S -> BbBa: A doesn't appear\n");
    printf("  - FOLLOW(A) = {a}\n\n");
    
    printf("FOLLOW(B):\n");
    printf("  - From S -> AaAb: B doesn't appear\n");
    printf("  - From S -> BbBa: 'b' follows B\n");
    printf("  - FOLLOW(B) = {b}\n\n");
    
    printf("RESULT:\n");
    printf("FOLLOW(S) = {$}\n");
    printf("FOLLOW(A) = {a}\n");
    printf("FOLLOW(B) = {b}\n");
    
    return 0;
}
