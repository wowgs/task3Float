int main()
{
    int i = 0;
    float number;

    scanf("%f",&number);

    int *f = (int*)&number;

    int sign = *f >> 31 & 1;
    int exp = *f >> 23 & 0xff;
    int m = *f & (0x7fffff);

    if (exp == 0xff)
    {
        if (m = 0)
        {
            printf((sign ? "-inf" : "+inf"));
        }

        else
        {
            printf("NaN");
        }
    }
    else
    {
        printf("%5d %29c%-d\n",sign,' ',exp-127);
        printf("(-1) * 1.");
        for (i = 22; i > 0; i--)
        {
            printf("%d", (m >> i)& 1);
        }
        printf(" * 2");

    }


    system("pause");
    return 0;
}
