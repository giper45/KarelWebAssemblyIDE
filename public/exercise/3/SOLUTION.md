# Solution: Karel Square Path

## Solution Explanation
This exercise demonstrates how to create precise geometric patterns using counting and state management within the existing `studentCode()` structure.

## Complete Solution
```c
void studentCode() {
    drawWorld();
    
    static int step = 0;      // Steps taken on current side
    static int side = 0;      // Which side of square (0-3)
    static bool squareComplete = false;
    
    if (!squareComplete) {
        if (side < 4) {  // Still working on the square
            if (step < 3) {
                // Move forward 3 steps for current side
                karel_move();
                step++;
                printf("Side %d: Step %d completed\n", side + 1, step);
            } else {
                // Completed current side, turn for next side
                karel_turn_left();
                step = 0;     // Reset step counter
                side++;       // Move to next side
                printf("Completed side %d, turning left\n", side);
            }
        } else {
            squareComplete = true;
            printf("Square completed! Karel is back at start.\n");
        }
    }
}
```


## Key Concepts
- **State Tracking**: Using static variables to remember progress between calls
- **Incremental Logic**: Each `studentCode()` call performs one action
- **Pattern Recognition**: 4 sides × (3 moves + 1 turn) = complete square
- **Completion Detection**: Knowing when the pattern is finished
- **Integration**: Works with existing `loop()` and timing structure

## How It Works
1. **`loop()` calls `studentCode()` every second**
2. **`studentCode()` performs one action per call**:
   - Move forward (3 times per side)
   - Turn left (once per side)
3. **Static variables track progress across calls**
4. **Square completes after 16 total actions**

## Pattern Breakdown
```
Side 1: Move → Move → Move → Turn Left
Side 2: Move → Move → Move → Turn Left  
Side 3: Move → Move → Move → Turn Left
Side 4: Move → Move → Move → Turn Left
Result: Back at starting position facing East
```

## Debugging Tips
1. Print current step and side values to track progress
2. Adjust timing to see each move clearly
3. Use different patterns (2x2, 4x4) to test flexibility
4. Verify Karel returns to exact starting position and orientation

## Extensions
- Make the square size configurable
- Create rectangles instead of squares
- Add beeper placement at each corner
