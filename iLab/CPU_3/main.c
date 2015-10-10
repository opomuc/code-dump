#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "cpu.h"
#include "cpu.c"
#include "read_from_file.h"
#include "read_from_file.c"

int CPU_code_make(CPU_t* cpu, FILE* prog);

int main() {

    FILE* program;
    CPU_t cpu;

    CPU_construct(&cpu);
    program = fopen("input.txt", "rt");

    int code_size = CPU_code_make(&cpu, program);
    int i = 0;
    bool flag = true;

    do {

        switch (cpu.code[i]) {

            case 0 : {

                flag = false;
                break;

            }
            case 1 : {

                Stack_push(cpu.stack_cpu, cpu.code[i+1]);
                i = i + 2;
                break;

            }
            case 2 : {

                printf("%d\n", Stack_pop(cpu.stack_cpu));
                i++;
                break;

            }
            case 3 : {

                Stack_push(cpu.stack_cpu, cpu.ax);
                i++;
                break;

            }
            case 4 : {

                CPU_add(&cpu);
                i++;
                break;

            }
            case 5 : {

                CPU_sub(&cpu);
                i++;
                break;

            }
            case 6 : {

                CPU_mul(&cpu);
                i++;
                break;

            }
            case 7 : {

                CPU_div(&cpu);
                i++;
                break;

            }
            case 8 : {

                CPU_dump(&cpu);
                i++;
                break;

            }
            default: {

                printf("Program terminated -> # Bad code #\n"
                       "Code size          -> # %d #\n"
                       "Bad command number -> # %d #", code_size, i + 1);

                flag = false;
                break;

            }
        }

    }
    while (flag && i < code_size); // *false*  means something went wrong, technically any mistake in the code goes on default, which prints an error message
				   // *true*  means program is working well and continues to the end of the code

    CPU_destruct(&cpu);
    fclose(program);
    return 0;

}

// IN:   a pointer to cpu, a pointer to an opened file with assemled code
// DOES: allocates a block of memory for an array of code, fills it with number representetives of cpu commands
// OUT:  returns a size of actual code (not the size of allocated memory)

int CPU_code_make(CPU_t* cpu, FILE* prog) {

    assert(cpu);

    char* cmd_str;
    int cmd_int = 0;
    int c_size = 10;
    int num = 0;

    for (num = 0; !feof(prog); num++) {

        cmd_str = read_word(prog);
        cmd_int = atoi(cmd_str);
        if (c_size <= num + 1) {

            c_size = c_size * 2;
            cpu->code = (int*) realloc (cpu->code, c_size * sizeof(int));

        }

        cpu->code[num] = cmd_int;

    }

    return num;

}
