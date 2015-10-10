#include <cstdio>
#include <cstdlib>
#include <cstring>

#include "read_from_file.h"


char* Eq;
char buf[100];
int buf_count = 0;

int GetG0(char* st);
int GetN();
int GetE();
int GetT();
int GetP();

int main()
{
    FILE*  in = fopen("input.txt", "r");
 //   FILE* out = fopen("output.txt", "w");

    char* str = read_string(in);
    int result = 0;
    int bracket_count = 0;

    try
    {
        int length = strlen(str);

        for (int i = 0; i < length; i++)
        {
            if (str[i] == '(')
            {
                if ('0' <= str[i+1] && str[i+1] <= '9' || str[i+1] == '(')
                {
                    bracket_count++;
                }
                else
                {
                    throw 2;
                }
            }

            if (str[i] == ')')
            {
                if (str[i+1] == '+' || str[i+1] == '-' || str[i+1] == '*' || str[i+1] == '/' || str[i+1] == '\0' || str[i+1] == ')')
                {
                    bracket_count--;
                }
                else
                {
                    throw 2;
                }
            }
        }
        if (bracket_count != 0)
        {
            throw 2;
        }

        result = GetG0(str);
    }
    catch (int error)
    {
        switch (error)
        {
            case 0:
            {
                printf("# Division by zero. ");
                break;
            }
            case 1:
            {
                printf("# Unknown error. ");
                break;
            }
            case 2:
            {
                printf("# Wrong bracket order. ");
                break;
            }
            case 3:
            {
                printf("# Wrong symbolic equation. ");
                break;
            }
        }

        printf("Program will be terminated #");
        free(str);
        fclose(in);
        return 0;
    }

    for(int i = 0; i < buf_count; i++)
    {
        printf("%c", buf[i]);
    }

    printf("\n\n%d", result);

    free(str);
 //   fclose(out);
    fclose(in);
    return 0;

}

int GetG0(char* st)
{
    Eq = st;

    int res = 0;

    if (*Eq == '(' || ('0' <= *Eq && *Eq <= '9'))
    {
        res = GetE();
    }
    else
    {
        throw 1;
    }

    if (*Eq != '\0')
    {
        throw 1;
    }

    return res;
}

int GetN()
{
    int val = 0;

    while ('0' <= *Eq && *Eq <= '9')
    {
        val = val*10 + *Eq - '0';
        buf[buf_count++] = *Eq;
        Eq++;
    }
    return val;
}

int GetE()
{
    int val = GetT();

    while (*Eq == '+' || *Eq == '-')
    {
        int op = *Eq;
        Eq++;

        if (*Eq < '0' || '9' < *Eq)
        {
            throw 3;
        }

        int val2 = GetT();

        if (op == '+')
        {
            val += val2;
            buf[buf_count++] = op;
        }
        if (op == '-')
        {
            val -= val2;
            buf[buf_count++] = op;
        }
    }
    return val;
}

int GetT()
{
    int val = GetP();

    while (*Eq == '*' || *Eq == '/')
    {
        int op = *Eq;
        Eq++;

        if ((*Eq < '0' || '9' < *Eq) && *Eq != '(')
        {
            throw 3;
        }
        else
        {
        int val2 = GetP();

        if (op == '*')
        {
            val *= val2;
            buf[buf_count++] = op;
        }
        if (op == '/')
        {
            if (val2 == 0)
            {
                throw 0;
            }

            val = val / val2;
            buf[buf_count++] = op;
        }
        }
    }
    return val;
}

int GetP()
{
    if (*Eq == '(')
    {
        Eq++;

        int val = GetE();
        if (*Eq == ')')
        {
            Eq++;
        }
        else
        {
            throw 2;
        }
        return val;

    }
    else
    {
        return GetN();
    }
}
