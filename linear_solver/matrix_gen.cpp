#include <iostream>
#include <fstream>
#include <ctime>
#include <stdio.h>
#include <stdlib.h>

using namespace std;

int main()
{
    srand(time(NULL));
    ofstream output;
    output.open("in.txt");
    int n = 0;
    cout << "Please, enter N- the order of the matrix\n";
    cin >> n ;
    int **a = new int* [n];
    for (int i = 0; i < n; i++)
    {
        a[i] = new int [n];
    }

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            a[i][j] = rand() % 10;
            //cout << a[i][j] << " ";
        }
        //cout << endl;
    }
     //printf ("!!!!!!!!!!!!!!!!!!!!\n") ;
    int* b = new int [n];
    for (int i = 0; i < n; i++)
    {
        b[i] = rand()%10;
        //cout << b[i] << " ";
    }
    //cout << endl;


    output << 0.001 << endl;
    output << n << endl;
    for (int i=0; i<n;i++)
    {
        output << b[i] << endl;
    }

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            output << a[i][j] << endl;
        }
    }

    for (int i = 0; i < n; i++)
    {
        free(a[i]);
    }
    free(b);
    free(a);
    cout << "Matrix is generated\n";
	output.close();
    return 0;
}