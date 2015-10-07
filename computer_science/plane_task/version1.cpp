#include <iostream>
#include <cstdio>
#include <cmath>
#include <cstdlib>


using namespace std;

int main()
{
    FILE* income;
    FILE* output;
    income = fopen("navy.txt", "r");
    output = fopen("out.txt", "w");

    int i, j = 0, k = 0, point_num = 0, time = 0, n = 0;
    int memory[255] = {};
    int velocity = 20, distance = 0, dx = 0, dy = 0, curr_time = 0;
    int min_d = 99999999;

    do
    {
        for (i = 0; i < 2; i++)
        {
            fscanf(income, "%d ", &memory[j]);
            memory[j] *= 10;
            j++;
        }
        point_num++;
    }
    while (!feof(income));

//    for (i = 0; i < point_num * 2; i++)
//    {
//        printf("\n%d", memory[i]);
//    }

    memory[254] = 0;
    memory[255] = 0;

    for (time = 0; time < 50; time++)
    {
//        memory[100] = (memory[0] - memory[254])*(memory[0]-memory[254]) + (memory[1] - memory[255])*(memory[1]-memory[255]);
//        memory[101] = 0;

         min_d = 9999999;

        for (i = 0, k = 0; i < (point_num - n); i++, k = i*2)
        {
            memory[102] = (memory[k] - memory[254])*(memory[k] - memory[254]) + (memory[k+1] - memory[255])*(memory[k+1] - memory[255]);

     //       printf("\n%d %d", memory[102], i);

            if (memory[102] < min_d)
            {
                min_d = memory[102];
                memory[101] = k;
                printf("\n\n%d %d %d\n\n", min_d, i, k);
            }
        }

        memory[252] = memory[memory[101]];
        memory[253] = memory[memory[101]+1];

        distance = sqrt(min_d);
        curr_time = distance / velocity;

        printf("\n%d %d %d %d", distance, curr_time, memory[252], memory[253]);

        dx = (memory[254] - memory[252]) / curr_time;
        dy = (memory[255] - memory[253]) / curr_time;

        memory[254] -= dx;
        memory[255] -= dy;

        if (((memory[254] - memory[252])*(memory[254] - memory[252]) + (memory[255] - memory[253])*(memory[255] - memory[253])) < 400)
        {
            fprintf(output, "from: (%d,%d);  to: (%d,%d);  target: (%d,%d);  current time: %d;   dx = %d;   dy = %d\n", memory[120], memory[121], memory[254], memory[255], memory[memory[101]], memory[memory[101]+1], time, dx, dy);

            memory[memory[101]] = memory[(point_num - 1 - n)*2];
            memory[memory[101] + 1] = memory[(point_num - 1 - n)*2 + 1];

            n++;
        }
        if (n == 10)
        {
            break;
        }

    }

    fclose(output);
    fclose(income);

    return 0;
}
