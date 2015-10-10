#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "cpu.h"

int main() {

    char com[] = "";
    int  num = 0;

    CPU_t cpu;
    CPU_construct(&cpu);

    while ((scanf("%s", com)) != EOF) {

        if ((strcmp(com, "push")) == 0) {

                scanf("%d\n", &num);
                if (!Stack_push(cpu.stack_cpu, num)) {

                    printf("Stack overflow!\n");

                }

            }
        else if ((strcmp(com, "pop")) == 0) {

               if (cpu.stack_cpu->counter != 0) printf("\n%d\n\n", Stack_pop(cpu.stack_cpu));

            }
        else if ((strcmp(com, "add")) == 0) {

                if (!CPU_add(&cpu)) {printf("Wrong arguments\n");}

            }
        else if ((strcmp(com, "dump")) == 0) {

                Stack_dump(cpu.stack_cpu);

            }
        else if ((strcmp(com, "mul")) == 0) {

                if (!CPU_mul(&cpu)) {printf("Wrong arguments!\n");}

            }
        else if ((strcmp(com, "sub")) == 0) {

                if (!CPU_sub(&cpu)) {printf("Wrong arguments!\n");}

            }
        else if ((strcmp(com, "div")) == 0) {

                if (!CPU_div(&cpu)) {printf("Wrong arguments!\n");}

            }
        else {printf("Wrong command!\n");}

    }

    CPU_destruct(&cpu);

    return 0;

}
