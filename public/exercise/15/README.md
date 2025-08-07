# Bidimensional Arrays with Karel

Learn to work with 2D arrays (matrices) in C programming. Karel will use a 2D array to map the world, store beeper locations, and navigate systematically through the matrix.

Bidimensional arrays (matrices) are fundamental data structures for representing 2D data like game boards, images, maps, and grids. This exercise teaches you how to declare, initialize, and manipulate 2D arrays in C.

## Your Task
Karel must:
1. **Create a 2D array** to represent a 5x5 world map
2. **Initialize the matrix** with world state information
3. **Use the matrix** to guide navigation and store beeper locations
4. **Update the matrix** as Karel collects beepers
5. **Print the matrix** to visualize the world state

Look at the world layout below:
![World Map](/exercise/17/world.png)

Define a bidimensional matrix that represents Karel's world:

### Matrix Representation
```c
int world_matrix[5][5] = {
    {0, 1, 0, 0, 1},  // Row 0 (y=5): . B . . B
    {0, 0, 1, 0, 0},  // Row 1 (y=4): . . B . .
    {1, 0, 0, 1, 0},  // Row 2 (y=3): B . . B .
    {0, 1, 0, 0, 0},  // Row 3 (y=2): . B . . .
    {0, 0, 1, 0, 0}   // Row 4 (y=1): . . B . .
};

// Where: 0 = empty, 1 = beeper, 2 = visited, 3 = karel
```

### Array Index Mapping
```
Karel coordinates vs Array indices:
Karel (1,5) ↔ array[0][0]  Karel (5,5) ↔ array[0][4]
Karel (1,4) ↔ array[1][0]  Karel (5,4) ↔ array[1][4]
Karel (1,3) ↔ array[2][0]  Karel (5,3) ↔ array[2][4]
Karel (1,2) ↔ array[3][0]  Karel (5,2) ↔ array[3][4]
Karel (1,1) ↔ array[4][0]  Karel (5,1) ↔ array[4][4]

Formula: array[5-y][x-1] = Karel position (x,y)
```
   1 2 3 4 5
5: . B . . B
4: . . B . .
3: B . . B .
2: . B . . .
1: S . B . .  ← Start position (1,1)

S = Start, B = Beeper, . = Empty
```

## Programming Concepts You'll Learn

### 1. 2D Array Declaration and Initialization
```c
#define MATRIX_SIZE 5

// Declare and initialize a 2D array
int world_matrix[MATRIX_SIZE][MATRIX_SIZE] = {
    {0, 1, 0, 0, 1},
    {0, 0, 1, 0, 0},
    {1, 0, 0, 1, 0},
    {0, 1, 0, 0, 0},
    {0, 0, 1, 0, 0}
};
```

### 2. Array Index Conversion
```c
// Convert Karel coordinates to array indices
int array_row = MATRIX_SIZE - karel_y;    // y=1 → row=4, y=5 → row=0
int array_col = karel_x - 1;              // x=1 → col=0, x=5 → col=4

// Access matrix element
int value = world_matrix[array_row][array_col];
```

### 3. Matrix Manipulation
```c
// Set value in matrix
world_matrix[row][col] = new_value;

// Get value from matrix
int current_value = world_matrix[row][col];

// Update matrix based on Karel's actions
if (beepers_present()) {
    world_matrix[array_row][array_col] = 2; // Mark as visited
}
```

### 4. Matrix Traversal with Arrays
```c
for (int row = 0; row < MATRIX_SIZE; row++) {
    for (int col = 0; col < MATRIX_SIZE; col++) {
        int karel_x = col + 1;
        int karel_y = MATRIX_SIZE - row;
        printf("Matrix[%d][%d] = %d corresponds to Karel position (%d,%d)\n",
               row, col, world_matrix[row][col], karel_x, karel_y);
    }
}
```

## Functions You'll Need to Implement

### 1. initialize_matrix()
```c
void initialize_matrix(int matrix[MATRIX_SIZE][MATRIX_SIZE]) {
    // Set up the matrix with beeper locations
    // Initialize all cells and place beepers at specific positions
}
```

### 2. print_matrix()
```c
void print_matrix(int matrix[MATRIX_SIZE][MATRIX_SIZE]) {
    // Print the matrix in a readable format
    // Show both array indices and Karel coordinates
}
```

### 3. karel_to_array_coords()
```c
void karel_to_array_coords(int karel_x, int karel_y, int* array_row, int* array_col) {
    *array_row = MATRIX_SIZE - karel_y;
    *array_col = karel_x - 1;
}
```

### 4. check_matrix_at_position()
```c
int check_matrix_at_position(int matrix[MATRIX_SIZE][MATRIX_SIZE], int karel_x, int karel_y) {
    int row, col;
    karel_to_array_coords(karel_x, karel_y, &row, &col);
    return matrix[row][col];
}
```

### 5. traverse_matrix()
```c
void traverse_matrix(int matrix[MATRIX_SIZE][MATRIX_SIZE]) {
    // Use nested loops to visit every position
    // Update matrix as beepers are collected
}
```c
void move_to_position(int target_x, int target_y) {
    // Move Karel from current position to target position
    // Handle both horizontal and vertical movement
}
```

