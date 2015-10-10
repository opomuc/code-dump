#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "read_from_file.h"
#include "read_from_file.c"

int main() {

    FILE* prog_text;
    FILE* prog_num;
    char* cmd_str;
    int cmd_int = 0;
    int arg = 0;

    prog_text = fopen("output.txt", "wt");
    prog_num = fopen("input.txt", "rt");

    do {

        cmd_str = read_string(prog_num);
        cmd_int = atoi(cmd_str);

        switch (cmd_int) {

            case 0: {

                fprintf(prog_text, "end\n");
                break;
            }
            case 1: {

                fprintf(prog_text, "push ");
                for (int i = 2; i <= strlen(cmd_str); i++) {

                    fprintf(prog_text, "%c", cmd_str[i]);

                }
                fprintf(prog_text, "\n");
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
            default: {

                printf("    # Bad code #");
                fprintf(prog_text, "    # Bad code #");
                fclose(prog_text);
                fclose(prog_num);

                exit(1);

            }
        }

    }
    while (!feof(prog_num));

    fclose(prog_text);
    fclose(prog_num);
    return 0;
}
