//Group memebers: Jiacheng Liang ID: 115886650, Zhicheng ID: 115690503, Kevin Zheng ID: 115748800
#include <stdlib.h>
#include <stdio.h>
#include "stack.h"
#include <stdlib.h>
#include <string.h>
#include "action.h"

//define each actions
typedef enum {
    MARK_,
    MOVE_F_,
    MOVE_B_,
    MOVE_L_,
    MOVE_R_,
    CWL_,
    CWR_,
    CWF_,
    CWB_,
    PUSH_,
    POP_,
    PEEK_,
    CLEAR_,
    BJPI_,
    CJPI_,
    BACKTRACK_,
    RP_,
    markStartingPoint_,
    check_surroundings_,
} ActionType;

//execute actions from the intelligence file
void executeAction(ActionType type) {
    switch (type) {
        case markStartingPoint_:
            printf("Mark starting position\n");
            break;
        case MARK_:
            printf("Action: MARK\n");
            break;
        case MOVE_F_:
            printf("Action: MOVE_F\n");
            break;
        case MOVE_B_:
            printf("Action: MOVE_B\n");
            break;
        case MOVE_L_:
            printf("Action: MOVE_L\n");
            break;
        case MOVE_R_:
            printf("Action: MOVE_R\n");
            break;
        case CWL_:
            printf("Action: CWL\n");
            break;
        case CWR_:
            printf("Action: CWR\n");
            break;
        case CWF_:
            printf("Action: CWF\n");
            break;
        case CWB_:
            printf("Action: CWB\n");
            break;
        case PUSH_:
            printf("Action: PUSH\n");
            break;
        case POP_:
            printf("Action: POP\n");
            break;
        case PEEK_:
            printf("Action: PEEK\n");
            break;
        case CLEAR_:
            printf("Action: CLEAR\n");
            break;
        case BJPI_:
            printf("Action: BJPI\n");
            break;
        case CJPI_:
            printf("Action: CJPI\n");
            break;
        case BACKTRACK_:
            printf("Action: BACKTRACK\n");
            break;
        case RP_:
            printf("Action: RP\n");
            break;
        case check_surroundings_:
            printf("Action: check surroundings\n");
            break;
        default:
            printf("Unknown action type\n");
            break;
    }
}

//Perform actions from the file.
void performActionsFromFile() {
    FILE *file = fopen("intelligence.txt", "r");
    if (file == NULL) {
        printf("Error: Unable to open intelligence file.\n");
        return;
    }
    char line[256];
    while (fgets(line, sizeof(line), file) != NULL) {
        // Remove trailing newline character
        line[strcspn(line, "\n")] = '\0';
        
        ActionType type;
        if (strcmp(line, "MARK") == 0)
            type = MARK_;
        else if (strcmp(line, "MOVE_F") == 0)
            type = MOVE_F_;
        else if (strcmp(line, "MOVE_B") == 0)
            type = MOVE_B_;
        else if (strcmp(line, "MOVE_L") == 0)
            type = MOVE_L_;
        else if (strcmp(line, "MOVE_R") == 0)
            type = MOVE_R_;
        else if (strcmp(line, "CWL") == 0)
            type = CWL_;
        else if (strcmp(line, "CWR") == 0)
            type = CWR_;
        else if (strcmp(line, "CWF") == 0)
            type = CWF_;
        else if (strcmp(line, "CWB") == 0)
            type = CWB_;
        else if (strcmp(line, "PUSH") == 0)
            type = PUSH_;
        else if (strcmp(line, "POP") == 0)
            type = POP_;
        else if (strcmp(line, "PEEK") == 0)
            type = PEEK_;
        else if (strcmp(line, "CLEAR") == 0)
            type = CLEAR_;
        else if (strcmp(line, "BJPI") == 0)
            type = BJPI_;
        else if (strcmp(line, "CJPI") == 0)
            type = CJPI_;
        else if (strcmp(line, "BACKTRACK") == 0)
            type = BACKTRACK_;
        else if (strcmp(line, "RP") == 0)
            type = RP_;
        else if (strcmp(line, "markStartingPoint") == 0)
            type = markStartingPoint_;
        else if (strcmp(line, "checkSurrounding") == 0)
            type = check_surroundings_;
        executeAction(type);
    }
    fclose(file);
}


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

//Printing the maze
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
                printf("E");// print 'E' for exit
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
    if(maze[x+1][y] != 8)
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
    stack* previous = NULL;
    printf("coordinate: [%d,%d]\n", x, y);
    printf("Performing actions from the intelligence file:\n");
    performActionsFromFile();
    while(is_exit(maze, x, y, rows, cols) != 0)
    {
        //know the next direction
        direction = check_surroundings(maze,x,y);
        switch(direction)
        {
            case 'v': 
            previous = BACKTRACK();
            printf("\n[%d,%d]\n", previous -> x, previous -> y);
            if (previous == NULL) {
            printf("Error: Stack is empty, cannot backtrack.\n");
            break;
            }
            x = previous -> x;
            y = previous -> y;
            break;

            case 'b': 
            move_F(&x);
            MARK(maze,x,y);
            printf("\n[%d,%d]\n", x, y);
            direction = check_surroundings(maze,x,y);
            if(direction == 'b')
            {
                if(x < rows && y> cols )
                {
                CJPI(maze, &x, &y, rows, cols, check_surroundings(maze,x,y));
                direction = check_surroundings(maze,x,y);
                if(direction == 'b')
                {
                    BJPI(maze, &x, &y, rows, cols, direction);
                    direction = check_surroundings(maze,x,y);
                }
                }
            }
            break;
            
            case 'f':
            move_B(&x);
            MARK(maze,x,y);
            direction = check_surroundings(maze,x,y);
            if(direction == 'f')
            {
                if(x < rows && y> cols )
                {
                CJPI(maze, &x, &y, rows, cols, check_surroundings(maze,x,y));
                direction = check_surroundings(maze,x,y);
                if(direction == 'f')
                {
                    BJPI(maze, &x, &y, rows, cols, direction);
                    direction = check_surroundings(maze,x,y);
                }
                }
            }
            break;

            case 'r': 
            move_R(&y);
            MARK(maze,x,y);
            direction = check_surroundings(maze,x,y);
            if(direction == 'r')
            {
                if(x < rows && y> cols )
                {
                CJPI(maze, &x, &y, rows, cols, check_surroundings(maze,x,y));
                direction = check_surroundings(maze,x,y);
                if(direction == 'r')
                {
                    BJPI(maze, &x, &y, rows, cols, direction);
                    direction = check_surroundings(maze,x,y);
                }
                }
            }
            break;
            
            case 'l':
            move_L(&y);
            MARK(maze,x,y);
            direction = check_surroundings(maze,x,y);
            if(direction == 'l')
            {
                if(x < rows && y> cols )
                {
                CJPI(maze, &x, &y, rows, cols, check_surroundings(maze,x,y));
                direction = check_surroundings(maze,x,y);
                if(direction == 'l')
                {
                    BJPI(maze, &x, &y, rows, cols, direction);
                    direction = check_surroundings(maze,x,y);
                }
                }
            }
            break;
        }  
    }

    printf("\ncoordinate: [%d,%d]\n", x, y);

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            printf(" %d ", maze[i][j]);
        }
        printf("\n");
  }

  for(int i = 0; i < position -> max; i++)
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