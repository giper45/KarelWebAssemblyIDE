# Solution: Karel Square Path

## Solution Explanation
This exercise demonstrates how to create precise geometric patterns using counting and state management.

## Complete Solution
```c
void loop(double timeSec, double elapsedSec) {
    draw();
    
    static double lastMoveTime = 0;
    static int step = 0;      // Steps taken on current side
    static int side = 0;      // Which side of square (0-3)
    
    if (timeSec - lastMoveTime > 0.5) {
        if (side < 4) {  // Still working on the square
            if (step < 3) {
                // Move forward 3 steps for current side
                karel_move();
                step++;
            } else {
                // Completed current side, turn for next side
                karel_turn_left();
                step = 0;     // Reset step counter
                side++;       // Move to next side
            }
        }
        // Square completed when side == 4
        
        lastMoveTime = timeSec;
    }
}
```

## Alternative Solution (Loop-based)
```c
void loop(double timeSec, double elapsedSec) {
    draw();
    
    static double lastMoveTime = 0;
    static int totalMoves = 0;
    static bool squareComplete = false;
    
    if (!squareComplete && timeSec - lastMoveTime > 0.5) {
        if (totalMoves % 4 == 3) {
            // Every 4th move is a turn
            karel_turn_left();
        } else {
            // Other moves are forward
            karel_move();
        }
        
        totalMoves++;
        if (totalMoves >= 16) {  // 4 sides × 4 actions each
            squareComplete = true;
            printf("Square completed!");
        }
        
        lastMoveTime = timeSec;
    }
}
```

## Key Concepts
- **State Tracking**: Using static variables to remember progress
- **Counting Logic**: Tracking steps and sides separately
- **Pattern Recognition**: 4 sides × (3 moves + 1 turn) = square
- **Completion Detection**: Knowing when the pattern is finished

## Debugging Tips
1. Print current step and side values to track progress
2. Adjust timing to see each move clearly
3. Use different patterns (2x2, 4x4) to test flexibility
4. Verify Karel returns to exact starting position and orientation

## Extensions
- Make the square size configurable
- Create rectangles instead of squares
- Add beeper placement at each corner
