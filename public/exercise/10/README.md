# Repeat Path

Learn to use for loops to repeat sequences of movements efficiently and create predictable patterns.

## Problem Description
Karel must move forward 3 cells, then turn around and move back 3 cells to return to the starting position. This complete sequence must be repeated 4 times total. Use a for loop to avoid code repetition and create clean, maintainable solutions.

## Initial Setup
- Karel starts at position (1,1) facing East
- No beepers are placed in the world
- Karel has a clear path of 10 cells to move forward and backward
- The goal is to demonstrate controlled repetition using loops

## Learning Objectives
1. **For Loop Mastery**: Learn to use for loops for exact repetition counts
2. **Sequence Organization**: Break complex behavior into repeatable patterns
3. **Direction Management**: Control Karel's orientation for bidirectional movement
4. **Code Efficiency**: Replace repetitive code with loop structures

## Expected Behavior
1. **Forward Movement**: Move 3 cells forward (East)
2. **Turn Around**: Execute 2 left turns to face West
3. **Backward Movement**: Move 3 cells backward (West) to starting column
4. **Reset Direction**: Execute 2 left turns to face East again
5. **Repeat**: Perform this complete sequence 4 times

## Movement Pattern
```
Start: (1,1) facing East

Iteration 1:
- Move East to (4,1)
- Turn around to face West  
- Move West back to (1,1)
- Turn around to face East

Iteration 2-4: Repeat the same pattern
```

## Key Concepts
### 1. **For Loop Structure**
Use a for loop to repeat the movement sequence exactly 4 times:
```c
for (int i = 0; i < 4; i++) {
    // Movement sequence here
}
```

### 2. **Turn Around Function**
Create a helper function or use multiple left turns to reverse direction:
```c
// Turn 180 degrees (turn around)
karel_turn_left();
karel_turn_left();
```

### 3. **Movement Counting**
Use nested loops or repeated moves for the 3-cell forward/backward movement:
```c
// Move forward 3 cells
for (int j = 0; j < 3; j++) {
    karel_move();
}
```

## Expected Output
```
Starting iteration 1...
Moving forward: Step 1 to (2,1)
Moving forward: Step 2 to (3,1) 
Moving forward: Step 3 to (4,1)
Turning around to face West...
Moving backward: Step 1 to (3,1)
Moving backward: Step 2 to (2,1)
Moving backward: Step 3 to (1,1)
Turning around to face East...
Iteration 1 complete!

Starting iteration 2...
[Pattern repeats 3 more times]

All 4 iterations completed! Karel back at starting position.
```

## Task Requirements
Complete the `studentCode()` function to:
1. Use a for loop to repeat the sequence 4 times
2. Move forward 3 cells in each iteration
3. Turn around efficiently (180 degrees)
4. Move backward 3 cells to return to start
5. Reset direction to face East for next iteration
6. Add progress tracking with printf statements

## Hints
- A complete "turn around" requires two left turns
- You can use nested for loops: outer for iterations, inner for movements
- Count your movements to ensure Karel moves exactly 3 cells each direction
- Verify Karel ends at the same position and direction as started

## Extensions
- Modify to repeat 6 times instead of 4
- Change the forward distance to 5 cells
- Add beeper placement at the furthest point of each iteration
- Create a variable pattern where distance increases each iteration
