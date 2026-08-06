#include <stdio.h>
#include <stdlib.h>

int main() {
    printf("TRAILING() - Operator Precedence Parser\n");
    printf("========================================\n\n");
    
    printf("Grammar:\n");
    printf("E -> E + T | T\n");
    printf("T -> T * F | F\n");
    printf("F -> (E) | id\n\n");
    
    printf("TRAILING Sets (Terminals that can follow a production):\n");
    printf("=========================================================\n");
    printf("TRAILING(E) = {+, ), $}\n");
    printf("  - E appears in: E + T (followed by +)\n");
    printf("  - E appears in: (E) (followed by ))\n");
    printf("  - E is start symbol (followed by $)\n\n");
    
    printf("TRAILING(T) = {+, *, ), $}\n");
    printf("  - T appears in: E + T (followed by +)\n");
    printf("  - T appears in: T * F (followed by *)\n");
    printf("  - T appears in: (E) where E ends (followed by ))\n");
    printf("  - T is start symbol (followed by $)\n\n");
    
    printf("TRAILING(F) = {+, *, ), $}\n");
    printf("  - F appears in: T * F (followed by *)\n");
    printf("  - F appears in: (E) where T ends (followed by ))\n");
    printf("  - F appears in: (E) where E ends (followed by ))\n");
    printf("  - F is start symbol (followed by $)\n\n");
    
    printf("TRAILING(+) = {+}\n");
    printf("TRAILING(*) = {*}\n");
    printf("TRAILING(() = {(}\n");
    printf("TRAILING()) = {)}\n");
    printf("TRAILING(id) = {id}\n\n");
    
    printf("Complete Operator Precedence Matrix Using TRAILING:\n");
    printf("========================================================\n");
    printf("       | +  | *  | (  | )  | id | $\n");
    printf("-------+----+----+----+----+----+---\n");
    printf("+      | >  | <  | <  | >  | <  | >\n");
    printf("*      | >  | >  | <  | >  | <  | >\n");
    printf("(      | <  | <  | <  | =  | <  | X\n");
    printf(")      | >  | >  | X  | >  | X  | >\n");
    printf("id     | >  | >  | X  | >  | X  | >\n");
    printf("$      | <  | <  | <  | X  | <  | =\n\n");
    
    printf("Usage in Parsing:\n");
    printf("- LEADING: determines what can start a nonterminal\n");
    printf("- TRAILING: determines what can follow a nonterminal\n");
    printf("- Together: build the operator precedence relations\n");
    
    return 0;
}
