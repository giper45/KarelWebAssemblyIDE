# Solution: Navigate to Corner

## Solution Explanation
This exercise requires systematic navigation using direction checking and movement logic.

## Complete Solution
```c
void loop(double timeSec, double elapsedSec) {
    draw();
    
    static double lastMoveTime = 0;
    
    if (timeSec - lastMoveTime > 0.5) {
        // First phase: move east until hitting the right wall
        if (facing_east() && front_is_clear()) {
            karel_move();
        }
        // Turn to face north when hitting east wall
        else if (facing_east() && !front_is_clear()) {
            karel_turn_left(); // Now facing north
        }
        // Second phase: move north until hitting the top wall
        else if (facing_north() && front_is_clear()) {
            karel_move();
        }
        // Mission accomplished - Karel is at top-right corner
        else if (facing_north() && !front_is_clear()) {
            printf("Karel reached the corner!");
            return; // Stop execution
        }
        
        lastMoveTime = timeSec;
    }
}
```

## Strategy Breakdown
1. **Phase 1**: Move east until hitting the boundary
2. **Phase 2**: Turn north and move until hitting the top boundary
3. **Completion**: Stop when destination is reached

## Key Concepts
- **Direction Testing**: Using `facing_east()` and `facing_north()`
- **Sequential Logic**: Two-phase movement plan
- **Termination Condition**: Stopping when goal is achieved

## Alternative Approach
You could also navigate by coordinates:
```c
if (karel.x < WORLD_WIDTH && facing_east()) {
    if (front_is_clear()) karel_move();
} else if (karel.y < WORLD_HEIGHT) {
    // Face north and move
    while (!facing_north()) karel_turn_left();
    if (front_is_clear()) karel_move();
}
```
