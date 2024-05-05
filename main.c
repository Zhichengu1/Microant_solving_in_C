#include <stdlib.h>
#include <stdio.h>
#include "stack.h"
#include <stdlib.h>
#include <string.h>

void copyMazeFromFile(int ***maze, int *rows, int *cols, char *filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error: Unable to open file.\n");
        return;
    }
    // Initialize rows and cols to 0
    *rows = 0;
    *cols = 0;
    
    // Count the number of rows and the maximum number of columns
    char line[256];
    while (fgets(line, sizeof(line), file) != NULL) {
        (*rows)++;
        int current_cols = strlen(line) - 1; // Exclude the newline character
        if (current_cols > *cols) {
            *cols = current_cols;
        }
    }


    // Reset file pointer to the beginning
    fseek(file, 0, SEEK_SET);

    // Allocate memory for the maze
    *maze = (int **)malloc(*rows * sizeof(int *));
    for (int i = 0; i < *rows; i++) {
        (*maze)[i] = (int *)malloc(*cols * sizeof(int));
    }


    // Read the maze contents into the array
    for (int i = 0; i < *rows; i++) {
        fgets(line, sizeof(line), file);
        for (int j = 0; j < *cols; j++) {
            if (line[j] == '*') {
                (*maze)[i][j] = 1; // '*' represents a wall
            } else {
                (*maze)[i][j] = 0; // Other characters represent empty spaces
            }
        }
    }

    fclose(file);
}


void printMaze(int **maze, int rows, int cols) {
    printf("Maze:\n");
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (maze[i][j] == 1) {
                printf("*"); // Print '*' for walls
            } else {
                printf(" "); // Print ' ' for empty spaces
            }
        }
        printf("\n");
    }
}


int main() {
    int **maze;
    int rows, cols;
    char filename[100]; // Maximum filename length


    printf("Enter the name of the maze file: ");
    fgets(filename, sizeof(filename), stdin);
    filename[strcspn(filename, "\n")] = '\0'; // Remove newline character if present


    // // Copy maze from file
    copyMazeFromFile(&maze, &rows, &cols, filename);


    // // Print the maze
    printf("Rows: %d, Columns: %d\n", rows, cols);
    printMaze(maze, rows, cols);


    //Free allocated memory
    for (int i = 0; i < rows; i++) {
    free(maze[i]);
    }
    free(maze);

    return 0;
}


/*
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
    stack* first = peek();
    printf("the value: [%d,%d]\n", first->x, first->y);
    */