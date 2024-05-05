#include <stdlib.h>
#include <stdio.h>
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

//actions
int is_StackFull()
{
    return curr->rear == max ? 1 : 0; 
}
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
stack* pop()
{
    stack* d = NULL;
    if(!is_StackEmpty())
    {
        curr->rear--; // decrease the rear pointer first
        d = &curr[curr->rear]; // get the top element
        free(&curr[curr->rear]);
    }
    else
    {
        printf("the stack is currently empty. ");
    }
    return d;
}

stack* peek()
{
    return &curr[curr->rear-1];
}

void clear()
{
    free(curr);
}

