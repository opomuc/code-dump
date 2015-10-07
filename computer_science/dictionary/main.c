#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

void swap_string(char* a, char* b);

int main() {

    char eng[100][30];
    char rus[100][30];
    int i = 0;
    int j = 0;
    int cmd;
    char wrong[30];
    char right[30];

    do {

        scanf("%d", &cmd);
        switch (cmd) {

            case 0: {break;}
            case 1: {

                scanf("%s %s", &eng[i][0], &rus[i][0]);
                i++;
                j++;
                break;

            }
            case 2: {

                scanf("%s %s", &wrong, &right);
                for (i = 0; i < j; i++) {

                    if (strcmp(&eng[i][0], wrong) == 0) {

                        strcpy(&eng[i][0], right);

                    }

                }
                break;
            }
            case 3: {

                scanf("%s %s", &wrong, &right);
                for (i = 0; i < j; i++) {

                    if (strcmp(&eng[i][0], wrong) == 0) {

                        strcpy(&rus[i][0], right);

                    }

                }
                break;
            }
            case 4: {

                scanf("%s", &wrong);
                for (i = 0; i < j; i++) {

                    if (strcmp(&eng[i][0], wrong) == 0) {

                        strcpy(&eng[i][0], "\0");
                        strcpy(&rus[i][0], "\0");
                                                          }
                }
                break;
            }
            case 5: {

                int num_swaps = 0;

                do {

                    for (int k = 0; k <= j - 2; k++) {

                        if (strcmp(&eng[k][0], &eng[k+1][0]) > 0) {

                            swap_string(&eng[k][0], &eng[k+1][0]);
                            swap_string(&rus[k][0], &rus[k+1][0]);
                            num_swaps++;

                        }
                    }

                    if (num_swaps > 0) {num_swaps = 0;}
                    else {num_swaps = -1;}

                }
                while (num_swaps >= 0);

                break;

            }
            case 6: {

                do {

                    scanf("%s", &wrong);

                    for (i = 0; i < j; i++) {

                        if (strcmp(&eng[i][0], wrong) == 0) {

                            printf("%s ", &rus[i][0]);

                        }

                    }

                } while (strcmp(wrong, "\n") == 0);

                printf("\n");
                break;

            }
            case 7: {

                printf("\n      DICTIONARY\n");
                for (i = 0; i < j; i++) {

                    printf("    # %s %s\n", &eng[i], &rus[i]);

                }
                printf("\n");
                break;

            }
            case 9: {

                printf("\n\t# 1 - add a new word"
                       "\n\t# 2 - change the english word"
                       "\n\t# 3 - change the translation"
                       "\n\t# 4 - delete the word from the dictionary"
                       "\n\t# 5 - sorting by alphabet"
                       "\n\t# 6 - translate the sentence"
                       "\n\t# 7 - print the dictionary"
                       "\n\t# 0 - exit\n\n");
                break;
            }
            default: {printf("Wrong command! Use help (9)\n"); break;}
        }

    } while (cmd != 0);

    return 0;
}

void swap_string(char* a, char* b) {

    char c[30];

    strcpy(c, a);
    strcpy(a, b);
    strcpy(b, c);

}
