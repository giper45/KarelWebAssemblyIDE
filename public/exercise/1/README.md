# Karel Welcome

## Objective
Learn how Karel moves in the world and practice basic navigation.

## Background
Karel is a simple robot that lives in a rectangular grid world. Karel can:
- Move forward one step with `karel_move()`
- Turn 90 degrees left with `karel_turn_left()`
- Check if the path ahead is clear with `front_is_clear()`

## Your Task
In this exercise, Karel starts at position (1,1) facing east. Your goal is to:
1. Make Karel move around the world
2. Practice avoiding walls by checking `front_is_clear()` before moving
3. Use `karel_turn_left()` to change direction when hitting a wall


Try to pick the first beeper under the wall. 


## Functions You'll Use
- `karel_move()` - Move forward one step
- `karel_turn_left()` - Turn 90 degrees counter-clockwise  
- `front_is_clear()` - Returns true if Karel can move forward

## Tips
- Always check if the front is clear before moving
- Turn left when you can't move forward
- Watch Karel navigate around the world automatically
