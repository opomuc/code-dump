#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "read_from_file.h"
#include "read_from_file.c"

typedef int value_t;

struct Elem {

    char* key_value;
    value_t value;
    Elem* next;

};

typedef struct {

    int num_elem = 100;
    Elem** head;

} HashTable;

HashTable*  HT_construct     ();
     Elem*  Elem_construct   ();
      void  HT_destruct      (HashTable* ht);
      int*  power_mod256     (int a, int x);
unsigned int  hash_f         (const char* key);
      void  add_elem         (Elem* where, const char* key, value_t data);
      void  add_to_hash      (HashTable* ht, const char* key, value_t data);
     Elem*  find_by_key      (Elem* head, const char* key_to_find);
     Elem*  find_in_hash     (HashTable* ht, const char* key_to_find);
       int  delete_from_hash (HashTable* ht, const char* key);

int main() {

    HashTable* ht = HT_construct();
    char* word;

    FILE* input;
    FILE* output;
    input  = fopen("input.txt", "rt");
    output = fopen("output.txt", "wt");

    while (!feof(input)) {

        word = read_word(input);

        printf("here\n");

        add_elem(ht -> head[hash_f(word) % 100], word, 10);

    }

    Elem* search_elem = find_in_hash(ht, "hero");

    printf("%d", search_elem -> value);


    fclose(input);
    fclose(output);

    HT_destruct(ht);

    return 0;

}

Elem* Elem_construct() {

    Elem* new_elem = (Elem*) calloc(1, sizeof(Elem));

    new_elem->next  = NULL;
    new_elem->value = 0;

    return new_elem;

}

HashTable* HT_construct() {

    HashTable* ht = (HashTable*) calloc (1, sizeof(HashTable));

    for (int i = 0; i < ht->num_elem; i++) {

        ht->head[i] = NULL;

    }

    return ht;

}

void HT_destruct (HashTable* ht) {


    for (int i = 0; i < ht->num_elem; i++) {

        ht->head[i] = NULL;

    }

    ht->num_elem = 0;

    free(ht);

}

// IN:   a pointer to an element of a list, key and data value
// DOES: creates a new element.
//       If received pointer is NULL adds it in place of it.
//       If it exists, creates an element and copies all the data, changes pointers
// OUT:  nothing

void add_elem(Elem* where, const char* key, value_t data) {

    Elem* temp;

    if (where != NULL) {

        Elem* new_elem = Elem_construct();

        temp = where -> next;

           where -> next = new_elem;
        new_elem -> next = temp;

        strcpy(new_elem -> key_value, key);
        new_elem -> value = data;

    }
    else {

        where = Elem_construct();

        strcpy(where -> key_value, key);
        where -> value = data;

    }
}

// IN:   a pointer to a first element of a list, key
// DOES: goes through the list and finds an element
// OUT:  a pointer to the found element, NULL if nothing found

Elem* find_by_key(Elem* head, const char* key_to_find) {

    Elem* current = head;

    while (current) {

        if (strcmp(key_to_find, current->key_value) == 0) {

            return current;

        }
        else {

            current = current->next;

        }

    }

    return NULL;

}

// IN:   a pointer to a hash table, key and some data
// DOES: calculates a hash function for this key, adds a new element to a hash table
// OUT:  nothing

void add_to_hash(HashTable* ht, const char* key, value_t data) {

    assert(ht);

    int i = hash_f(key) % ht->num_elem;

    add_elem(ht->head[i], key, data);

}

// IN:   a pointer to a hash table, key
// DOES: calculates a hash function for this key, calls a search by key in the needed list
// OUT:  a pointer to the found element, NULL if nothing found

Elem* find_in_hash(HashTable* ht, const char* key_to_find) {

    int hf = hash_f(key_to_find) % ht->num_elem;

    return find_by_key(ht->head[hf], key_to_find);

}

//
//
//

int delete_from_hash(HashTable* ht, const char* key) {

    printf("%s : Not implimented", __func__);
    return 0;

}

// Polynomial hash function

unsigned int hash_f(const char* key) {

    int  sum = 0;
    int  len = strlen(key);
    int* pow = power_mod256(42, len);
    int  key_num[len + 1];

    for (unsigned int i = 0; i <= len; i++) {

        key_num[i] = key[i];

    }

    for (unsigned int i = 0; i <= len; i++) {

        sum = sum + key_num[i] * pow[i];

    }

    free(pow);

    return sum;

}

//  IN:   two numbers - a (base), x (exponent)
//  DOES: allocates a block of memory for an array. Fills it with remainders in division powers by 256
//  OUT:  a pointer to an array

int* power_mod256(int a, int x) {

    int* pow = (int*) calloc(20, sizeof(int));
    int len = 10;

    pow[0] = 1;

    if (x > len) {

        len = x + 1;
        pow = (int*) realloc(pow, len * sizeof(int));

    }

    for (int i = 1; i <= x; i++) {

        pow[i] = pow[i-1] * a;

    }

    for (int i = 0; i <= x; i++) {

        pow[i] = pow[i] % 256;

    }

    return pow;
}
