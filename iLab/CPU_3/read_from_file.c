// IN: 	 a pointer to an opened file with text
// DOES: reads a word (a string number) from file. Space is the symbol of the end of a word (a string number).
// OUT:  a pointer to a string containing a word (a string number), the string ends with \0

char* read_word(FILE* program) {

    char* word = (char*) calloc (5, sizeof(char));
    int c;
    int i = 0;
    int length = 5;

    do {

        c = fgetc(program);

        if (length <= i + 1) {

            length = length * 2;
            word = (char*) realloc (word, length * sizeof(char));

        }

        word[i] = c;
        i++;

    } while (c != ' ' && c != '\n' && c != EOF);

    word[i - 1] = '\0';

    return word;

}

// IN: 	 a pointer to an opened file with text
// DOES: reads a string from file
// OUT:  a pointer to a string, the string ends with \0

char* read_string(FILE* program) {

    char* word = (char*) calloc (5, sizeof(char));
    int c;
    int i = 0;
    int length = 5;

    do {

        c = fgetc(program);

        if (length <= i + 1) {

            length = length * 2;
            word = (char*) realloc (word, length * sizeof(char));

        }

        word[i] = c;
        i++;

    } while (c != '\n' && c != EOF);

    word[i - 1] = '\0';

    return word;

}
