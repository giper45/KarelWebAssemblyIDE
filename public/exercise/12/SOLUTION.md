# Exercise 12: Zig-Zag Fill - Solution

## Overview
This exercise demonstrates advanced nested loop patterns and direction control by implementing a zig-zag filling algorithm. Karel fills a 5x5 area with beepers, moving in alternating directions for each row.



## Step-by-step Explanation

1. **Goal**: Fill a 5x5 grid with beepers, moving in a zig-zag pattern (one row to the right, the next to the left, and so on).

2. **Helper function**: `karel_turn_right()` makes Karel turn right by calling the `karel_turn_left()` function three times.

3. **Variables**:
   - `no_moves` and `no_rows` are both set to 5, for a 5x5 grid.
   - `beepersPlaced` keeps track of how many beepers have been placed.

4. **Main row loop**: An outer `for` loop iterates through all the rows (`i` from 0 to 4).
   - At the start of each row, Karel places a beeper at the current position.
   - An inner loop moves Karel across the row, placing a beeper in each cell (for a total of 5 beepers per row).

5. **Changing direction**:
   - At the end of each row (except the last), Karel must move up one position and change direction:
     - If facing east, turn left, move up, turn left again (now facing west).
     - If facing west, turn right, move up, turn right again (now facing east).

6. **End**:
   - After completing the last row, Karel stops and prints a completion message.

---

## Complete Solution
```c
void karel_turn_right()
{
    for (int i = 0; i < 3; i++)
        karel_turn_left();
    
}


void studentCode()
{
    static bool exerciseComplete = false;
    static int currentRow = 1;
    static int currentCol = 1;
    static int beepersPlaced = 0;
    const int no_moves = 5;
    const int no_rows = 5;

    if (!exerciseComplete)
    {
        for (int i = 0; i < no_rows; i++)
        {
            // Place beeper at start of each row
            karel_put_beeper();
            beepersPlaced++;
            printf("Row %d: Placed beeper #%d at (%d,%d)\n", i + 1, beepersPlaced, karel_get_x(), karel_get_y());
            
            // Move across the row placing beepers
            for (int j = 0; j < no_moves - 1; j++) // no_moves - 1 perché il primo beeper è già piazzato
            {
                karel_move();
                karel_put_beeper();
                beepersPlaced++;
                printf("Row %d: Placed beeper #%d at (%d,%d)\n", i + 1, beepersPlaced, karel_get_x(), karel_get_y());
            }
            
            // IMPORTANTE: Solo se NON siamo all'ultima riga, muoviti verso l'alto
            if (i < no_rows - 1) 
            {
                if (facing_east())
                {
                    karel_turn_left();   // Gira a nord
                    karel_move();        // Muovi verso l'alto
                    karel_turn_left();   // Gira a ovest per la prossima riga
                }
                else if (facing_west())
                {
                    karel_turn_right();  // Gira a nord  
                    karel_move();        // Muovi verso l'alto
                    karel_turn_right();  // Gira a est per la prossima riga
                }
                printf("Moving to row %d, now facing %s\n", i + 2, facing_east() ? "East" : "West");
            }
            else 
            {
                // Ultima riga completata - non muoverti verso l'alto
                printf("Final row completed! Staying at position (%d,%d)\n", karel_get_x(), karel_get_y());
            }
        }
        
        printf("Zig-zag fill complete! %d beepers placed in %dx%d area.\n", beepersPlaced, no_moves, no_rows);
        printf("Final position: (%d,%d) facing %s\n", karel_get_x(), karel_get_y(), DIRECTION_NAMES[karel_get_direction()]);
        exerciseComplete = true;
    }
}
```