### 2. traverse_row()
```c
void traverse_row(int row_number) {
    // Move to start of row and traverse left to right
    // Check each position for beepers
}
```

### 3. check_and_count_beeper()
```c
void check_and_count_beeper() {
    // Check current position for beeper
    // If found, increment counter and optionally pick it up
}
```

### 4. matrix_traversal()
```c
void matrix_traversal() {
    // Main function implementing nested loop logic
    // Traverse entire 5x5 matrix systematically
}
```

## Setup Information
- Karel starts at position (1,1) facing East
- Karel has infinite beepers in bag (not needed for this exercise)
- Beepers are randomly placed throughout the 5x5 grid
- Karel must visit every cell exactly once

## Success Criteria
- Karel visits all 25 positions in the 5x5 matrix
- Karel follows the correct traversal pattern (left to right, row by row)
- Karel accurately counts all beepers in the matrix
- The solution demonstrates proper nested loop implementation

## Algorithm Steps

### Step 1: Initialize
```c
void initialize_traversal() {
    printf("Starting matrix traversal at (1,1)\n");
    total_beepers = 0;
    current_row = 1;
}
```

### Step 2: Outer Loop (Rows)
```c
for (int row = 1; row <= 5; row++) {
    printf("Starting row %d\n", row);
    traverse_row(row);
}
```

### Step 3: Inner Loop (Columns)
```c
void traverse_row(int row) {
    move_to_position(1, row); // Start of row
    for (int col = 1; col <= 5; col++) {
        move_to_position(col, row);
        check_and_count_beeper();
    }
}
```

### Step 4: Beeper Detection
```c
void check_and_count_beeper() {
    if (beepers_present()) {
        total_beepers++;
        printf("Beeper found at (%d, %d) - Total: %d\n", 
               karel_get_x(), karel_get_y(), total_beepers);
    }
}
```

## Code Structure Template
```c
#define MATRIX_SIZE 5

static int total_beepers = 0;

void move_to_position(int target_x, int target_y) {
    // Implement movement logic
}

void check_and_count_beeper() {
    // Check current cell and count beepers
}

void traverse_row(int row_number) {
    // Traverse one complete row
}

void matrix_traversal() {
    // Main nested loop implementation
    for (int row = 1; row <= MATRIX_SIZE; row++) {
        traverse_row(row);
    }
}

void studentCode() {
    static bool traversal_complete = false;
    
    if (!traversal_complete) {
        matrix_traversal();
        printf("Matrix traversal complete! Total beepers found: %d\n", total_beepers);
        traversal_complete = true;
    }
}
```

## Learning Objectives
- **Nested Loops**: Understand how to use loops within loops for 2D traversal
- **Matrix Navigation**: Learn systematic approaches to visiting every cell
- **Coordinate Systems**: Practice working with x,y coordinate systems
- **Counter Variables**: Implement proper counting and state tracking
- **Algorithm Design**: Break down complex problems into simpler steps

## Why This Matters
Matrix traversal is fundamental in:
- **Image Processing**: Processing every pixel in an image
- **Game Development**: Updating game board states, pathfinding
- **Data Analysis**: Processing spreadsheet data, scientific computations  
- **Computer Graphics**: Rendering 2D textures and patterns
- **Database Operations**: Table scanning and data processing

This exercise teaches you the foundation for working with any 2D data structure and prepares you for more advanced algorithms like flood fill, maze solving, and image analysis.

## Expected Output
```
Starting matrix traversal at (1,1)
Starting row 1
Moving to position (1, 1)
Moving to position (2, 1)
Beeper found at (3, 1) - Total: 1
...
Starting row 2
Beeper found at (2, 2) - Total: 2
...
Matrix traversal complete! Total beepers found: 6
```
