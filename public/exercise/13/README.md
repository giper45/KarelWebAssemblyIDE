# Make Code Modular

## Objective
Learn to break complex problems into smaller, reusable functions by refactoring the square drawing problem from Exercise 3.

## Background
In Exercise 3, you solved the problem of making Karel walk in a square pattern. Now you'll take that same problem and break it down into modular functions. This demonstrates one of the most important principles in programming: **modularity** - the practice of dividing a program into separate, interchangeable components.

## Your Task
Rewrite the square walking solution using these specific functions:

### Required Functions to Implement:
1. **`move_one_side()`** - Move Karel forward 3 steps (one side of the square)
2. **`turn_corner()`** - Turn Karel left to prepare for the next side
3. **`draw_square()`** - Use the above functions to draw a complete square

### Function Specifications:
- **`move_one_side()`**: Should move Karel exactly 3 steps forward
- **`turn_corner()`**: Should turn Karel left once (90 degrees)
- **`draw_square()`**: Should call `move_one_side()` and `turn_corner()` in the right sequence to complete a square

## Programming Concepts You'll Learn
- **Function Definition**: Creating your own functions with `void function_name()`
- **Function Calls**: Using your functions inside other functions
- **Code Reusability**: Using the same function multiple times
- **Abstraction**: Hiding implementation details inside functions
- **Modularity**: Breaking complex problems into smaller pieces

## Strategy
Think about the square pattern:
1. What actions are repeated?
2. How can you group related actions together?
3. How do the functions work together to solve the bigger problem?

## Success Criteria
Karel should trace a 3x3 square and return to the exact starting position, but this time your code should be organized into clear, reusable functions.

## Code Structure Example
Your solution should follow this pattern:
```c
void move_one_side() {
    // Your implementation here
}

void turn_corner() {
    // Your implementation here
}

void draw_square() {
    // Use move_one_side() and turn_corner() here
}

void studentCode() {
    // Call draw_square() when appropriate
}
```

## Why This Matters
Modular code is:
- **Easier to read** - Each function has a clear purpose
- **Easier to debug** - Problems are isolated to specific functions
- **Reusable** - Functions can be used in multiple places
- **Maintainable** - Changes only need to be made in one place

This reflects real-world C programming where complex systems are built from many small, focused functions.
