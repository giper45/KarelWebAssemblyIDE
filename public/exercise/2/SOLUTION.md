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

### Solution
```c
void studentCode() {
    if (front_is_clear()) {
        karel_move();
    } else if (facing_east()) {
        karel_turn_left(); // Turn to north
    }
    // When facing north and front blocked = corner reached
}
```