#include <stdio.h>
#include <stdlib.h>

int main() {
    printf("Eliminating Left Recursion\n\n");
    
    printf("Original Grammar:\n");
    printf("S -> (L) / a\n");
    printf("L -> L , S / S\n\n");
    
    printf("Analysis:\n");
    printf("The production L -> L , S has left recursion\n");
    printf("This means L appears at the beginning of the right side\n\n");
    
    printf("Transformation Process:\n");
    printf("1. Identify the left recursive production: L -> L , S / S\n");
    printf("2. Separate into left-recursive and non-recursive parts:\n");
    printf("   - Left-recursive part: L , S\n");
    printf("   - Non-recursive part: S\n");
    printf("3. Create new non-terminal L' for the recursive part\n");
    printf("4. Apply transformation:\n");
    printf("   - L -> S L'\n");
    printf("   - L' -> , S L' / epsilon\n\n");
    
    printf("Modified Grammar:\n");
    printf("S -> (L) / a\n");
    printf("L -> S L'\n");
    printf("L' -> , S L' / epsilon\n\n");
    
    printf("Verification:\n");
    printf("The new grammar has no left recursion\n");
    printf("It generates the same language as the original grammar\n");
    
    return 0;
}
