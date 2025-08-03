# Karel Square Path

## Objective
Program Karel to walk in a perfect square pattern and return to the starting position.

## Background
This exercise teaches you how to create precise movement patterns using Karel's basic commands. You'll learn to coordinate movement and turning to create geometric shapes.

## Your Task
Write code that makes Karel:
1. Start at position (1,1) facing east
2. Move forward 3 steps
3. Turn left and move forward 3 steps  
4. Turn left and move forward 3 steps
5. Turn left and move forward 3 steps
6. End up back at the starting position facing east

## Functions You'll Use
- `karel_move()` - Move forward one step
- `karel_turn_left()` - Turn 90 degrees counter-clockwise

## Strategy
Think about how many times you need to repeat the pattern:
- Move forward 3 times
- Turn left once
- Repeat this 4 times to complete the square

## Success Criteria
Karel should trace a 3x3 square and return to the exact starting position and orientation.
