char* read_word(FILE* program) {

    char* word = (char*) calloc (5, sizeof(char*));
    int c;
    int i = 0;
    int length = 5;

        do {

            c = fgetc(program);

            if (length <= i + 1) {

                length = length + length / 2;
                word = (char*) realloc (word, length * sizeof(char*));

            }

            word[i] = c;
            i++;

        } while (c != ' ' && c != EOF);

    return word;

}
