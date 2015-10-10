/** **********************************************************************************
 * @file    qsort_unknown.c
 * @date    2013-10-09 19:00
 * @author  Roman Proskin <roman.proskin@frtk.ru>
 * @version 1.0.0
 *
 * @par Sorts an entered set of numbers
 *
 * @warning do not input decimals
**************************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <assert.h>

const int DATA_SIZE = 5;

void quick_sort(int* data, int length);
void swap1(int* a, int* b);

int main()
{
    int* data = (int*) calloc(DATA_SIZE, sizeof(*data));
    int  num_size = DATA_SIZE, c = 0;

    printf("to end type .");

    for (int i = 0; i <= num_size - 1; i++)
    {
        assert(0 < i && i <= num_size - 1);
        assert(data != NULL);

        scanf("%d", &data[i]);
        c = getchar();

        if (c != '.' && i == num_size - 1)
        {
            num_size = num_size + 1;
            data = (int*) realloc(data, num_size * sizeof(*data));
        }

        if (c == '.')
        {
            //data = (int*) realloc(data, num_size * sizeof(int));
            break;
        }
    }

    quick_sort(data, num_size);
    printf("\n");

    for (int i = 0; i <= num_size - 1; i++)
    {
        printf("%d ", data[i]);
    }

    free(data);
    return 0;

}

/** ********************************************************************************
 quick_sort - sorts a random sequence

 @param   mass         The sequence
 @param   elements     The number of elements

 @note    maximum of n*ln(n) operations
************************************************************************************/

void quick_sort(int* data, int length)
{
    int right = length, left = 0;
    int middle = data[length/2];

    do
    {
        while (data[left] < middle)
        {
            left++;
        }
        while (data[right] > middle)
        {
            right--;
        }

        if (left <= right)
        {
            swap1(&data[left], &data[right]);
            left++;
            right--;
        }

    }
    while (left < right);

    if (right > 0)
    {
        quick_sort(data, right);
    }

    if (left < length)
    {
        quick_sort(data + left, length - left);
    }

}

/** ********************************************************************************
 swap1 - swaps two numbers in places

 @param     a     First number
 @param     b     Second number

************************************************************************************/

void swap1(int* a, int* b)
{
    int temp = 0;

    temp = *a;
    *a = *b;
    *b = temp;
}
