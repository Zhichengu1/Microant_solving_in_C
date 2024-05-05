#include "stack.h"
#include <stdlib.h>
#include <stab.h>
#include <stdio.h>
#include "action.h"

int max;
stack* curr;

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

//mark -> kevin
void MARK(int** Maze, int x, int y) 
{
    if (Maze[x][y] == 0)
    {
        push(x,y);
        Maze[x][y] = 2;
    }
    else
    {
        printf("\ncannot enter here\n");
    }
}

// move F, B, L, R
void move_F(int *x) {
    *x += 1;
}
void move_B(int *x) {
    *x -= 1;
}
void move_L(int *y) {
    *y -= 1;
}
void move_R(int *y) {
    *y += 1;
}

//CWL check left
int CWL(int **maze, int row, int col)
{
    if(col == 0)
    {
        printf("the current col is 0");
    }
    return col > 0 && maze[row][col-1] != 1 && maze[row][col-1] != 2 ? 1 : 0;
}

//CWR check right until it reaches a wall
int CWR(int** maze, int x, int y, int max_col)
{
    return y < max_col && maze[x][y+1] != 1 && maze[x][y+1] != 2 ? 1 : 0;  
}

//CWF check front
int CWF(int** maze, int x, int y)
{
    return x > 0 && maze[x-1][y] != 1 && maze[x-1][y] != 2 ? 1 : 0;
}

//CWB check back
int CWB(int** maze, int x, int y, int max_row)
{
    return x < max_row && maze[x+1][y] != 1 && maze[x+1][y] != 2 ? 1 : 0;
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
        printf("the stack is currently full");
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

//current position is free
void BJPI(int** maze, int* x, int* y, int max_row, int max_col, char direction)
{
    switch(direction)
    {
        case 'r': 
        {
            while (!(is_StackFull())&& *y < max_col && maze[*x][*y+1] != 1 && maze[*x][*y+1] != 2)
            {
                (*y)++;
                push((*x),(*y));
            }
        }
        break;

        case 'l':
        {
            while (!(is_StackFull()) && *x > 0 && maze[*x][*y-1] != 1 && maze[*x][*y-1] != 2)
            {
                (*y)--;
                push((*x),(*y));
            }
        }
        break;
        case 'f': 
        {
            while(!(is_StackFull()) && x > 0 && maze[*x-1][*y] != 1 && maze[*x-1][*y] != 2)
            {
                (*x)--;
                push((*x),(*y));
            }
        }
        case 'b':
        {
            while(!(is_StackFull()) && *x < max_row && maze[*x+1][*y] != 1 && maze[*x+1][*y] != 2)
            {
                (*x)++;
                push((*x),(*y));
            }
        }
        break;
    }
}

void CJPI(int** maze, int* x, int* y,int max_row, int max_col, char direction)
{
    switch(direction)
    {
        case 'r': 
            if (maze[*x][*y+1] != 1 && maze[*x][*y+1] != 2)
            {
                move_R(y);
            }
            break;

        case 'l':
            if (*y > 0 && maze[*x][*y-1] != 1 && maze[*x][*y-1] != 2)
            {
                move_L(y);
            }
            break;

        case 'f':
            if (*x > 0 && maze[*x-1][*y] != 1 && maze[*x-1][*y] != 2)
            {
                move_B(x);
            }
            break;

        case 'b':
            if (maze[*x+1][*y] != 1 && maze[*x+1][*y] != 2)
            {
                move_F(x);
            }
            break;
    }
      if(!is_StackFull())
      {
        push((*x),(*y));
        }
}


stack* BACKTRACK(int x, int y)
{
    stack* c = peek();
    while(c -> x != x && c -> y != y && !(is_StackEmpty()))
    {
        c = pop();
    }
    return c;
}

void repeat_function(int n, void (*f)())
{
    for(int i = 0; i < n; i++)
    {
        f();
    }
}










