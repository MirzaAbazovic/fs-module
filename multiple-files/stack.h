typedef struct S_stack
{
    int number;
    struct S_stack *next;
} stack;

void push(int number, stack **stack_ptr);
int pop(stack **stack_ptr);
