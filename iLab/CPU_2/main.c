#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "cpu.h"

int main() {

    char com[30];
    int  arg;
    int x = 10;

    CPU_t cpu;
    CPU_construct(&cpu);

    do {

        scanf("%s", com);

        if ((strcmp(com, "push")) == 0) {

                scanf("%d\n", &arg);
                if (!Stack_push(cpu.stack_cpu, arg)) {

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

                CPU_dump(&cpu);

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
        else if ((strcmp(com, "push_ax")) == 0) {

            Stack_push(cpu.stack_cpu, cpu.ax);

        }
        else if ((strcmp(com, "mov")) == 0) {

            CPU_mov_ax(&cpu, x);

        }
        else if ((strcmp(com, "dstr")) == 0) {

            Stack_destruct(cpu.stack_cpu);

        }
        else if ((strcmp(com, "end")) == 0) {

            break;

        }
        else {printf("Wrong command!\n");}

    } while (true);

    CPU_destruct(&cpu);

    return 0;

}
