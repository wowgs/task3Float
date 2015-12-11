#include <stdio.h>
int main ()
{
    char num1[100] = "10011";
    char num2[100] = "0111";
    int dif;
    int max = strlen(num1) > strlen(num2) ? strlen(num1) : strlen(num2);
    int i;
    for (i = strlen(num1); i < max; i++)
    {
        num1[i] = '0';
    }
    for (i = strlen(num2); i < max; i++)
    {
        num2[i] = '0';
    }
    i = max - 1;
    while ((num1[i] == num2[i]) && (num1[i] != '\0'))
    {
        i--;
    }
    dif = num1[i] - num2[i];

    if (dif == 0)
    {
        printf("=");
    }
    else if (dif < 0 )
    {
        printf("<");
    }
    else
    {
        printf(">");
    }
}