# Swap Beeper

Learn to combine movement, conditional logic, and beeper manipulation to relocate objects based on environmental conditions.

## Problem Description
Karel starts at position (1,1) and must find an initial beeper, pick it up, then search for the first empty cell (no beeper present) to place it there. This exercise combines multiple concepts: searching, collecting, and conditional placement.

## Initial Setup
- Karel starts at (1,1) facing East
- One beeper is placed at position (3,1) 
- Additional beepers are placed at positions (5,1), (6,1), (8,1)
- Karel must pick up the first beeper found and move it to the first empty cell

## Enum explanation 
The enum `Phase`  is used to track which part of the operation Karel is currently performing:
```c
enum Phase {
  SEARCHING_BEEPER,
  SEARCHING_EMPTY_CELL,
  COMPLETE
};

```

You can use this enum to control the flow of your program, ensuring Karel knows whether it is currently looking for a beeper to pick up or an empty cell to place the beeper.

Look at the `studentCode()` function to see how to implement this logic.
The conditions are implemented using a `switch` statement based on the current phase of the operation:
```c
switch (currentPhase) {
    case SEARCHING_BEEPER:
        // Logic for searching beeper
        break;
    case SEARCHING_EMPTY_CELL:
        // Logic for searching empty cell
        break;
    case COMPLETE:
        // Logic for completion
        break;
}
```

Implement your logic inside the appropriate case blocks to control Karel's behavior based on the current phase.



## Expected Behavior
1. **Search Phase**: Move forward until you find the first beeper
2. **Collection Phase**: Pick up the beeper when found
3. **Search Phase 2**: Continue moving to find the first empty cell
4. **Placement Phase**: Drop the beeper at the first empty position found
5. **Completion**: Stop and report the swap operation


### 2. **State Tracking**
Track which phase of the algorithm you're in:
- Searching for beeper to pick up
- Carrying beeper, searching for empty cell
- Beeper placed, operation complete

### 3. **Conditional Logic**
Use different conditions for different phases:
- `!beepers_present()` - looking for a beeper to pick up
- `beepers_present()` - looking for an empty cell while carrying

## Expected Output
```
Phase 1: Searching for beeper to pick up...
Step 1: Moved to (2, 1) - Searching...
Step 2: Moved to (3, 1) - Searching...
Beeper found at (3, 1)! Picking up...
Phase 2: Carrying beeper, searching for empty cell...
Step 3: Moved to (4, 1) - Searching for empty cell...
Step 4: Moved to (7, 1) - Searching for empty cell...
Empty cell found at (7, 1)! Placing beeper...
SUCCESS! Beeper swapped from (3, 1) to (7, 1) in 4 steps!
```

## Task Requirements
Complete the `studentCode()` function to:
1. Use delayed movement for visible animation
2. Search for the first beeper and pick it up
3. Continue searching for the first empty cell
4. Place the beeper at the empty location
5. Track and report the swap operation
