#include "stack.h"
#include <stdlib.h>
#include <stdio.h>
#include "action.h"

stack* curr;
int maxk = 0;
int max_row = 0;
int max_cols = 0;

stack* create_stack(int size, int max_r, int max_c)
{
    if(size > 0)
    {
        curr = (stack*) malloc(sizeof(stack) * size);
        curr->front = 0;
        curr->rear = 0;
        max_row = max_r;
        maxk = size;
        max_cols = max_c;
        curr-> max = 0;
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
        curr-> max++;
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
        curr -> max--;
        // If the element is popped, change it to zero
        curr[curr->rear].x = 0;
        curr[curr->rear].y = 0;
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
    return curr->rear == maxk ? 1 : 0; 
}

//mark -
void MARK(int** Maze, int x, int y) 
{
    if (Maze[x][y] == 0)
    {
        push(x,y);
        Maze[x][y] = 2;
    }
    else if(Maze[x][y] == 2)
    {
        return;
    }
    else if(Maze[x][y] == 8)
    {
        push(x,y);
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

//you check one direction until it reaches the wall
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
            while(!(is_StackFull()) && *x > 0 && maze[*x-1][*y] != 1 && maze[*x-1][*y] != 2)
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

//CJPI move only one position at a time if it is the same direction
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

//backtrack: pop and then peek
stack* BACKTRACK()
{
    if(is_StackEmpty())
    {
        printf("The stack is empty");
        return NULL;
    }
    
    // Pop an element from the stack
    stack* d = pop();
    // Return the top element of the stack
    stack* c = peek();
    return c;
}

//repeat function
void repeat_function(int n, void (*f)())
{
    for(int i = 0; i < n; i++)
    {
        f();
    }
}