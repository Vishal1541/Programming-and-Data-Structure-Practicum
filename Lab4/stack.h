#ifndef List		/* any suggestive variable name is fine */
#define List

typedef struct l    /* Structure*/
{
    char info;
    struct list *ptr;
}list;

typedef struct s    /* Structure*/
{
    list *top;
    int size;	
}stack;

// create stack
void create(stack *s);
// push a char into stack
void push(stack *s, char x);
// pop the top of the stack
char pop(stack *s);
// return the top of stack, without popping
char peek(stack *s);
// is the stack empty?
int isEmpty(stack *s);
// return the size of the stack
int getSize(stack *s);
// return the reverse order of the stack
void revStack(stack *rs, stack *s);
// prints the elements of the stack
void printStack(stack *s);
#endif
