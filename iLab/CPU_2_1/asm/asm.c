#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {

    FILE* prog_text;
    FILE* prog_num;
    char cmd[20];
    int arg = 0;

    prog_text = fopen("input.txt", "rt");
    prog_num = fopen("output.txt", "wt");

    do {

        fscanf(prog_text, "%s", cmd);

        if ((strcmp(cmd, "push")) == 0) {

            fscanf(prog_text, "%d", &arg);
            fprintf(prog_num, "1 %d\n", arg);

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

    } while (!feof(prog_text));

    fclose(prog_text);
    fclose(prog_num);

    return 0;
}
