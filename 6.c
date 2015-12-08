#include <stdio.h>
#include <string.h>
int main()
{
    int i, j;
    char s1[1000];
    int arr[1000] = {0};
    int n;
    printf("Please, enter your n = ");
    scanf("%d", &n);
    for (i = 0; i < n; i++)
    {
        scanf("%s", &s1);
        for (j = 0; j < strlen(s1); j++)
        {
            arr[j] = arr[j] ^ (int)s1[j];
        }
    }
      printf("%s", arr);
}
