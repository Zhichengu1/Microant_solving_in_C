(Virtual Ant): ECE Course Project
  [the best exit method alternative](https://algo.monster/liteproblems/1926)

- action.c file: "Contains all the actions that an ant can take."
- action.h file: "methods initialization".
- intelligence.txt file: "a generic maze exit file".
- main.c file: "main program"
- memory.c file: "keep track of the steps that the ant take."

The ant has its own memory in the form of a stack with a maximum size of MAX_SIZE. It has operators (functions) like pop, push, peek, clear, empty, and full. 
Each stack element can store the current physical position of the ant inside the maze, described as the pair (x, y). The positions are indicated by two integer numbers, x and y, but the accurate position is not displayed to the ant. Therefore, the ant does not know the map coordinates of the place it must navigate, its current position coordinates, or any of its previous positions’ coordinates. The implementation will be in the C programming language.


To avoid linker issue compile the following commands:

gcc main.c action.c -o main

./main

