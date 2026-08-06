#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    char input[200];
    int spaces = 0, newlines = 0, tabs = 0;
    
    printf("Enter text (press Ctrl+D or type 'END' on new line to finish):\n");
    
    while (fgets(input, sizeof(input), stdin) != NULL) {
        if (strcmp(input, "END\n") == 0) break;
        
        for (int i = 0; input[i] != '\0'; i++) {
            if (input[i] == ' ') spaces++;
            else if (input[i] == '\n') newlines++;
            else if (input[i] == '\t') tabs++;
        }
    }
    
    printf("Total spaces: %d\n", spaces);
    printf("Total tabs: %d\n", tabs);
    printf("Total newlines: %d\n", newlines);
    
    return 0;
}
