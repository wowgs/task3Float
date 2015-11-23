union floatInt
{
    unsigned int i;
    float f;
};

int main()
{
    int i = 0;
    float number;

    union floatInt u;
    scanf("%f", &number);
    u.f = number;

    int sign = u.i >> 31 & 1;
    int exp = u.i >> 23 & 0xff;
    int m = u.i & (0x7fffff);

    if (exp == 0xff)
    {
        if (m == 0)
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
        printf("%5d %29c%-d\n", sign, ' ', exp-127);
        printf("(-1) * 1.");
        for (i = 22; i > 0; i--)
        {
            printf("%d", (m >> i) & 1);
        }
        printf(" * 2");

    }


    system("pause");
    return 0;
}
