# Solution: Karel First Steps

## Solution Explanation
This exercise demonstrates Karel's basic movement pattern: move forward when possible, turn left when blocked.

## Key Concepts
1. **Conditional Movement**: Always check `front_is_clear()` before moving
2. **Wall Avoidance**: Use `karel_turn_left()` to navigate around obstacles
3. **Loop Logic**: The movement logic runs continuously in the main loop

Look at this code:
```c
void studentCode()
{
    drawWorld();
    karel_move();
    if (!front_is_clear())
    {
        karel_turn_left();
    }
    if (beepers_present())
    {
        karel_pick_beeper();
    }

}

```

The `drawWorld()` function always renders the world. 
The `karel_move()` moves Karel of a single step. 
If `front_is_clear()` is false, there is a wall (or the end of the world) in front of Karel, so it turns left with `karel_turn_left()`.

The `beepers_present()` checks if there is a beeper in Karel's current position, and if so, it picks it up with `karel_pick_beeper()`.

With this logic, Karel is able to pick the first beeper under the wall and navigate around the world.

Try some other functions, for example, try to go to the north-west corner of the world, or try to pick all the beepers in the world.




## Expected Behavior
Karel will navigate around the world's perimeter, following walls and turning when necessary. This creates a predictable patrol pattern.

## Learning Outcomes
- Understanding basic movement commands
- Learning conditional logic with world sensing
- Practicing timing-controlled robot behavior

