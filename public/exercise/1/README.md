# Welcome to Karel's World!
Karel is a robot that can navigate a grid world, and in this exercise, you'll help Karel move around while avoiding walls.
Karel lives in a rectangular grid world. Karel can:
- Move forward one step with `karel_move()`
- Turn 90 degrees left with `karel_turn_left()`
- Check if the path ahead is clear with `front_is_clear()`
- Pick up a beeper with `karel_pick_beeper()`
- Put down a beeper with `karel_put_beeper()`

See the documentation for more details on other functions.

## Your Task
In this exercise, you do not have tasks!
Karel starts at position (1,1) facing east. Your main goal is to:
1. Make Karel move around the world
2. Practice avoiding walls by checking `front_is_clear()` before moving
3. Use `karel_turn_left()` to change direction when hitting a wall

Try to pick the first beeper under the wall.


- `karel_move()` - Move forward one step
- `karel_turn_left()` - Turn 90 degrees counter-clockwise  
- `front_is_clear()` - Returns true if Karel can move forward

## Tips
- Always check if the front is clear before moving
- Turn left when you can't move forward
- Watch Karel navigate around the world automatically

## Documentation
Look at `SOLUTION.md` for a tutorial on how to use Karel's functions.
Also on the top right corner, you can find a button to see the documentation for all Karel's functions.
