# Array of Positions

## Objective
Learn to use arrays to store coordinate data and make Karel visit specific positions in a planned sequence.

## Background
Arrays are fundamental data structures in C that allow you to store multiple values of the same type. In this exercise, you'll use arrays to store x and y coordinates, then make Karel navigate to each position in sequence.

## Your Task
Karel needs to visit a series of specific positions where beepers are located. Instead of hardcoding each move, you'll:

1. **Create arrays** to store the target positions
2. **Use loops** to iterate through the array
3. **Implement navigation** to move Karel to each position
4. **Collect beepers** at each target location

### Target Positions
Karel must visit these positions in order:
- (3, 2)
- (1, 4) 
- (5, 1)
- (4, 3)
- (2, 5)

## Programming Concepts You'll Learn

### 1. Array Declaration and Initialization
```c
int x_positions[] = {3, 1, 5, 4, 2};
int y_positions[] = {2, 4, 1, 3, 5};
```

### 2. Array Length Calculation
```c
int num_positions = sizeof(x_positions) / sizeof(x_positions[0]);
```

### 3. Array Traversal
```c
for (int i = 0; i < num_positions; i++) {
    // Access x_positions[i] and y_positions[i]
}
```

### 4. Coordinate Navigation
You'll need to implement logic to move Karel from his current position to a target position.

## Functions You'll Use
- `karel_move()` - Move forward one step
- `karel_turn_left()` - Turn 90 degrees counter-clockwise
- `karel_pick_beeper()` - Pick up a beeper
- `beepers_present()` - Check if beepers are at current position

## Strategy Hints

### Navigation Logic
To move from current position to target position:
1. Calculate the difference in x and y coordinates
2. Move horizontally first, then vertically (or vice versa)
3. Use loops to repeat movements

### Direction Management
Remember Karel's direction system:
- 0 = East (right)
- 1 = North (up) 
- 2 = West (left)
- 3 = South (down)

## Success Criteria
- Karel visits all 5 target positions in the correct order
- Karel picks up the beeper at each position
- Your solution uses arrays to store the coordinates
- Karel ends up at the final position (2, 5)

## Code Structure Template
```c
void navigate_to_position(int target_x, int target_y) {
    // Implement navigation logic
}

void visit_all_positions() {
    int x_positions[] = {3, 1, 5, 4, 2};
    int y_positions[] = {2, 4, 1, 3, 5};
    int num_positions = sizeof(x_positions) / sizeof(x_positions[0]);
    
    for (int i = 0; i < num_positions; i++) {
        navigate_to_position(x_positions[i], y_positions[i]);
        if (beepers_present()) {
            karel_pick_beeper();
        }
    }
}
```

## Why This Matters
Arrays are essential in C programming for:
- **Data organization** - Store related values together
- **Efficient processing** - Use loops to process multiple items
- **Scalability** - Easy to add or modify data
- **Memory efficiency** - Contiguous memory allocation
