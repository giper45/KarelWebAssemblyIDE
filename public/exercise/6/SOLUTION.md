# Solution: Count Beepers

## Solution Explanation
This exercise teaches basic counting logic by having Karel count beepers along a street and display the running count.

## Solution
```c
void studentCode() {
    static bool missionComplete = false;
    static int beeperCount = 0;
    
    if (!missionComplete) {
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

## Key Concepts Demonstrated

### 1. **Counting Logic**
```c
static int beeperCount = 0;
if (beeper_present()) {
    beeperCount++;  // Increment counter for each beeper found
}
```

### 2. **Loop Control**
```c
static bool missionComplete = false;
if (!missionComplete) {
    // Continue execution
}
```

### 3. **Movement with Boundary Check**
```c
if (front_is_clear()) {
    move();  // Continue moving
} else {
    // Wall reached, complete mission
    missionComplete = true;
}
```

### 4. **Real-time Feedback**
```c
printf("Position: (%d, %d) | Beepers counted: %d\n", 
       karel_get_x(), karel_get_y(), beeperCount);
```

## How It Works

1. **Check for Beeper**: At each position, check if a beeper is present
2. **Count**: If a beeper is found, increment the counter  
3. **Move**: If the front is clear, move forward to continue counting
4. **Complete**: When hitting a wall, display the final count and complete the mission
5. **Display**: Show current position and running count for tracking progress

## Expected Output

```
Position: (1, 1) | Beepers counted: 1
Position: (2, 1) | Beepers counted: 2  
Position: (3, 1) | Beepers counted: 2
Position: (4, 1) | Beepers counted: 3
Final count: 3 beepers total
```

## Debugging Tips
1. **Check beeper detection** - verify `beeper_present()` works correctly
2. **Monitor count increments** - ensure counter increases only when beepers are found
3. **Test boundary conditions** - confirm proper stopping at walls
4. **Verify output timing** - check that printf appears in real-time

## Common Mistakes to Avoid
- Incrementing count without checking for beeper presence
- Moving without checking if front is clear
- Not handling the wall boundary condition properly
- Forgetting to mark mission as complete
- Not handling phase transitions properly

## Extensions
- Count beepers in multiple rows
- Implement different counting patterns (every other beeper, etc.)
- Create visual counter displays using beeper arrangements
- Add validation to verify counting accuracy

## Learning Outcomes
- **Abstract Counting**: Convert observations to numerical data
- **Physical Representation**: Use beepers to represent abstract concepts
- **Multi-Phase Logic**: Organize complex tasks into manageable phases
- **State Management**: Track progress through different operational modes
