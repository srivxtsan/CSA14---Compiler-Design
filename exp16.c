#include <stdio.h>
#include <stdlib.h>

int main() {
    printf("Compiler Backend - Code Generation\n");
    printf("====================================\n\n");
    
    printf("Backend Components:\n");
    printf("-------------------\n");
    printf("1. Intermediate Code Optimizer\n");
    printf("   - Simplifies three address code\n");
    printf("   - Removes dead code\n");
    printf("   - Optimizes loops\n\n");
    
    printf("2. Code Generator\n");
    printf("   - Converts optimized code to assembly\n");
    printf("   - Allocates registers\n");
    printf("   - Manages memory\n\n");
    
    printf("3. Assembly Code Generator\n");
    printf("   - Produces machine-specific assembly code\n");
    printf("   - Handles target architecture instructions\n\n");
    
    printf("4. Linker\n");
    printf("   - Links object files\n");
    printf("   - Resolves external references\n");
    printf("   - Produces executable\n\n");
    
    printf("Example Translation:\n");
    printf("====================\n");
    printf("Source Code: c = a + b * 2;\n\n");
    
    printf("Three Address Code:\n");
    printf("  t1 = b * 2\n");
    printf("  t2 = a + t1\n");
    printf("  c = t2\n\n");
    
    printf("Optimized TAC:\n");
    printf("  t1 = b << 1      (multiply by 2 is bit shift)\n");
    printf("  c = a + t1\n\n");
    
    printf("Assembly Code (x86):\n");
    printf("  MOV eax, [b]     ; Load b into eax\n");
    printf("  SHL eax, 1       ; Shift left by 1 (multiply by 2)\n");
    printf("  ADD eax, [a]     ; Add a to eax\n");
    printf("  MOV [c], eax     ; Store result in c\n\n");
    
    printf("Object Code:\n");
    printf("  Machine instructions in binary format\n\n");
    
    printf("Executable (after linking):\n");
    printf("  Final binary file ready to run\n");
    
    return 0;
}
