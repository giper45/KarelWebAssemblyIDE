# Solution: Make Code Modular

## Solution Explanation
This exercise demonstrates how to break a complex problem into smaller, reusable functions. The square drawing problem from Exercise 3 is refactored to use modular functions that each have a single, clear responsibility.

## Complete Solution
```c
void move_one_side() {
    // Move Karel forward 3 steps (one side of the square)
    for (int i = 0; i < 3; i++) {
        karel_move();
    }
}

void turn_corner() {
    // Turn Karel left to prepare for the next side
    karel_turn_left();
}

void draw_square() {
    // Use move_one_side() and turn_corner() to draw a complete square
    for (int side = 0; side < 4; side++) {
        move_one_side();
        turn_corner();
    }
}

void studentCode() {
    static bool squareComplete = false;
    
    if (!squareComplete) {
        draw_square();
        squareComplete = true;
        printf("Square completed using modular functions!\n");
    }
}
```

## Alternative Solution (State-Based for Real-Time Execution)
If you want to maintain the real-time, step-by-step execution pattern:

```c
void move_one_side() {
    karel_move();
}

void turn_corner() {
    karel_turn_left();
}

void draw_square() {
    static int step = 0;
    static int side = 0;
    static bool squareComplete = false;
    
    if (!squareComplete && side < 4) {
        if (step < 3) {
            move_one_side();
            step++;
            printf("Side %d: Step %d completed\n", side + 1, step);
        } else {
            turn_corner();
            step = 0;
            side++;
            printf("Completed side %d, turning corner\n", side);
        }
        
        if (side >= 4) {
            squareComplete = true;
            printf("Square completed using modular functions!\n");
        }
    }
}

void studentCode() {
    draw_square();
}
```

## Key Programming Concepts Demonstrated

### 1. Function Modularity
- **`move_one_side()`**: Handles the movement logic for one side
- **`turn_corner()`**: Handles the turning logic
- **`draw_square()`**: Orchestrates the complete square drawing

### 2. Single Responsibility Principle
Each function has one clear job:
- `move_one_side()` only moves
- `turn_corner()` only turns
- `draw_square()` only coordinates

### 3. Abstraction
The `draw_square()` function hides the implementation details of how to move and turn, making the code easier to understand at a high level.

### 4. Reusability
The `move_one_side()` and `turn_corner()` functions can be reused in other contexts or combined differently.

## Benefits of This Approach

### Code Readability
```c
// Instead of this unclear code:
for (int i = 0; i < 4; i++) {
    karel_move(); karel_move(); karel_move();
    karel_turn_left();
}

// We have this clear, self-documenting code:
for (int side = 0; side < 4; side++) {
    move_one_side();
    turn_corner();
}
```

### Easy Modification
Want to change the square size? Just modify `move_one_side()`:
```c
void move_one_side() {
    for (int i = 0; i < 5; i++) {  // Now it's a 5x5 square
        karel_move();
    }
}
```

### Debugging
If Karel isn't turning correctly, you know the problem is in `turn_corner()`. If he's not moving the right distance, check `move_one_side()`.

### Extension
You can easily create new shapes:
```c
void draw_rectangle() {
    for (int i = 0; i < 2; i++) {
        move_one_side();      // Short side
        turn_corner();
        move_long_side();     // Long side
        turn_corner();
    }
}
```

## Real-World Application
This modular approach is fundamental in C programming:
- **Device drivers** break hardware interaction into small functions
- **Games** separate rendering, input, and game logic
- **Operating systems** modularize process management, memory allocation, etc.

The principle of "do one thing well" makes code maintainable and scalable.
