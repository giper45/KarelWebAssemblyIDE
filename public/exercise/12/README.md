# Zig-Zag Fill

Learn to use nested loops and direction control to fill rectangular areas efficiently using a zig-zag pattern.

## Problem Description
Karel must fill a 5x5 area with beepers, moving in a zig-zag pattern. This means:
- Row 1: Move left to right, placing beepers
- Row 2: Move right to left, placing beepers  
- Row 3: Move left to right, placing beepers
- Row 4: Move right to left, placing beepers
- Row 5: Move left to right, placing beepers

After completing each row, Karel must move up one row and reverse direction to start the next row.

## Initial Setup
- Karel starts at position (1,1) facing East
- The world is empty - Karel will place beepers to fill a 5x5 area
- Karel must place a beeper at every position from (1,1) to (5,5)

## Learning Objectives
1. **Nested Loop Control**: Use outer loop for rows, inner loop for columns
2. **Direction Management**: Alternate between east and west directions
3. **Pattern Recognition**: Understand zig-zag movement patterns
4. **Coordinate Tracking**: Keep track of current position and direction

## Expected Behavior
1. **Row 1**: Start at (1,1), move east placing beepers at (1,1), (2,1), (3,1), (4,1), (5,1)
2. **Turn Around**: Turn to face west and move north to (5,2)
3. **Row 2**: Move west placing beepers at (5,2), (4,2), (3,2), (2,2), (1,2)
4. **Turn Around**: Turn to face east and move north to (1,3)
5. **Continue**: Repeat pattern for rows 3, 4, and 5

## Movement Pattern
```
Row 5: → → → → →  (East direction)
Row 4: ← ← ← ← ←  (West direction)  
Row 3: → → → → →  (East direction)
Row 2: ← ← ← ← ←  (West direction)
Row 1: → → → → →  (East direction, starting row)
```

## Key Concepts

### 1. **Nested Loop Structure**
```c
for (int row = 1; row <= 5; row++) {
    for (int col = 1; col <= 5; col++) {
        // Place beeper and move
    }
    // Prepare for next row
}
```

### 2. **Direction Alternation**
```c
if (row % 2 == 1) {
    // Odd rows: move east (left to right)
} else {
    // Even rows: move west (right to left)
}
```

### 3. **Turn Around Logic**
```c
// Turn 180 degrees
karel_turn_left();
karel_turn_left();
```

## Expected Output
```
Starting zig-zag fill pattern...
Row 1: Placing beeper at (1,1)
Row 1: Moving east to (2,1), placing beeper
Row 1: Moving east to (3,1), placing beeper
Row 1: Moving east to (4,1), placing beeper
Row 1: Moving east to (5,1), placing beeper
Turning around and moving to row 2...
Row 2: Placing beeper at (5,2)
Row 2: Moving west to (4,2), placing beeper
Row 2: Moving west to (3,2), placing beeper
Row 2: Moving west to (2,2), placing beeper
Row 2: Moving west to (1,2), placing beeper
[Pattern continues for rows 3-5]
Zig-zag fill complete! 25 beepers placed.
```

## Task Requirements
Complete the `studentCode()` function to:
1. Use nested loops for row and column iteration
2. Place a beeper at each position in the 5x5 area
3. Alternate direction between rows (east for odd rows, west for even rows)
4. Handle turning around and moving to the next row
5. Track progress with appropriate printf statements
6. Ensure Karel ends at the final position (5,5) or (1,5) depending on the pattern

## Hints
- Use modulo operator (%) to determine if row number is odd or even
- Remember to place a beeper before moving (except for the last position in each row)
- Karel needs to turn around (180°) between rows
- After turning around, Karel needs to move north to the next row
- Consider using separate phases for row filling and row transition

## Extensions
- Modify to fill a 3x3 or 7x7 area
- Create a spiral fill pattern instead of zig-zag
- Add validation to ensure all positions are filled
- Implement the pattern in reverse (start from top-left)
