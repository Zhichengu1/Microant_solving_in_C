#include "stack.h"
#include <stdlib.h>
#include <stdio.h>
#include "action.h"
int max = 0;
stack* curr;
int max_row = 0;
int max_cols = 0;
stack* create_stack(int size, int max_r, int max_c)
{
    if(size > 0)
    {
        curr = (stack*) malloc(sizeof(stack) * size);
        curr->front = 0;
        curr->rear = 0;
        max = size;
        max_row = max_r;
        max_cols = max_c;
    }
    else
    {
        curr = NULL;
        printf("The stack memory is empty");
    }
    return curr;
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

//memory
int is_StackFull()
{
    return curr->rear == max ? 1 : 0; 
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
    if(*x+1 < max_row)
    {
        (*x)++;
    }
}
void move_B(int *x) {
    if(*x-1 > 0) 
    {
        (*x)--;
    }
}
void move_L(int *y) {
    if(*y-1 != 0)
    {
        (*y)--;
    }
}
void move_R(int *y) {
    if(*y+1 < max_cols)
    {
        (*y)++;
    }
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
int CWR(int** maze, int x, int y)
{
    return y < max_cols && maze[x][y+1] != 1 && maze[x][y+1] != 2 ? 1 : 0;  
}

//CWF check front
int CWF(int** maze, int x, int y)
{
    return x > 0 && maze[x-1][y] != 1 && maze[x-1][y] != 2 ? 1 : 0;
}

//CWB check back
int CWB(int** maze, int x, int y)
{
    return x < max_row && maze[x+1][y] != 1 && maze[x+1][y] != 2 ? 1 : 0;
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
                MARK(maze,(*x),(*y));
            }
        }
        break;

        case 'l':
        {
            while (!(is_StackFull()) && *x > 0 && maze[*x][*y-1] != 1 && maze[*x][*y-1] != 2)
            {
                (*y)--;
                MARK(maze,(*x),(*y));
            }
        }
        break;
        case 'f': 
        {
            while(!(is_StackFull()) && x > 0 && maze[*x-1][*y] != 1 && maze[*x-1][*y] != 2)
            {
                (*x)--;
                MARK(maze,(*x),(*y));
            }
        }
        case 'b':
        {
            while(!(is_StackFull()) && *x < max_row && maze[*x+1][*y] != 1 && maze[*x+1][*y] != 2)
            {
                (*x)++;
                MARK(maze,(*x),(*y));
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
    MARK(maze,(*x),(*y));
}

stack* BACKTRACK(int* x, int* y)
{
    stack* c = peek();
    while(c -> x != *x && c -> y != *y && !(is_StackEmpty()))
    {
        c = pop();
    }
    if(is_StackEmpty())
    {
        printf("The starting position is a dead end");
        return NULL;
    }
    *x = c->x;
    *y = c->y;
    return c;
}


void repeat_function(int n, void (*f)())
{
    for(int i = 0; i < n; i++)
    {
        f();
    }
}