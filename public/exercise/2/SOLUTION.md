# Solution: Navigate to Corner

## Solution Explanation
This exercise requires systematic navigation using direction checking and movement logic to reach the top-right corner.


## Strategy Breakdown
1. **Phase 1**: Move east until hitting the boundary wall
2. **Phase 2**: Turn north (left turn from east) and move until hitting top boundary  
3. **Completion**: Stop when both walls are reached (top-right corner)

## Key Concepts
- **Direction Testing**: Using `facing_east()` and `facing_north()`
- **Wall Detection**: Using `front_is_clear()` to detect boundaries
- **Sequential Logic**: Two-phase movement plan with state transitions
- **Termination**: Natural stopping when destination is reached

## Code Flow
```
Start (1,1) facing East
↓
Move East while front_is_clear()
↓
Hit right wall → Turn Left (now facing North)  
↓
Move North while front_is_clear()
↓
Hit top wall → Destination reached!
```

### Simple solution code
The most simple solution involves moving step by step without using loops. 
We can observe that the world is a 10x10 grid, and Karel needs to move 9 steps east and then 9 steps north to reach the top-right corner (10,10) from the starting position (1,1).

Here is the code that achieves this:
```c
void studentCode() 
{
    karel_move();
    karel_move();
    karel_move();
    karel_move();
    karel_move();
    karel_move();
    karel_move();
    karel_move();
    karel_move();
    karel_turn_left();
    karel_move();
    karel_move();
    karel_move();
    karel_move();
    karel_move();
    karel_move();
    karel_move();
    karel_move();
    karel_move();
}
```

### Do you already know loops?
If you are familiar with loops, you can simplify the solution using a loop structure to handle the repeated movements:
```c
void studentCode()
{
    while (front_is_clear()) {
        karel_move();
    }
    karel_turn_left();
    while (front_is_clear()) {
        karel_move();
    }
}
```
This version uses `while` loops to handle the movement in both phases, making the code cleaner and more efficient.
We will see how to use loops in next exercises, but for now, you can use the loop version if you are comfortable with it.