#include <stdio.h>
#include <stdlib.h>

int main() {
    printf("LEADING() - Operator Precedence Parser\n");
    printf("=======================================\n\n");
    
    printf("Grammar:\n");
    printf("E -> E + T | T\n");
    printf("T -> T * F | F\n");
    printf("F -> (E) | id\n\n");
    
    printf("LEADING Sets (Terminals that can start a production):\n");
    printf("=======================================================\n");
    printf("LEADING(E) = {(, id}\n");
    printf("  - E can start with E + T: starts with LEADING(E) = {(, id}\n");
    printf("  - E can start with T: starts with LEADING(T) = {(, id}\n\n");
    
    printf("LEADING(T) = {(, id}\n");
    printf("  - T can start with T * F: starts with LEADING(T) = {(, id}\n");
    printf("  - T can start with F: starts with LEADING(F) = {(, id}\n\n");
    
    printf("LEADING(F) = {(, id}\n");
    printf("  - F can start with (E): starts with '('\n");
    printf("  - F can start with id: starts with 'id'\n\n");
    
    printf("LEADING(+) = {+}\n");
    printf("LEADING(*) = {*}\n");
    printf("LEADING(() = {(}\n");
    printf("LEADING()) = {)}\n");
    printf("LEADING(id) = {id}\n\n");
    
    printf("Operator Precedence Matrix:\n");
    printf("============================\n");
    printf("       | +  | *  | (  | )  | id | $\n");
    printf("-------+----+----+----+----+----+---\n");
    printf("+      | >  | <  | <  | >  | <  | >\n");
    printf("*      | >  | >  | <  | >  | <  | >\n");
    printf("(      | <  | <  | <  | =  | <  | X\n");
    printf(")      | >  | >  | X  | >  | X  | >\n");
    printf("id     | >  | >  | X  | >  | X  | >\n");
    printf("$      | <  | <  | <  | X  | <  | =\n\n");
    
    printf("Key:\n");
    printf("  < = reduce (precedence is higher)\n");
    printf("  > = shift (precedence is lower)\n");
    printf("  = = equal precedence\n");
    printf("  X = error\n");
    
    return 0;
}
