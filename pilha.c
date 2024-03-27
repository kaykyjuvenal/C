#include <stdio.h>
#include <stdlib.h>
//PILHA FIRST IN LAST OUT primeira que entra sai primeiro
#define STACKSIZE 100
struct stack{
    int top;
    int items[STACKSIZE];
};
int empty_stack(struct stack *ps){
    if(ps->top == -1)
        return 1;
    else
        return 0;
}
void push_stack(struct stack *ps, int x){
    if(ps->top == STACKSIZE-1){
        printf("Stack is full\n");
        exit(1);
    } else{
        ps->items[++ps->top] = x;
    }
}
int pop_stack(struct stack *ps){
    if(empty_stack(ps)){
        printf("%s","Stack is empty\n");
        exit(1);
    } 
    return (ps->items[ps->top--]);
}
int main(){

    struct stack s;
    s.top = -1;
    if (empty_stack(&s))
    {
        printf("%s","Stack is empty\n");
    }
    push_stack(&s,1);
    push_stack(&s,2);
    push_stack(&s,3);
    push_stack(&s,4);
    push_stack(&s,5);
    printf("%d\n", pop_stack(&s));
    printf("%d\n", pop_stack(&s));
    printf("%d\n", pop_stack(&s));
    printf("%d\n", pop_stack(&s));
    printf("%d\n", pop_stack(&s));
    printf("%d", pop_stack(&s));
    return 0;
}