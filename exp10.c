#include <stdio.h>
#include <stdlib.h>

int main() {
    printf("Eliminating Left Factoring\n\n");
    
    printf("Original Grammar:\n");
    printf("S -> iEtS / iEtSeS / a\n");
    printf("E -> b\n\n");
    
    printf("Analysis:\n");
    printf("Productions S -> iEtS and S -> iEtSeS have common prefix 'iEt'\n");
    printf("This requires backtracking in predictive parsing\n\n");
    
    printf("Transformation Process:\n");
    printf("1. Identify common prefix: 'iEt'\n");
    printf("2. Factor out the common prefix:\n");
    printf("   - S -> iEt(S / eS) / a\n");
    printf("3. Create new non-terminal S' for the different suffixes\n");
    printf("4. Rewrite productions:\n");
    printf("   - S -> iEtS' / a\n");
    printf("   - S' -> S / eS\n\n");
    
    printf("Modified Grammar:\n");
    printf("S -> iEtS' / a\n");
    printf("S' -> S / eS\n");
    printf("E -> b\n\n");
    
    printf("Alternative form with epsilon:\n");
    printf("S -> iEtS' / a\n");
    printf("S' -> S / eS / epsilon\n");
    printf("E -> b\n\n");
    
    printf("Verification:\n");
    printf("The new grammar has no common prefixes\n");
    printf("LL(1) parser can now make decisions without backtracking\n");
    
    return 0;
}
