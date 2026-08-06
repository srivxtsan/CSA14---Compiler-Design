#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char name[50];
    char type[20];
    char scope[20];
    int value;
} Symbol;

int main() {
    Symbol symbolTable[100];
    int count = 0;
    int choice;
    
    while (1) {
        printf("\n=== Symbol Table Operations ===\n");
        printf("1. Insert Symbol\n");
        printf("2. Search Symbol\n");
        printf("3. Delete Symbol\n");
        printf("4. Display All Symbols\n");
        printf("5. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);
        
        if (choice == 1) {
            printf("Enter symbol name: ");
            scanf("%s", symbolTable[count].name);
            printf("Enter type (int/float/char/string): ");
            scanf("%s", symbolTable[count].type);
            printf("Enter scope (global/local): ");
            scanf("%s", symbolTable[count].scope);
            printf("Enter value: ");
            scanf("%d", &symbolTable[count].value);
            count++;
            printf("Symbol inserted successfully!\n");
        }
        else if (choice == 2) {
            char search[50];
            printf("Enter symbol name to search: ");
            scanf("%s", search);
            int found = 0;
            for (int i = 0; i < count; i++) {
                if (strcmp(symbolTable[i].name, search) == 0) {
                    printf("\nFound Symbol:\n");
                    printf("Name: %s\n", symbolTable[i].name);
                    printf("Type: %s\n", symbolTable[i].type);
                    printf("Scope: %s\n", symbolTable[i].scope);
                    printf("Value: %d\n", symbolTable[i].value);
                    found = 1;
                    break;
                }
            }
            if (!found) printf("Symbol not found!\n");
        }
        else if (choice == 3) {
            char search[50];
            printf("Enter symbol name to delete: ");
            scanf("%s", search);
            int found = 0;
            for (int i = 0; i < count; i++) {
                if (strcmp(symbolTable[i].name, search) == 0) {
                    for (int j = i; j < count - 1; j++) {
                        symbolTable[j] = symbolTable[j + 1];
                    }
                    count--;
                    printf("Symbol deleted successfully!\n");
                    found = 1;
                    break;
                }
            }
            if (!found) printf("Symbol not found!\n");
        }
        else if (choice == 4) {
            if (count == 0) {
                printf("Symbol table is empty!\n");
            } else {
                printf("\n=== Symbol Table ===\n");
                printf("%-15s %-12s %-10s %-10s\n", "Name", "Type", "Scope", "Value");
                printf("----------------------------------------------\n");
                for (int i = 0; i < count; i++) {
                    printf("%-15s %-12s %-10s %-10d\n", 
                           symbolTable[i].name, symbolTable[i].type, 
                           symbolTable[i].scope, symbolTable[i].value);
                }
            }
        }
        else if (choice == 5) {
            printf("Exiting...\n");
            break;
        }
        else {
            printf("Invalid choice!\n");
        }
    }
    
    return 0;
}
