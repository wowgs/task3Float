#include <stdio.h>
#include <string.h>
int main ()
{
    char c;
    int flag = 0;
    char st[2];
    FILE *f = fopen("input.txt", "r");
    if (f == NULL)
    {
        printf("File not found");
        return;
    }

    while((st[0] = fgetc(f)) != EOF)
    {
    if ((st[0] == '/') && (st[1] == '/'))
    {
        flag = 1;
    }
    if (flag == 1)
    {
        if (st[0] == '/')
        {
            st[0]=fgetc(f);
        }
        printf("%c", st[0]);
    }

    if (st[0] == '\n')
    {
        flag = 0;
    }
    st[1]=st[0];
    }

}
