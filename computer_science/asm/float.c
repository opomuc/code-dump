#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <float.h>

#define length   64
#define length1  52

int double_to_bin(double num, int* memory);
int dec_in_bin(long dec, int *bin);
void sign(int *second, int *result, int len);


int main()
{
    int   memory[20][length];
    double a = -3513.56;

    printf("%d\n", double_to_bin(a, &memory[0][0]));

    for (int i = 0; i < length1; i++)
    {
        memory[1][i] = memory[0][length1-i-1];
    }
    for (int i = 0; i < length1; i++)
    {
        printf("%d", memory[1][length1-i-1]);
    }

    return 0;
}

int dec_in_bin(long dec, int *bin)
{
    int i, k = 0, sign = 0, move = 1; // why do we need parameter k??
    long dc;

    dc = fabs(dec);

    for (i = 0; i < length1; i++)
    {
        *(bin+k++) = (!sign) ? dc%2 : !(dc%2);
        dc = dc/2;
        if (sign && move)
        {
            if (*(bin+k-1))
            {
                *(bin+k-1) = 0;
            }
            else
            {
                *(bin+k-1) = 1;
                move = 0;
            }
        }
    }

    return 0;
}

void sign(int *second, int *result, int len)
{
    int i, sn = 0;
    for (i = 0; i < len; i++)
    {
        if (sn)
        {
            *(result+i) = !*(second+i);
        }
        else
        {
            if (*(second+i))
            {
                *(result+i) = 1;
                sn = 1;
            }
            else *(result+i) = 0;
        }
    }
}

int double_to_bin(double num, int* mem)
{
    //printf("not implemented");

 //   if (num > DBL_MAX || (num < DBL_MIN && > DBL_EPSILON))
 //   {
 //       return 2;
 //   }

    if (num < DBL_EPSILON)
    {
        *(mem+length-1) = 1;
    }
    else
    {
        *(mem+length-1) = 0;
    }


    long dec  = (long) num;
    dec_in_bin(dec, mem);

    long frac = 0;

    return 0;
}
