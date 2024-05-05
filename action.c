#include "stack.h"
#include <stdlib.h>
#include <stab.h>


/*


MARK – the ant marks its current position using a chemical called pheromone.
2. MOVE_F – moves the VA from the current position one position forward. If Michael
locates at coordinates (x, y), it will move to (x + 1, y).
3. MOVE_B – moves the virtual ant from the current position one position backward. If
Michael locates at coordinates (x, y), it will move to (x - 1, y).
4. MOVE_L – moves the virtual ant from the current position one position left. If Michael
locates at coordinates (x, y), it will move to (x, y - 1).
5. MOVE_R – moves the virtual ant from the current position one position right. If Michael
locates at coordinates (x, y), it will move to (x, y + 1).
6. CWL – Michael checks if the next locations to the left (until meeting a wall) are pheromone
free. If the locations are free then Michael feels an itch. Otherwise, if no location is free
(e.g., because there is a pheromone mark or a wall on the left of Michael), then Michael
does not feel the itch.
7. CWR – Michael checks if the next locations to the right (until meeting a wall) are
pheromone free. If the locations are free then Michael feels another kind of itch.


*/

//stack follow the logic FILO

//mark -> kevin

/*
void MARK(int** Maze[][], int x, int y);
{
    if (MAZE[x][y] == 'x' || MAZE[X]{Y} == '*')
    {
        printf("Value cannot be printed here");
    }
    else
    {
        MAZE[x][y] = 'x'
    }
}
*/


// move F, B, L, R


//CWL


/*
Michael checks if the next locations to the left (until meeting a wall) are pheromone
free. If the locations are free then Michael feels an itch. Otherwise, if no location is free
(e.g., because there is a pheromone mark or a wall on the left of Michael), then Michael
does not feel the itch
*/



/*

BJPI (Bold jump for itching) – jump x position along the direction for which Michael felt
an itch (left, right, forward, backward). For example, after performing CWR, Michael felt
an itch because the direction to the right of the current position was free. Then it decided
to act using BJPI, meaning that it jumped x positions to the right, as the itching was felt
after Michael checked the locations to the right of its current position. The number of
positions over which it jumped is found by after using the corresponding CWL, CWR, CWF,
CWB action. For example, if the next 4 locations to the left of the current position are
free, then x is 4 after executing CWL. If x is zero after executing action CWL, but the ant
still executes action BJPI, then Michael stays in its current position. Every BJPI stops the
corresponding itching of the ant, e.g., the itching type that triggered the jump.

*/



