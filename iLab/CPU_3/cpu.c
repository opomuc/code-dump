void CPU_construct(CPU_t* cpu) {

    assert(cpu);

    cpu->ax = 0;
    cpu->code = (int*) calloc(10, sizeof(int));
    cpu->stack_cpu = (Stack_t*) malloc(sizeof(Stack_t));

    Stack_construct(cpu->stack_cpu);

}

void CPU_destruct(CPU_t* cpu) {

    assert(cpu);

    Stack_destruct(cpu->stack_cpu);
    free(cpu->stack_cpu);
    free(cpu->code);
    cpu = NULL;

}

int CPU_ok(const CPU_t* cpu) {

    assert(cpu);

    return Stack_ok(cpu->stack_cpu);

}

int CPU_add(CPU_t* cpu) {

    if ((cpu->stack_cpu->counter) >= 2) {

        int a = Stack_pop(cpu->stack_cpu);
        int b = Stack_pop(cpu->stack_cpu);
        Stack_push(cpu->stack_cpu, a+b);
        return 1;

    }
    else return 0;
}

int CPU_mul(CPU_t* cpu) {

    if ((cpu->stack_cpu->counter) >= 2) {

        int a = Stack_pop(cpu->stack_cpu);
        int b = Stack_pop(cpu->stack_cpu);
        Stack_push(cpu->stack_cpu, a*b);
        return 1;

    }
    else return 0;
}

int CPU_sub(CPU_t* cpu) {

    if ((cpu->stack_cpu->counter) >= 2) {

        int a = Stack_pop(cpu->stack_cpu);
        int b = Stack_pop(cpu->stack_cpu);
        Stack_push(cpu->stack_cpu, b-a);
        return 1;

    }
    else return 0;
}

int CPU_div(CPU_t* cpu) {

    if ((cpu->stack_cpu->counter) >= 2) {

        int a = Stack_pop(cpu->stack_cpu);
        int b = Stack_pop(cpu->stack_cpu);
        Stack_push(cpu->stack_cpu, b/a);
        return 1;

    }
    else return 0;
}

void Stack_construct (Stack_t* st) {

    st->counter = 0;

    for (int i = 0; i < STK_SZ; i++) {st->data[i] = 0;}

    assert(st);

}

void Stack_destruct(Stack_t* st) {

    assert(st);

    st->counter = 0xBAD;
    for (int i = 0; i <= STK_SZ; i++) {st->data[i] = 0xBAD;}
    st = NULL;

}

int Stack_ok(const Stack_t* st) {

    return (st && (0 <= st->counter) && (st->counter < STK_SZ));

}

void Stack_dump(const Stack_t* st) {

    printf("\n  Stack // adress: %p\n", st);
    putchar('\n');
    printf("    # counter = %d\n", st->counter);
    printf("    # stack size = %d\n", STK_SZ);

    for (int i = 0; i <= STK_SZ - 1; i++) {

        if (i < st->counter) {

            printf("    # data[%d] = %d*\n", i, st->data[i]);

        }
        else {

            printf("    # data[%d] = %d\n", i, st->data[i]);

        }
    }

    putchar('\n');

}

int Stack_push(Stack_t* st, elem_t num) {

    if (!Stack_ok(st)) {

        Stack_dump(st);
        assert(!"   # Stack overflow #  ");

    }

    st->data[st->counter++] = num;


    if (!Stack_ok(st)) {return 0;}
    else {

        return 1;

    }

}

int Stack_pop(Stack_t* st) {

    if (--st->counter >= 0) return st->data[st->counter];

    else if (!Stack_ok(st)) {

        Stack_dump(st);
        assert(!"   # Stack is empty #  ");

    }
    else return 0xBAD;

}

void CPU_dump(CPU_t* cpu) {

    assert(cpu);
    printf("\n  CPU //\n\n");
    printf("    # register ax = %d\n", cpu->ax);
    Stack_dump(cpu->stack_cpu);

}

void CPU_mov_ax(CPU_t* cpu, int num) {

    assert(cpu);

    cpu->ax = num;

}
