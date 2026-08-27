#include <stdio.h>
#include <ctype.h>

int main()
{
    char str[50];
    int i, valid = 1;

    printf("Enter identifier: ");
    scanf("%s", str);

    if (!(isalpha(str[0]) || str[0] == '_'))
        valid = 0;

    for (i = 1; str[i] != '\0'; i++)
    {
        if (!(isalnum(str[i]) || str[i] == '_'))
        {
            valid = 0;
            break;
        }
    }

    if (valid)
        printf("Valid Identifier");
    else
        printf("Invalid Identifier");

    return 0;
}
