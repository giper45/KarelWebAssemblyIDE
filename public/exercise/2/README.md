# Navigate to Corner
Guide Karel from the starting position to the top-right corner of the world.
In this exercise, you'll practice precise navigation. Instead of wandering around, Karel needs to reach a specific destination.

## Your Task
Write code to make Karel navigate from position (1,1) to the top-right corner of the world at position (10,8).

## Strategy
1. Move east until you reach the rightmost wall
2. Move north until you reach the topmost wall
3. Use `front_is_clear()` to detect walls
4. Use proper turning logic to change direction

## Functions You'll Use
- `karel_move()` - Move forward one step
- `karel_turn_left()` - Turn 90 degrees counter-clockwise
- `front_is_clear()` - Check if path is clear
- `facing_east()`, `facing_north()` - Check current direction

## Success Criteria
Karel should end up at the top-right corner and stop there.