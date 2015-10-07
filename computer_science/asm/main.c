
//#include "stdafx.h"
#include "stdio.h"
#include "math.h"

#define max 16777214
#define lenth 25
#define lenth2 50
#define mem 255

int memory[mem][lenth];

typedef struct
{
	int comm;
	int af;
	int as;
} command;

command acom[mem];

void wmemory(int addr)
{
    int i = 0;
    for (i = 0; i < lenth; i++)
    {
        memory[addr][i] = memory[0][i];
    }
}

void equal(int* first, int* second, int* result)
{
    int i = 0;
    for (i = 0; i < lenth; i++)
    {
        *(result+i) = ((*(first+i) && *(second+i)) || (*(first+i) || *(second+i))) ? 0 : 1;
    }
}

int dec_in_bin(long dec, int *bin)
{
    int i, k = 0, sign = 0, move = 1; // why do we need parameter k??
    long dc;

    if (dec < 0)
    {
        sign = 1;
    }

    dc = fabs(dec);

    if (dc > max)
    {
        return 1;
    }

    for (i = 0; i < lenth; i++)
    {
        *(bin+k++) = (!sign) ? dc%2 : !(dc%2);
       // *(bin++) = (!sign) ? dc%2 : !(dc%2);
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

long bin_in_dec(int *bin)
{
    int i, k = 1, move = 1, n = 0, sign;
    sign = *(bin+lenth-1);
    for (i = 0; i < lenth-1; i++)
    {
        if (!sign) n = n + *(bin+i)*k;
        else if (move && *(bin+i))
        {
            n = n + k;
            move = 0;
        }
	    else if (!move && !(*(bin+i)))
	    {
            n = n + k;
        }
        k = k*2;
    }
    if (sign) n = -n;

    return n;
}

int addition(int *first, int *second, int *result, int len)
{
    int i, move = 0;

    for (i = 0; i < len-1; i++)
    {
        if (move)
        {
            if (*(first+i) && *(second+i))
            {
                *(result+i) = 1;
	        }
            else
            {
                if (*(first+i) || *(second+i))
                {
                    *(result+i) = 0;
                }
                else
                {
                    *(result+i) = 1;
                    move = 0;
                }
            }
        }
        else
        {
            if (*(first+i) && *(second+i))
            {
                *(result+i) = 0;
                move = 1;
            }
	        else
	        {
                *(result+i) = (*(first+i) || *(second+i)) ? 1 : 0;
	        }
        }
    }
    if (move)
    {
        if (!(*(first+len-1) || *(second+len-1)))
        {
            return 2;
        }
        else
        {
            if (*(first+len-1) && *(second+len-1))
            {
                *(result+len-1) = 1;
            }
            else
            {
                *(result+len-1) = (*(first+len-1) || *(second+len-1)) ? 0 : 1;
            }
        }
    }
 //   else        // why? move is 0 after addition so the result is not a big number
 //   {
   //     if (*(first+len-1) && *(second+len-1))
     //   {
       //     return 2;
 //       }
   //     else
     //   {
       //     *(result+len-1)= (*(first+len-1) || *(second+len-1)) ? 1 : 0;
 //       }
 //   }

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


int substraction(int *first, int *second, int *result, int len)
{
    int re[lenth2];
    sign(second, &re[0], len);
    return addition(first, &re[0], result, len);
}

int multiplication(int *first, int *second, int *result, int len)
{
    int i = 0, j = 0, num = 0, num2 = 0, sgn = 0, intern[lenth2], dsecond[lenth2];
                      // variable  num2 is unnecessary
    sgn = ((*(first+len-1) && *(second+len-1)) || !(*(first+len-1) || *(second+len-1))) ? 0 : 1;
               // if they are both negative    or     if both are NOT negative
    for (i = 0; i < len; i++)
    {
        intern[i] = *(first+i);        // why do we need to copy both numbers?
        dsecond[i] = *(second+i);      //
        *(result+i) = 0;
    }
    if (*(first+len-1))
    {
        sign(first, &intern[0], len);
    }
    if (*(second+len-1))
    {
        sign(second, &dsecond[0],len);
    }
    for (i = 0; i < len-2; i++)
	{
        if (dsecond[i])
		{
            if (num2)
            {
                return 3;
            }

            num = addition(result, &intern[0], result, len);

            if (num)
            {
                return 3;
            }
        }
        if (intern[len-2])
        {
            num2 = 3;
        }
        for (j = len-2; j > 0; j--)
        {
            intern[j] = intern[j-1];
        }

        intern[0] = 0;
    }

    if (sgn)
    {
        sign(result, result, len);
    }

    return 0;
}

int division(int *first, int *second, int *result)
{
    int i = 0, j = 0, order = 0, sgn = 0, sgn2 = 0, res = 0;
    int intern[lenth2], dsec[lenth2], dsec2[lenth], dsecond[lenth2], dsecond2[lenth2], dfirst[lenth2], dres[lenth2];

    sgn = ((*(first+lenth-1) && *(second+lenth-1)) || !(*(first+lenth-1) || *(second+lenth-1))) ? 0 : 1;

    for (i = 0; i < lenth2; i++)
    {
        dfirst[i] = intern[i] = dsecond[i] = dsecond2[i] = dres[i] = 0;
    }
    for (i = 0; i < lenth; i++)
    {
        dfirst[i] = *(first+i);
        dsecond[i] = *(second+i);
        dsecond2[i] = dsec[i] = dsec2[i] = 0;
    }
    if (*(first+lenth-1))
    {
        sign(first, &dfirst[0], lenth);
    }
    if (*(second+lenth-1))
    {
        sign(second, &dsecond[0], lenth);
    }
    for (res = i = 0; i < lenth; i++)
    {
        if (dfirst[i] != dsecond[i])
        {
            res = 1;
            break;
        }
    }
    if (!res)
    {
        for (i = 1; i < lenth; i++)
        {
            *(result+i) = 0;
        }
        *(result) = 1;

        if (sgn)
        {
            sign(result, result, lenth);
        }
        return 0;
    }
    for (i = 0; i < lenth-1; i++)
    {
        if (dsecond[i])
        {
            order = i + 1;
            sgn2++;
        }
    }

    if (!order)
    {
            return 4;
    }
    if (order == 1)
	{
        for (i = 0; i < lenth; i++)
        {
            *(result+i) = dfirst[i];
        }
        if (sgn)
        {
            sign(result, result, lenth);
        }
        return 0;
	}

    for (i = 0; i < lenth; i++)
    {
        dfirst[i+lenth] = dfirst[i];
        dfirst[i] = 0;
    }
    for (i = (sgn2 == 1) ? 1 : 0; i < order; i++)
    {
        for (j = 0; j < lenth2-1; j++)
        {
            dfirst[j] = dfirst[j+1];
        }
    }
    if (sgn2 == 1)
    {
        for (i = 0; i < lenth; i++)
        {
        *(result+i) = dfirst[lenth+i];
        }
        if (sgn)
        {
            sign(result, result, lenth);
            return 0;
        }
    }
    for (i = 0; i < lenth2; i++)
    {
        dres[i] = dfirst[i];
    }

    dsec[order] = dsec2[order] = 1;
    substraction(&dsec[0], &dsecond[0], &dsecond[0], lenth);

    for (i=0; i<lenth; i++)
    {
        dsecond2[i] = dsecond[i];
    }

    do
    {
        for (i = 0; i < lenth2; i++)
        {
            intern[i] = dfirst[i];
        }

        i = res = 0;

        while (!dsec[i++])
        {
            for (j = 1; j < lenth2; j++)
            {
                intern[j-1] = intern[j];
            }
        }
        for (j = 0; j < lenth2; j++)
        {
            if (intern[j])
            {
                res = 1;
                break;
            }
        }
        if (!res)
        {
            res = dres[lenth-1];
            break;
        }

        multiplication(&dsecond[0], &intern[0], &intern[0], lenth2);
        addition(&dres[0], &intern[0], &dres[0], lenth2);
        multiplication(&dsecond2[0], &dsecond[0], &dsecond[0], lenth2);
        multiplication(&dsec2[0], &dsec[0], &dsec[0], lenth2);

    } while (res);

    for (i = 0; i < lenth; i++)
    {
        *(result+i) = dres[lenth+i];
    }
    if (res)
    {
        for (i = 0; i < lenth; i++)
        {
            if (*(result+i))
            {
                *(result+i) = 0;
            }
            else
            {
                *(result+i) = 1;
                break;
            }
        }
    }

    sgn2 = 1;

    for (i = 0; i < lenth; i++)
    {
        if (sgn2)
        {
            if (*(result+i))
            {
                dres[i] = 0;
            }
            else
            {
                dres[i] = 1;
                sgn2 = 0;
            }
		}
        else
        {
            dres[i] = *(result+i);
        }
	}
    if (sgn)
    {
        sign(result, result, lenth);
    }

    return 0;
}

void error(int flag)
{
	switch (flag)
	{
	    case 1: printf("\n\tenter big numer"); break;
        case 2: printf("\n\taddition big numer"); break;
		case 3: printf("\n\tmultiplication big numer"); break;
        case 4: printf("\n\tdivision by zero"); break;
		case 5: printf("\n\tnegative root"); break;
        case 6: printf("\n\tunknown command"); break;
		default:printf("\n\tunknown error");
}
}

int jump0(int* first)
{
    int i = 0;
    for (i = 0; i < lenth; i++)
    {
        if(*(first+i)) return 0;
    }
    return 1;
}

int jump1(int* first)
{
    int i = 0;
    for (i = 0; i < lenth; i++)
    {
        if(*(first+i)) return 1;
    }
    return 0;
}

void monitor()
{
	int ccount = 0, eflag = 0, jump = 0, num = 0;

	do
	{
        eflag = jump = 0;

        switch (acom[ccount].comm)
        {
            case 0: {return;}
            case 1:
            {
                eflag = addition(&memory[acom[ccount].af][0], &memory[acom[ccount].as][0], &memory[0][0], lenth);
                break;
            }
            case 2:
            {
                eflag = substraction(&memory[acom[ccount].af][0], &memory[acom[ccount].as][0], &memory[0][0], lenth);
                break;
            }
            case 3:
            {
                eflag = multiplication(&memory[acom[ccount].af][0], &memory[acom[ccount].as][0], &memory[0][0], lenth);
                break;
            }
            case 4:
            {
                eflag = division(&memory[acom[ccount].af][0], &memory[acom[ccount].as][0], &memory[0][3]);
                break;
            }
            case 5:
            {
                equal(&memory[acom[ccount].af][0], &memory[acom[ccount].as][0], &memory[0][0]);
                break;
            }
            case 6:
            {
                jump = jump0(&memory[acom[ccount].af][0]);
                break;
            }
            case 7:
            {
                jump = jump1(&memory[acom[ccount].af][0]);
                break;
            }
            case 20:
            {
                num = acom[ccount].af;
                wmemory(num);
                break;
            }
            case 21:
            {
                num = acom[ccount].af;
                printf("\n\t Adress = %d value = %d\n", num, bin_in_dec(&memory[num][0]));
                break;
            }
            default:
            {
                printf("\n\tunknown command");
                return;
            }
        }

        if (eflag)
        {
            error(eflag);
            return;
        }
        if (jump)
        {
            ccount = acom[ccount].as;
        }
        else ccount++;

	} while (acom[ccount].comm);

	printf("\n\tResult:%d", bin_in_dec(&memory[0][0]));

}

void assembler()
{
	int i = 0, var = 0, cc = 0, nc = 0, ncount = 1, ccount = 0;
	long num = 0;

	do
	{
		printf("\n\t select numbers = 1, commands = 2, program = 3  ");
		scanf("%d", &var);

		switch (var)
		{
            case 1:
            {
                do
                {
                    printf("\n\taddress = %d\tenter address = ", ncount);
                    scanf("%d", &nc);
                    if (!nc)
                    {
                        break;
                    }
                    printf("\tenter number = ");
                    scanf("%d", &num);

                    i = dec_in_bin(num, &memory[nc][0]);

                    if (i)
                    {
                        break;
                    }
                    if (ncount <= nc) ncount = nc + 1;

                } while (nc);

                break;
            }
            case 2:
            {
                do
                {
                    printf("\n\taddress = %d\tenter address = ", ccount);
                    scanf("%d", &cc);
                    printf("\tenter command = ");
                    scanf("%d", &acom[cc].comm);
                    if (!acom[cc].comm)
                    {
                        break;
                    }
                    printf("\tenter first = ");
                    scanf("%d", &acom[cc].af);
                    printf("\tenter second = ");
                    scanf("%d", &acom[cc].as);
                    if (ccount <= cc)
                    {
                        ccount = cc+1;
                    }
                } while (acom[cc].comm);

                break;
            }
            case 3:
            {
                printf("\n\n\tNUMBERS");

                for (i = 1; i < ncount; i++)
                {
                    printf("\n\taddres = %d\t number = %ld", i, bin_in_dec(&memory[i][0]));
                }

                printf("\n\n\tCOMMANDS");

                for (i = 0; i <= ccount; i++)
                {
                    printf("\n\taddres = %d\t command = %d\t first = %d\t second = %d" , i, acom[i].comm, acom[i].af, acom[i].as);
                }
            }
            default:
            {
                printf("\n\tWrong choice");
                break;
            }
        }
    } while (var);

    printf("\n\tend of assembly\n");
}




int main()
{
	printf("\n\tHaven't seen you for ages!");
	assembler();
    monitor();
    printf("\n\n\tSee you soon!\n");

	return 0;
}
