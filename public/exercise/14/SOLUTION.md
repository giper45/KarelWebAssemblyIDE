# Solution: Array of Positions

## Solution Explanation
This exercise demonstrates how to use arrays to store coordinate data and implement navigation logic. The solution combines array traversal with geometric navigation algorithms.

## Complete Solution
```c
void navigate_to_position(int target_x, int target_y) {
    // Move horizontally first
    while (karel_get_x() != target_x) {
        if (karel_get_x() < target_x) {
            // Need to move east
            while (karel_get_direction() != 0) { // 0 = East
                karel_turn_left();
            }
            karel_move();
        } else {
            // Need to move west
            while (karel_get_direction() != 2) { // 2 = West
                karel_turn_left();
            }
            karel_move();
        }
    }
    
    // Move vertically
    while (karel_get_y() != target_y) {
        if (karel_get_y() < target_y) {
            // Need to move north
            while (karel_get_direction() != 1) { // 1 = North
                karel_turn_left();
            }
            karel_move();
        } else {
            // Need to move south
            while (karel_get_direction() != 3) { // 3 = South
                karel_turn_left();
            }
            karel_move();
        }
    }
}

void visit_all_positions() {
    int x_positions[] = {3, 1, 5, 4, 2};
    int y_positions[] = {2, 4, 1, 3, 5};
    int num_positions = sizeof(x_positions) / sizeof(x_positions[0]);
    
    for (int i = 0; i < num_positions; i++) {
        printf("Moving to position (%d, %d)...\n", x_positions[i], y_positions[i]);
        navigate_to_position(x_positions[i], y_positions[i]);
        
        if (beepers_present()) {
            karel_pick_beeper();
            printf("Beeper collected at (%d, %d)\n", karel_get_x(), karel_get_y());
        }
    }
    printf("All positions visited!\n");
}

void studentCode() {
    static bool missionComplete = false;
    
    if (!missionComplete) {
        visit_all_positions();
        missionComplete = true;
    }
}
```

## Alternative Solution (State-Based for Real-Time)
```c
void navigate_to_position(int target_x, int target_y) {
    static bool moving_horizontal = true;
    static bool positioned = false;
    
    if (!positioned) {
        if (moving_horizontal && karel_get_x() != target_x) {
            if (karel_get_x() < target_x) {
                while (karel_get_direction() != 0) karel_turn_left();
                karel_move();
            } else {
                while (karel_get_direction() != 2) karel_turn_left();
                karel_move();
            }
        } else if (karel_get_y() != target_y) {
            moving_horizontal = false;
            if (karel_get_y() < target_y) {
                while (karel_get_direction() != 1) karel_turn_left();
                karel_move();
            } else {
                while (karel_get_direction() != 3) karel_turn_left();
                karel_move();
            }
        } else {
            positioned = true;
            moving_horizontal = true; // Reset for next call
        }
    }
    
    return positioned;
}

void studentCode() {
    static int current_target = 0;
    static bool missionComplete = false;
    
    int x_positions[] = {3, 1, 5, 4, 2};
    int y_positions[] = {2, 4, 1, 3, 5};
    int num_positions = 5;
    
    if (!missionComplete && current_target < num_positions) {
        if (navigate_to_position(x_positions[current_target], y_positions[current_target])) {
            if (beepers_present()) {
                karel_pick_beeper();
                printf("Beeper collected at (%d, %d)\n", karel_get_x(), karel_get_y());
            }
            current_target++;
        }
        
        if (current_target >= num_positions) {
            missionComplete = true;
            printf("All positions visited!\n");
        }
    }
}
```

## Key Programming Concepts Demonstrated

### 1. Array Declaration and Initialization
```c
int x_positions[] = {3, 1, 5, 4, 2};  // Implicit size (5 elements)
int y_positions[] = {2, 4, 1, 3, 5};  // Parallel array for y coordinates
```

### 2. Array Size Calculation
```c
int num_positions = sizeof(x_positions) / sizeof(x_positions[0]);
// sizeof(x_positions) = total bytes (5 * sizeof(int))
// sizeof(x_positions[0]) = bytes per element (sizeof(int))
// Result: number of elements
```

### 3. Array Traversal with For Loop
```c
for (int i = 0; i < num_positions; i++) {
    // Access elements: x_positions[i], y_positions[i]
}
```

### 4. Coordinate Navigation Algorithm
The navigation function implements a Manhattan distance algorithm:
1. Move horizontally to correct x-coordinate
2. Move vertically to correct y-coordinate

### 5. Direction Management
```c
// Karel's direction constants:
// 0 = East, 1 = North, 2 = West, 3 = South
while (karel_get_direction() != target_direction) {
    karel_turn_left();
}
```

## Advanced Concepts

### Parallel Arrays
Using two arrays to store related data:
```c
x_positions[0] = 3, y_positions[0] = 2  // Position (3,2)
x_positions[1] = 1, y_positions[1] = 4  // Position (1,4)
```

### Algorithm Optimization
The solution could be improved with:
- **Shortest path calculation** between positions
- **Direction optimization** to minimize turns
- **Obstacle avoidance** if walls are present

### Memory Considerations
```c
// Stack allocation (automatic)
int positions[10];  // Fixed size, fast access

// Could be extended to dynamic allocation:
// int* positions = malloc(count * sizeof(int));
```

## Real-World Applications
This exercise teaches concepts used in:
- **GPS navigation systems** - Route planning through waypoints
- **Robot pathfinding** - Moving through coordinate sequences  
- **Game development** - Character movement along predetermined paths
- **Data visualization** - Plotting points from coordinate arrays

The combination of arrays and navigation logic is fundamental to many programming applications involving spatial data and sequential processing.
