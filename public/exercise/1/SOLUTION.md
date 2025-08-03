# Solution: Karel First Steps

## Solution Explanation
This exercise demonstrates Karel's basic movement pattern: move forward when possible, turn left when blocked.

## Key Concepts
1. **Conditional Movement**: Always check `front_is_clear()` before moving
2. **Wall Avoidance**: Use `karel_turn_left()` to navigate around obstacles
3. **Loop Logic**: The movement logic runs continuously in the main loop

## Code Analysis
```c
static double lastMoveTime = 0;
if(timeSec - lastMoveTime > 1.0) {
    if(front_is_clear()) {
        karel_move();
    } else {
        karel_turn_left();
    }
    lastMoveTime = timeSec;
}
```

## What Happens
1. Karel checks if 1 second has passed (timing control)
2. If front is clear, Karel moves forward
3. If blocked by a wall, Karel turns left
4. This creates a wall-following behavior

## Expected Behavior
Karel will navigate around the world's perimeter, following walls and turning when necessary. This creates a predictable patrol pattern.

## Learning Outcomes
- Understanding basic movement commands
- Learning conditional logic with world sensing
- Practicing timing-controlled robot behavior

