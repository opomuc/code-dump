#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

typedef int elem_t;

const int STK_SZ = 15;

struct Stack_t {

    const char* name;
    int counter;
    elem_t* data;

};

void Stack_construct  (Stack_t* st);
void Stack_destruct   (Stack_t* st);
 int Stack_ok         (const Stack_t* st);
void Stack_dump       (const Stack_t* st);
 int Stack_push       (Stack_t* st, elem_t num);
 int Stack_pop        (Stack_t* st);

int main() {

    int a = 0, b = 0;

    Stack_t calc = {"calc"};
    Stack_construct(&calc);



    for (int i = 0; a != '\n'; i++) {

        scanf("%d", &a);

        if (Stack_push(&calc, a));
        else {

            printf("Stop that! Push is forbidden\nYou can only pop now");
            break;

        }

    }

    Stack_dump(&calc);

    for (int i = 0; i <= STK_SZ - 1; i++) {

        b = Stack_pop(&calc);
        printf("%d ", b);

    }

    Stack_destruct(&calc);

    return 0;

}

void Stack_construct(Stack_t* st) {

    assert(&st != NULL);

    (*st).counter = 0;
    (*st).data    = (elem_t*) calloc(STK_SZ, sizeof(elem_t));

}

void Stack_destruct(Stack_t* st) {

    assert(&st != NULL);

    free ((*st).data);
    st->counter = 0xBAD;
    st->data = (elem_t*) 0xBAD;
    st = NULL;

}

int Stack_ok(const Stack_t* st) {

    return (st && (0 <= (*st).counter) && ((*st).counter < STK_SZ));

}

void Stack_dump(const Stack_t* st) {

    printf("\nStack name: %s // adress: %d\n", (*st).name, &st);
    putchar('\n');
    printf("    # counter = %d\n", (*st).counter);
    printf("    # stack size = %d\n", STK_SZ);

    for (int i = 0; i <= STK_SZ - 1; i++) {

        printf("    # data[%d] = %d\n", i, (*st).data[i]);

    }

    putchar('\n');

}

int Stack_push(Stack_t* st, elem_t num) {

    if (!Stack_ok(st)) {

        Stack_dump(st);
        assert(!"everything is bad");

    }

    (*st).data[(*st).counter++] = num;


    if (!Stack_ok(st)) {return 0;}
    else {

        return 1;

    }

}

int Stack_pop(Stack_t* st) {

    if (--(*st).counter >= 0) return (*st).data[(*st).counter];

    else if (!Stack_ok(st)) {

        Stack_dump(st);
        assert(!"everything is bad");

    }

}
