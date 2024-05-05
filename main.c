#include <stdlib.h>
#include <stdio.h>
#include "stack.h"
#include <stdlib.h>
#include <string.h>
#include "action.h"


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
            } 
            else {
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
            } 
            else if(maze[i][j] == 2){
                printf("x"); // Print '*' for walls
            }
            else if(maze[i][j] == 8)
            {
                printf("E");
            }
            else {
                printf(" "); // Print ' ' for empty spaces
            }
        }
        printf("\n");
    }
}

//first entry
void markStartingPoint(int **maze, int rows, int cols) 
{
    // Find the first empty space in the first line and mark it as the starting point
    for (int i = 0; i < cols; i++) {
        if (maze[0][i] == 0) {
        // Mark as starting point
            MARK(maze, 0, i);
        }
    }
}
//check the surrouding
char check_surroundings(int** maze, int x, int y)
{
    if(CWL(maze, x, y) == 1)
    {
        return 'l';
    }
    else if (CWB(maze, x, y) == 1)
    {
        return 'b';
    }
    else if(CWF(maze, x,y) == 1)
    {
        return 'f';
    }
    else if (CWR(maze,x,y) == 1)
    {
        return 'r';
    }
    else
    {
        return 'v';
    }
}

//exit
int is_exit(int **maze, int x, int y, int max_rows, int max_cols)
{
    int result = 0;
    for(int i = 0; i < max_cols; i++)
    {
            if(maze[max_rows-1][i] == 0)
            {
                maze[max_rows-1][i] = 8;
            }
    }
    if(maze[x][y] != 8)
    {
        result = 1;
    } 
    return result;
}

int main() {
    int **maze;
    int rows, cols, x, y;
    char filename[100]; // Maximum filename length

    printf("Enter the name of the maze file: ");
    fgets(filename, sizeof(filename), stdin);
    filename[strcspn(filename, "\n")] = '\0'; // Remove newline character if present

    // // Copy maze from file
    copyMazeFromFile(&maze, &rows, &cols, filename);
    stack* position = create_stack(100, rows, cols);

    //init position
    markStartingPoint(maze, rows, cols);
    x = position[0].x;
    y = position[0].y;
    char direction;
    stack* current = NULL;
    printf("coordinate: [%d,%d]\n", x, y);
    while(is_exit(maze, x, y, rows, cols))
    {
        //know the next direction
        direction = check_surroundings(maze,x,y);
        printf("\n%c\n", direction);
        switch(direction)
        {
            case 'v': 
            current = BACKTRACK(&x, &y);
            break;
            case 'b': 
            move_F(&x);
            MARK(maze,x,y);
            direction = check_surroundings(maze,x,y);
            if(direction != 'v')
            {
                CJPI(maze, &x, &y, rows, cols, check_surroundings(maze,x,y));
                direction = check_surroundings(maze,x,y);
                printf("\n%c\n", check_surroundings(maze,x,y));
                if(direction != 'v')
                {
                    BJPI(maze, &x, &y, rows, cols, direction);
                    direction = check_surroundings(maze,x,y);
                }
            }
            break;
            case 'f':
            move_B(&x);
            if(check_surroundings(maze,x,y) != 'v')
            {
                CJPI(maze, &x, &y, rows, cols, check_surroundings(maze,x,y));
                printf("\n%c\n", check_surroundings(maze,x,y));
                printf("\n%d %d\n", x, y);

                if(check_surroundings(maze,x,y) != 'v')
                {
                    printf("\n%d %d\n", x, y);
                    BJPI(maze, &x, &y, rows, cols, check_surroundings(maze,x,y));
                    printf("\n%c\n", check_surroundings(maze,x,y));
                    printf("\n%d %d\n", x, y);
                }
            }
            break;
            case 'r': 
            move_R(&y);
            if(check_surroundings(maze,x,y) != 'v')
            {
                CJPI(maze, &x, &y, rows, cols, check_surroundings(maze,x,y));
                printf("\n%c\n", check_surroundings(maze,x,y));
                printf("\n%d %d\n", x, y);

                if(check_surroundings(maze,x,y) != 'v')
                {
                    printf("\n%d %d\n", x, y);
                    BJPI(maze, &x, &y, rows, cols, check_surroundings(maze,x,y));
                    printf("\n%c\n", check_surroundings(maze,x,y));
                    printf("\n%d %d\n", x, y);
                }
            }
            break;
            case 'l':
            move_L(&y);
            if(check_surroundings(maze,x,y) != 'v')
            {
                CJPI(maze, &x, &y, rows, cols, check_surroundings(maze,x,y));
                printf("\n%c\n", check_surroundings(maze,x,y));
                printf("\n%d %d\n", x, y);

                if(check_surroundings(maze,x,y) != 'v')
                {
                    printf("\n%d %d\n", x, y);
                    BJPI(maze, &x, &y, rows, cols, check_surroundings(maze,x,y));
                    printf("\n%c\n", check_surroundings(maze,x,y));
                    printf("\n%d %d\n", x, y);
                }
            }
            break;
        }   
        break;     
    }

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            printf(" %d ", maze[i][j]);
        }
        printf("\n");
  }
  for(int i = 0; i < 10; i++)
  {
    printf("\ncoordinate: [%d,%d]\n", position[i].x, position[i].y);
  }
   
    printf("\n\n this %c \n\n", maze[0][4]);
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


