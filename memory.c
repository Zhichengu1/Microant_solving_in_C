#include <stdlib.h>
#include <stab.h>
#include "stack.h"

//init pointer for stack memory
stack* curr;
int max;

//given size
stack* create_stack(int size)
{
    if(size > 0)
    {
        curr = (stack*) malloc(sizeof(curr) * size);
        curr->front = 0;
        curr->rear = 0;
        max = size;
    }
    else
    {
        curr = NULL;
        printf("The stack memory is empty");
    }
    return curr;
}

//stack follow the logic FILO
int is_StackFull()
{
    return curr->rear == max ? 1 : 0; 
}
//
int is_StackEmpty()
{
    return curr -> rear == curr -> front ? 1 : 0;
}

void push(int x , int y)
{
    if(!is_StackFull())
    {
        curr[curr->rear].x = x;
        curr[curr->rear].y = y;
        curr->rear++;
    }
    else
    {
        printf("the stack is currently empty");
    }
}
int pop()
{
    if(!is_StackEmpty())
    {
        
    }

}
int peek()
{

}
void clear();
