#include <stdio.h>
void float1(float number)
{
    union floatInt
    {
        unsigned int i;
        float f;
    };

    union floatInt u;
    u.f = number;
    unsigned int sign = u.i >> 31 & 1;
    unsigned int exp = u.i >> 23 & 0xff;
    unsigned int m = u.i & (0x7fffff);
    printFloat(sign, exp, m);
}

float2(float number)
{
    struct bits
    {
        unsigned int m:23;
        unsigned int e:8;
        unsigned int s:1;
    };

    union floatint
    {
        float f;
        struct bits b;
    };
    union floatint u;
    u.f = number;
    int sign = u.b.s;
    int exp = u.b.e;

    int m = u.b.m;
    printFloat(sign, exp, m);
}

void float3(float number)
{
    int *f = (int*)&number;
    unsigned int sign = *f >> 31 & 1;
    unsigned int exp = *f >> 23 & 0xff;
    unsigned int m = *f & (0x7fffff);
    printFloat(sign, exp, m);
}
int printFloat(int sign, int exp, int m)
{
    int i = 0;
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
    printf("\n");
}

int main()
{
    float f1, f2;
    scanf("%f %f", &f1, &f2);
    float1(f1 / f2);
    float2(f1 / f2);
    float3(f1 / f2);
    system("pause");
    return 0;
}
