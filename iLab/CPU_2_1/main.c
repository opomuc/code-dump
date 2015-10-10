#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "cpu.h"

int CPU_run(CPU_t* cpu, const char* prog);

int main() {

    int  x = -10;
    int  y = 0;

    CPU_t cpu;
    CPU_construct(&cpu);

    while (x <= 10) {

        CPU_mov_ax(&cpu, x);
        y = CPU_run(&cpu, "input.txt");
        printf("x = %d, y = %d\n", x, y);
        x++;

    }

    CPU_destruct(&cpu);

    return 0;

}

int CPU_run(CPU_t* cpu, const char* prog) {

    assert(cpu);

    FILE* program;

    char com[30];
    int arg = 0;
    program = fopen(prog, "rt");

    while (!feof(program)) {

    fscanf(program, "%s", com);

    if ((strcmp(com, "push")) == 0) {

        fscanf(program, "%d\n", &arg);
        Stack_push(cpu->stack_cpu, arg);

    }
    else if ((strcmp(com, "pop")) == 0) {

        if (cpu->stack_cpu->counter != 0) printf("\n%d\n\n", Stack_pop(cpu->stack_cpu));

    }
    else if ((strcmp(com, "add")) == 0) {

        if (!CPU_add(cpu)) {printf("Wrong arguments\n");}

    }
    else if ((strcmp(com, "dump")) == 0) {

        CPU_dump(cpu);

    }
    else if ((strcmp(com, "mul")) == 0) {

        if (!CPU_mul(cpu)) {printf("Wrong arguments!\n");}

    }
    else if ((strcmp(com, "sub")) == 0) {

        if (!CPU_sub(cpu)) {printf("Wrong arguments!\n");}

    }
    else if ((strcmp(com, "div")) == 0) {

        if (!CPU_div(cpu)) {printf("Wrong arguments!\n");}

    }
    else if ((strcmp(com, "push_ax")) == 0) {

        Stack_push(cpu->stack_cpu, cpu->ax);

    }
    else if ((strcmp(com, "end")) == 0) {

        break;

    }
    }

    fclose(program);

    return Stack_pop(cpu->stack_cpu);

}
