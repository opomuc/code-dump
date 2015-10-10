/** **********************************************************************************
 * @file    qsort_1.c
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


void swap1(int* a, int* b);
void quick_sort(int* data, int length);

int main()
{
    int data[ARRAY_SIZE], i = 0, length = 0;

    printf("The program sorts a sequence from min to max value\n\n");
    printf("Please insert the number of elements: ");
    scanf("%d", &length);
    printf("Now insert each element of the sequence: ");

    for (i = 0; i <= length - 1; i++)
    {
        scanf("%d", &data[i]);
    }

    quick_sort (data, length - 1);

    printf("Sorted sequence: ");

    for (i = 0; i <= length - 1; i++)
    {
        printf("%d ", data[i]);
    }

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
