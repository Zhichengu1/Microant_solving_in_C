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