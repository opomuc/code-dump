#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <math.h>

const int DATA_SIZE = 10;  //констанста времени компиляции


int main()
{

    int data[DATA_SIZE] = {};  //инициализация убрана по причине.....

    for (int i = 0; i < DATA_SIZE; i++)
    {
        assert (0 <= i   && i   < DATA_SIZE);
        //assert (0 <= i-1 && i-1 < DATA_SIZE);
        data[i] = rand()*1000 + i;
        //data[i] = data[i-1];
    }

    int n = rand();
    int*  area = (int*)  calloc (n, sizeof (*area));  //(n, sizeof (int));   т.к. area уже объявлена, ее можно использовать в качестве указателя
    char* str  = (char*) calloc (n, sizeof ( *str));  //(n, sizeof (char));

    area[0] = 20;

    free (area);
    area = NULL; // Обнуление указателя,      free (NULL) - не производит ничего

    free (str);
    //free (area);  повторное free - ошибка


}

