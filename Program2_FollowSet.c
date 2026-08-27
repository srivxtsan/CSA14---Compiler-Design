#include <stdio.h>

int main()
{
    char followS[] = "$";
    char followA[] = "b";
    char followB[] = "$";

    printf("FOLLOW(S) = { %s }\n", followS);
    printf("FOLLOW(A) = { %s }\n", followA);
    printf("FOLLOW(B) = { %s }\n", followB);

    return 0;
}
