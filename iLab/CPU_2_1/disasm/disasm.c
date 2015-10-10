#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {

    FILE* prog_text;
    FILE* prog_num;
    int cmd = 0;
    int arg = 0;

    prog_text = fopen("output.txt", "wt");
    prog_num = fopen("input.txt", "rt");

    do {

        fscanf(prog_num, "%d", &cmd);

        switch (cmd) {

            case 0: {

                fprintf(prog_text, "end\n");
                break;
            }
            case 1: {

                fscanf(prog_num, "%d", &arg);
                fprintf(prog_text, "push %d\n", arg);
                break;
            }
            case 2: {

                fprintf(prog_text, "pop\n");
                break;
            }
            case 3: {

                fprintf(prog_text, "push_ax\n");
                break;
            }
            case 4: {

                fprintf(prog_text, "add\n");
                break;
            }
            case 5: {

                fprintf(prog_text, "sub\n");
                break;
            }
            case 6: {

                fprintf(prog_text, "mul\n");
                break;
            }
            case 7: {

                fprintf(prog_text, "div\n");
                break;
            }
            case 8: {

                fprintf(prog_text, "dump\n");
                break;
            }
            default: break;
        }

    }
    while (!feof(prog_num));

    fclose(prog_text);
    fclose(prog_num);

    return 0;

}
