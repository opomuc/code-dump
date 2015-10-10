
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "read_from_file.h"

// IN: 	 a pointer to an opened file with text
// DOES: reads a string from file
// OUT:  a pointer to a string, the string ends with \0

char* read_string (FILE* program, const char* delims /* = " \n" */) {

    char* word = (char*) calloc (10, sizeof(char));
    char c;
    int i = 0;
    int length = 10;

    do {

        c = fgetc(program);

        if (length <= i + 1) {

            length = length * 2;
            word = (char*) realloc (word, length * sizeof(char));

        }

        word[i] = c;
        i++;

    } while (! (delims && strchr (delims, c) || c == EOF) );

    word[i - 1] = '\0';

    return word;

}
