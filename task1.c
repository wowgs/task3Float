#include <stdio.h>
#include <string.h>
int main ()
{
    const int SIZE = 512;
    char st;
    char s[SIZE];
    printf("Enter your string ");
    gets(s);
    printf("Enter your character");
    scanf("%c", &st);
    int i = 0;
    while (s[i] != '\0')
    {
        if (s[i] != st)
        {
            printf("%c", s[i]);
        }
        i++;
    }
}

