struct bits
{
    int m:23;
    int e:8;
    int s:1;
};

union floatint
{
    float f;
    struct bits b;
};

int main()
{
    int i = 0;
    float number;

    union floatint u;
    scanf("%f", &number);
    u.f = number;

    int sign = u.b.s;
    int exp = u.b.e;
    int m = u.b.m;

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
        printf("%5d %28c %-d\n", sign, ' ', exp-127);
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
