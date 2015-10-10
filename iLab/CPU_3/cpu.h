typedef int elem_t;
const int STK_SZ = 10;

typedef struct {

    int counter;
    elem_t data[STK_SZ];

} Stack_t;

typedef struct {

    int ax;
    int* code;
    Stack_t* stack_cpu;

} CPU_t;

void Stack_construct (Stack_t* st);
void Stack_destruct  (Stack_t* st);
 int Stack_ok        (const Stack_t* st);
void Stack_dump      (const Stack_t* st);
 int Stack_push      (Stack_t* st, elem_t num);
 int Stack_pop       (Stack_t* st);
void CPU_construct   (CPU_t* cpu);
void CPU_destruct    (CPU_t* cpu);
 int CPU_ok          (const CPU_t* cpu);
 int CPU_add         (CPU_t* cpu);
 int CPU_mul         (CPU_t* cpu);
 int CPU_sub         (CPU_t* cpu);
 int CPU_div         (CPU_t* cpu);
void CPU_mov_ax      (CPU_t* cpu, int num);
void CPU_dump        (CPU_t* cpu);