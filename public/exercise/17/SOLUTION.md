# Solution: Matrici Bidimensionali con Karel

This exercise demonstrates how to work with 2D arrays (matrices) in C programming, using Karel to navigate and manipulate a matrix that represents the world state.

## Problem Analysis

Karel needs to:
- Create and initialize a 5x5 2D array to represent the world
- Map beeper locations in the matrix
- Use the matrix to guide navigation
- Update the matrix as actions are performed
- Understand coordinate system conversion between Karel world and array indices

## Key Concept: Coordinate System Mapping

The most important concept is converting between Karel coordinates and array indices:

```c
// Karel uses coordinates (1,1) to (5,5) where (1,1) is bottom-left
// Arrays use indices [0][0] to [4][4] where [0][0] is top-left

// Conversion formulas:
array_row = MATRIX_SIZE - karel_y;    // y=1 → row=4, y=5 → row=0  
array_col = karel_x - 1;              // x=1 → col=0, x=5 → col=4

// Example mappings:
Karel (1,1) ↔ array[4][0]  (bottom-left)
Karel (5,5) ↔ array[0][4]  (top-right)
Karel (3,3) ↔ array[2][2]  (center)
```

## Solution Strategy

### 1. Matrix Declaration and Initialization
```c
#define MATRIX_SIZE 5
static int world_matrix[MATRIX_SIZE][MATRIX_SIZE];

void initialize_matrix(int matrix[MATRIX_SIZE][MATRIX_SIZE]) {
    // Initialize all cells to 0 (empty)
    for (int row = 0; row < MATRIX_SIZE; row++) {
        for (int col = 0; col < MATRIX_SIZE; col++) {
            matrix[row][col] = 0;
        }
    }
    
    // Set beeper locations to 1 using coordinate conversion
    matrix[0][1] = 1;  // Karel (2,5) → array[0][1]
    matrix[0][4] = 1;  // Karel (5,5) → array[0][4]
    matrix[1][2] = 1;  // Karel (3,4) → array[1][2]
    matrix[2][0] = 1;  // Karel (1,3) → array[2][0]
    matrix[2][3] = 1;  // Karel (4,3) → array[2][3]
    matrix[3][1] = 1;  // Karel (2,2) → array[3][1]
    matrix[4][2] = 1;  // Karel (3,1) → array[4][2]
}
```

### 2. Coordinate Conversion Functions
```c
void karel_to_array_coords(int karel_x, int karel_y, int* array_row, int* array_col) {
    *array_row = MATRIX_SIZE - karel_y;  // Convert y-coordinate
    *array_col = karel_x - 1;            // Convert x-coordinate
}

int check_matrix_at_karel_position(int matrix[MATRIX_SIZE][MATRIX_SIZE]) {
    int karel_x = karel_get_x();
    int karel_y = karel_get_y();
    
    int array_row, array_col;
    karel_to_array_coords(karel_x, karel_y, &array_row, &array_col);
    
    return matrix[array_row][array_col];
}
```

### 3. Matrix Traversal Using 2D Array
```c
void traverse_matrix_with_array(int matrix[MATRIX_SIZE][MATRIX_SIZE]) {
    total_beepers = 0;
    
    // Nested loops to traverse 2D array systematically
    for (int row = 0; row < MATRIX_SIZE; row++) {
        for (int col = 0; col < MATRIX_SIZE; col++) {
            // Convert array indices to Karel coordinates
            int karel_x = col + 1;              // col=0 → x=1
            int karel_y = MATRIX_SIZE - row;    // row=0 → y=5
            
            // Move Karel to this position
            move_to_position(karel_x, karel_y);
            
            // Check matrix value at this position
            int matrix_value = matrix[row][col];
            
            if (matrix_value == 1) {  // Matrix indicates beeper here
                if (beepers_present()) {
                    karel_pick_beeper();
                    total_beepers++;
                    printf("Beeper collected at (%d,%d) - Total: %d\n", 
                           karel_x, karel_y, total_beepers);
                    matrix[row][col] = 2; // Mark as visited
                }
            } else {
                matrix[row][col] = 2; // Mark as visited (no beeper)
            }
        }
    }
}
```

### 4. Matrix Visualization
```c
void print_matrix(int matrix[MATRIX_SIZE][MATRIX_SIZE]) {
    printf("\n=== World Matrix (2D Array) ===\n");
    printf("Array indices:  ");
    for (int col = 0; col < MATRIX_SIZE; col++) {
        printf("[%d] ", col);
    }
    printf("\n");
    
    for (int row = 0; row < MATRIX_SIZE; row++) {
        printf("Row [%d]: ", row);
        for (int col = 0; col < MATRIX_SIZE; col++) {
            printf(" %d  ", matrix[row][col]);
        }
        
        int karel_y = MATRIX_SIZE - row;
        printf("  ← Karel y=%d\n", karel_y);
    }
    
    printf("\nLegend: 0=Empty, 1=Beeper, 2=Visited\n\n");
}
```

