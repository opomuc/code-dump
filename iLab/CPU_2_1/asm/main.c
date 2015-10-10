#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "read_from_file.h"
#include "read_from_file.c"

int main() {

    FILE* prog_text;
    FILE* prog_num;
    char* cmd;
    int   len = 0;
    bool  flag = true;

    prog_text = fopen("input.txt", "rt");
    prog_num = fopen("output.txt", "wt");

    do {

        cmd = read_string(prog_text);

        if ((strncmp(cmd, "push ", 5)) == 0) {

            fprintf(prog_num, "1 ");

            len = strlen(cmd);

            for (int i = 5; i <= len - 1; i++) {

                fprintf(prog_num, "%c", cmd[i]);

            }

            fprintf(prog_num, "\n");

        }
        else if ((strcmp(cmd, "pop")) == 0) {

            fprintf(prog_num, "2\n");

        }
        else if ((strcmp(cmd, "push_ax")) == 0) {

            fprintf(prog_num, "3\n");

        }
        else if ((strcmp(cmd, "add")) == 0) {

            fprintf(prog_num, "4\n");

        }
        else if ((strcmp(cmd, "sub")) == 0) {

            fprintf(prog_num, "5\n");

        }
        else if ((strcmp(cmd, "mul")) == 0) {

            fprintf(prog_num, "6\n");

        }
        else if (strcmp(cmd, "div") == 0) {

            fprintf(prog_num, "7\n");

        }
        else if (strcmp(cmd, "dump") == 0) {

            fprintf(prog_num, "8\n");

        }
        else if (strcmp(cmd, "end") == 0) {

            fprintf(prog_num, "0\n");

        }
        else {

            fprintf(prog_num, "-1\n");
            printf("Bad code");
            flag = false;
            break;

        }

    } while (!feof(prog_text));

    fclose(prog_text);
    fclose(prog_num);

    if (flag) return 0;
    else return 1;

}
