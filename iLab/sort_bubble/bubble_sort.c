/** **********************************************************************************
 * @file    bubble_sort.c
 * @date    2013-10-08 01:00
 * @author  Roman Proskin <roman.proskin@frtk.ru>
 * @version 1.0.1
 *
 * @par Sorts a random sequence
 *
 * @warning works good :)
**************************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

const int ARRAY_SIZE = 32000;

void bubble_sort(int* data, int length);
void swap1(int* a, int* b);

int main()
{
    int data[ARRAY_SIZE], i = 0, length = 0;

    printf("The program sorts a sequence from min to max value\n\n");
    printf("Please insert the number of elements: ");
    scanf("%i", &length);
    printf("Now insert each element of the array: ");

    for (i = 0; i < length; i++)
    {
        scanf("%i", &data[i]);
    }

    bubble_sort(data, length);

    for (i = 0; i < length; i++)
    {
        printf("%i ", data[i]);
    }

    return 0;
}

void bubble_sort(int* data, int length)
{
    int num_swaps = 0;

    do
    {
        for (int i = 0; i < length - 1; i++)
        {
            if (data[i] > data[i+1])
            {
                swap1(&data[i], &data[i+1]);
                num_swaps = num_swaps + 1;
            }
        }

        if (num_swaps > 0) num_swaps = 0;
        else num_swaps = -1;
    }
    while (num_swaps >= 0);
}

void swap1(int* a, int* b)
{
    int temp = 0;

    temp = *a;
    *a = *b;
    *b = temp;
}
