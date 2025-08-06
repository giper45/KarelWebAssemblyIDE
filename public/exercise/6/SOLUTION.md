# Solution: Count Beepers
This exercise teaches basic counting logic by having Karel count beepers along a street and display the running count.

## Solution
```c
void studentCode() {
    bool missionComplete = false;
    int beeperCount = 0;
    
    while (!missionComplete) {
        // TODO: Implement counting logic
        // 1. Check if beeper present at current position
        // 2. Increment counter if beeper found
        // 3. Move forward if possible
        // 4. Display final count when wall reached
        
        if (beepers_present())
        {
            beeperCount++;
        }
        karel_move();
        if (!front_is_clear())
        {
            printf("Counting completed, beeperCount: %d", beeperCount);
            missionComplete = true;
            
        }
        else 
        {
            printf("Position: (%d, %d) | Beepers counted: %d\n", 
               karel_get_x(), karel_get_y(), beeperCount);
        }
        
        
    }
}
```

The exercise requires Karel to count the number of beepers along a street. The provided solution implements a simple counting mechanism using a while loop and conditionals to check for beepers and walls. Karel moves forward, counting beepers until it reaches a wall, at which point it displays the final count.

It starts by defining a boolean flag `missionComplete` to track when Karel has finished counting. The `beeperCount` variable is initialized to zero. Inside the loop, Karel checks if a beeper is present at its current position and increments the count accordingly. It then moves forward and checks if the front is clear. If it encounters a wall, it prints the total count of beepers and sets `missionComplete` to true, ending the loop.
