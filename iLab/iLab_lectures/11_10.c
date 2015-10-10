#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main()
{
    int theData[10] = {10, 20, 30};

    Sum(theData, sizeof(theData) / sizeof(*theData)); //   !!!!!!

    const int res[...] = ...

    *(int*)res[0] = 0 //позволяет изменить адрес, т.к. применено приведение типа (int*)


    int* res  = Select(theData, ..., res); // изначально передается указатель конечного массива. \
                        массив при этом меняется, однако вопрос о времени жизни решается сам собой

    // имя задается в зависимости от действия функции

    int* res2 = Select(theData2, ... )  // При вторичном вызове, данные массива res будут потеряны, \
                                        т.к. использована статическая переменная


    char* str = NULL;                //
                                     //  в адрес записываем само значение
    strcpy ((char*)&str, "ABC");     //



    //Sum(theData, 10)
    //&theData - излишне

}

int Sum(int data[], int size) //можно выделить нулевой элемент, который будет являться концом массива/строки
{
    int s = sizeof(data) / sizeof(*data) //   sizeof *(data), sizeof *data, sizeof (data[0])

    return sum;
}

int* Select(const int data[], int size) // const int size  писать не обязательно
{
    int s = sizeof(data) / sizeof(*data);

    //int* result = calloc ...

    //int result[constanta] = ...  -  не передает массив, а лишь указатель на временную память

    //static int result[constanta] = ... // статическая переменная - значение не будет удалено после завершения функции



    return result;



}
