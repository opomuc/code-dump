#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main()
{
    int theData[10] = {10, 20, 30};

    Sum(theData, sizeof(theData) / sizeof(*theData)); //   !!!!!!

    const int res[...] = ...

    *(int*)res[0] = 0 //��������� �������� �����, �.�. ��������� ���������� ���� (int*)


    int* res  = Select(theData, ..., res); // ���������� ���������� ��������� ��������� �������. \
                        ������ ��� ���� ��������, ������ ������ � ������� ����� �������� ��� �����

    // ��� �������� � ����������� �� �������� �������

    int* res2 = Select(theData2, ... )  // ��� ��������� ������, ������ ������� res ����� ��������, \
                                        �.�. ������������ ����������� ����������


    char* str = NULL;                //
                                     //  � ����� ���������� ���� ��������
    strcpy ((char*)&str, "ABC");     //



    //Sum(theData, 10)
    //&theData - �������

}

int Sum(int data[], int size) //����� �������� ������� �������, ������� ����� �������� ������ �������/������
{
    int s = sizeof(data) / sizeof(*data) //   sizeof *(data), sizeof *data, sizeof (data[0])

    return sum;
}

int* Select(const int data[], int size) // const int size  ������ �� �����������
{
    int s = sizeof(data) / sizeof(*data);

    //int* result = calloc ...

    //int result[constanta] = ...  -  �� �������� ������, � ���� ��������� �� ��������� ������

    //static int result[constanta] = ... // ����������� ���������� - �������� �� ����� ������� ����� ���������� �������



    return result;



}