## Complete Solution

```c
#include "karel.h"
#define REFRESH_RATE 0.5
#define MATRIX_SIZE 5

const char* DIRECTION_NAMES[] = {"East", "North", "West", "South"};
void studentCode();

static int world_matrix[MATRIX_SIZE][MATRIX_SIZE];
static int total_beepers = 0;

void setup() {
    karel_init();
    karel_set_bag_beepers(0);
    
    // Place beepers at specific positions
    karel_add_beeper(2, 5);  // Top row
    karel_add_beeper(5, 5);
    karel_add_beeper(3, 4);  // Second row
    karel_add_beeper(1, 3);  // Third row
    karel_add_beeper(4, 3);
    karel_add_beeper(2, 2);  // Fourth row
    karel_add_beeper(3, 1);  // Bottom row
    
    printf("Exercise 17: 2D Arrays (Matrices)\n");
    printf("Karel will use a 2D array to map and navigate the world\n");
}

void initialize_matrix(int matrix[MATRIX_SIZE][MATRIX_SIZE]) {
    // Initialize all cells to 0
    for (int row = 0; row < MATRIX_SIZE; row++) {
        for (int col = 0; col < MATRIX_SIZE; col++) {
            matrix[row][col] = 0;
        }
    }
    
    // Set beeper locations using coordinate conversion
    matrix[0][1] = 1;  // (2,5)
    matrix[0][4] = 1;  // (5,5)
    matrix[1][2] = 1;  // (3,4)
    matrix[2][0] = 1;  // (1,3)
    matrix[2][3] = 1;  // (4,3)
    matrix[3][1] = 1;  // (2,2)
    matrix[4][2] = 1;  // (3,1)
}

void move_to_position(int target_x, int target_y) {
    // Move horizontally first
    while (karel_get_x() != target_x) {
        if (karel_get_x() < target_x) {
            while (karel_get_direction() != 0) karel_turn_left(); // Face East
            if (front_is_clear()) karel_move();
        } else {
            while (karel_get_direction() != 2) karel_turn_left(); // Face West
            if (front_is_clear()) karel_move();
        }
    }
    
    // Then move vertically
    while (karel_get_y() != target_y) {
        if (karel_get_y() < target_y) {
            while (karel_get_direction() != 1) karel_turn_left(); // Face North
            if (front_is_clear()) karel_move();
        } else {
            while (karel_get_direction() != 3) karel_turn_left(); // Face South
            if (front_is_clear()) karel_move();
        }
    }
}

void traverse_matrix_with_array(int matrix[MATRIX_SIZE][MATRIX_SIZE]) {
    total_beepers = 0;
    
    for (int row = 0; row < MATRIX_SIZE; row++) {
        for (int col = 0; col < MATRIX_SIZE; col++) {
            int karel_x = col + 1;
            int karel_y = MATRIX_SIZE - row;
            
            move_to_position(karel_x, karel_y);
            
            if (matrix[row][col] == 1) {
                if (beepers_present()) {
                    karel_pick_beeper();
                    total_beepers++;
                    printf("Beeper collected at (%d,%d) - Total: %d\n", 
                           karel_x, karel_y, total_beepers);
                }
            }
            matrix[row][col] = 2; // Mark as visited
        }
    }
}

void studentCode() {
    static bool traversal_complete = false;
    
    if (!traversal_complete) {
        printf("Starting 2D array traversal...\n");
        
        initialize_matrix(world_matrix);
        traverse_matrix_with_array(world_matrix);
        
        printf("Matrix traversal complete! Total beepers: %d\n", total_beepers);
        traversal_complete = true;
    }
}

static double lastMoveTime = 0;

void loop(double timeSec, double elapsedSec) {
    if(timeSec - lastMoveTime > REFRESH_RATE) {
        bool ready = drawWorld();
        if (ready)
            studentCode();
        lastMoveTime = timeSec;
    }
}
```

## Key Learning Points

1. **2D Array Declaration**: `int matrix[ROWS][COLS]` creates a 2D array
2. **Coordinate Conversion**: Essential for mapping between Karel coordinates and array indices
3. **Nested Loop Traversal**: Systematic way to visit every matrix element
4. **Matrix Manipulation**: Reading and writing values at specific indices
5. **State Representation**: Using matrix values to encode different world states

## Expected Output

```
Starting 2D array traversal...
Beeper collected at (2,5) - Total: 1
Beeper collected at (5,5) - Total: 2
Beeper collected at (3,4) - Total: 3
Beeper collected at (1,3) - Total: 4
Beeper collected at (4,3) - Total: 5
Beeper collected at (2,2) - Total: 6
Beeper collected at (3,1) - Total: 7
Matrix traversal complete! Total beepers: 7
```

This solution demonstrates the fundamental concepts of 2D arrays in C programming, including declaration, initialization, coordinate mapping, and systematic traversal using nested loops.