# Solution: Find First Beeper and Stop
The following code provides a solution for the exercise where Karel must walk along a street and stop at the first beeper it encounters without picking it up.

```c
void studentCode() {
    static bool searchComplete = false;
    static int stepsTaken = 0;
    
    if (!searchComplete) {
        // Continue searching while no beeper present and path is clear
        while (!beepers_present() && front_is_clear()) {
            karel_move();
            stepsTaken++;
            printf("Step %d: Moved to (%d, %d) - Searching...\n", 
                   stepsTaken, karel_get_x(), karel_get_y());
        }
        
        // Search is complete - check results
        searchComplete = true;
        
        if (beepers_present()) {
            printf("SUCCESS! First beeper found at position (%d, %d) after %d steps!\n", 
                   karel_get_x(), karel_get_y(), stepsTaken);
        } else {
            printf("Search ended at wall. No beeper found after %d steps.\n", stepsTaken);
        }
        
        printf("Position: (%d, %d) | Steps taken: %d | Beeper here: %s\n", 
               karel_get_x(), karel_get_y(), stepsTaken, 
               beepers_present() ? "YES" : "NO");
    }
}
```

### Step by step explanation 
1. **Initialization**: The function starts by defining a static boolean `searchComplete` to track if the search is done, and an integer `stepsTaken` to count how many steps Karel has moved.
2. **Conditional Loop**: The main logic is inside a `while` loop that continues as long as there is no beeper present at Karel's current position and the front is clear.
3. **Movement and Logging**: Inside the loop, Karel moves forward one step at a time, increments the `stepsTaken` counter, and prints the current position and search status.
4. **Completion Check**: After the loop, it checks if a beeper was found. If so, it prints a success message with the position and steps taken. If Karel reaches a wall without finding a beeper, it prints a message indicating that no beeper was found.
5. **Final Status**: Finally, it prints the current position, total steps taken, and whether a beeper is present at that position.




