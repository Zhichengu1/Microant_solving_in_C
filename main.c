#include <stdlib.h>
#include <stdio.h>
#include "stack.h"

int main()
{
    int size = 0;
    printf("Enter the size for your stack: ");
    scanf("%d", &size);
    stack* curr = create_stack(size);
    
    push(1, 2);
    push(2, 3);
    push(3, 2);
    printf("the stack is full or not: %d\n", is_StackFull());
    printf("the stack is empty or not: %d\n", is_StackEmpty());
    for(int i = 0; i < size; i++)
    {
            printf("the value: [%d,%d]\n", curr[i].x, curr[i].y);
    }
    stack* d = pop();
    for(int i = 0; i < size; i++)
    {
            printf("the value: [%d,%d]\n", curr[i].x, curr[i].y);
    }
    printf("the value: [%d,%d]\n", d->x, d->y);
    
}
