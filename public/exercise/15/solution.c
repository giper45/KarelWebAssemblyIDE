#include "karel.h"
#define REFRESH_RATE 0.01
#define MATRIX_SIZE 5

const char* DIRECTION_NAMES[] = {"East", "North", "West", "South"};
void studentCode();

// Static 2D array to represent the world matrix
static int world_matrix[MATRIX_SIZE][MATRIX_SIZE];
static int total_beepers = 0;

void setup() {
    karel_init();
    karel_set_bag_beepers(0);
    
    // Place beepers in the actual world
    karel_add_beeper(2, 5);  // Top row
    karel_add_beeper(5, 5);
    karel_add_beeper(3, 4);  // Second row
    karel_add_beeper(1, 3);  // Third row
    karel_add_beeper(4, 3);
    karel_add_beeper(2, 2);  // Fourth row
    karel_add_beeper(3, 1);  // Bottom row
    
    printf("Karel uses a 2D array to map and navigate the world\n");
    printf("Beepers at: (2,5), (5,5), (3,4), (1,3), (4,3), (2,2), (3,1)\n");
}
// Initialize the 2D matrix with beeper locations
void initialize_matrix(int matrix[MATRIX_SIZE][MATRIX_SIZE]) {
    printf("Initializing 2D matrix with beeper locations...\n");
    
    // First, initialize all cells to 0 (empty)
    for (int row = 0; row < MATRIX_SIZE; row++) {
        for (int col = 0; col < MATRIX_SIZE; col++) {
            matrix[row][col] = 0;
        }
    }
    
    // Set beeper locations to 1
    // Convert Karel coordinates to array indices: array[MATRIX_SIZE-y][x-1]
    matrix[0][1] = 1;  // Karel (2,5) → array[0][1]
    matrix[0][4] = 1;  // Karel (5,5) → array[0][4]
    matrix[1][2] = 1;  // Karel (3,4) → array[1][2]
    matrix[2][0] = 1;  // Karel (1,3) → array[2][0]
    matrix[2][3] = 1;  // Karel (4,3) → array[2][3]
    matrix[3][1] = 1;  // Karel (2,2) → array[3][1]
    matrix[4][2] = 1;  // Karel (3,1) → array[4][2]
    
    printf("Matrix initialized with 7 beepers\n");
}

// Print the matrix in a readable format
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
        
        // Show corresponding Karel coordinates
        int karel_y = MATRIX_SIZE - row;
        printf("  ← Karel y=%d\n", karel_y);
    }
    
    printf("\nLegend: 0=Empty, 1=Beeper, 2=Visited, 3=Karel\n");
    printf("Karel coordinates: x=1-5, y=1-5\n\n");
}

// Convert Karel coordinates to array indices
void karel_to_array_coords(int karel_x, int karel_y, int* array_row, int* array_col) {
    *array_row = MATRIX_SIZE - karel_y;  // y=1 → row=4, y=5 → row=0
    *array_col = karel_x - 1;            // x=1 → col=0, x=5 → col=4
}

// Check what value is in the matrix at Karel's current position
int check_matrix_at_karel_position(int matrix[MATRIX_SIZE][MATRIX_SIZE]) {
    int karel_x = karel_get_x();
    int karel_y = karel_get_y();
    
    int array_row, array_col;
    karel_to_array_coords(karel_x, karel_y, &array_row, &array_col);
    
    return matrix[array_row][array_col];
}

// Update matrix at Karel's position
void update_matrix_at_karel_position(int matrix[MATRIX_SIZE][MATRIX_SIZE], int new_value) {
    int karel_x = karel_get_x();
    int karel_y = karel_get_y();
    
    int array_row, array_col;
    karel_to_array_coords(karel_x, karel_y, &array_row, &array_col);
    
    matrix[array_row][array_col] = new_value;
    printf("Updated matrix[%d][%d] = %d at Karel position (%d,%d)\n", 
           array_row, array_col, new_value, karel_x, karel_y);
}

// Helper function to move Karel to specific position
void move_to_position(int target_x, int target_y) {
    printf("Moving Karel to position (%d,%d)\n", target_x, target_y);
    
    // Move horizontally first
    while (karel_get_x() != target_x) {
        if (karel_get_x() < target_x) {
            // Face east and move
            while (karel_get_direction() != 0) karel_turn_left();
            if (front_is_clear()) karel_move();
        } else {
            // Face west and move
            while (karel_get_direction() != 2) karel_turn_left();
            if (front_is_clear()) karel_move();
        }
    }
    
    // Then move vertically
    while (karel_get_y() != target_y) {
        if (karel_get_y() < target_y) {
            // Face north and move
            while (karel_get_direction() != 1) karel_turn_left();
            if (front_is_clear()) karel_move();
        } else {
            // Face south and move
            while (karel_get_direction() != 3) karel_turn_left();
            if (front_is_clear()) karel_move();
        }
    }
}

// Main function to traverse matrix using 2D array
void traverse_matrix_with_array(int matrix[MATRIX_SIZE][MATRIX_SIZE]) {
    printf("\n*** Starting matrix traversal using 2D array ***\n");
    total_beepers = 0;
    
    // Use nested loops to traverse the matrix
    // Outer loop: iterate through array rows (0 to MATRIX_SIZE-1)
    // Inner loop: iterate through array columns (0 to MATRIX_SIZE-1)
    
    for (int row = 0; row < MATRIX_SIZE; row++) {
        printf("\n=== Processing matrix row %d ===\n", row);
        
        for (int col = 0; col < MATRIX_SIZE; col++) {
            // Convert array indices back to Karel coordinates
            int karel_x = col + 1;              // col=0 → x=1, col=4 → x=5
            int karel_y = MATRIX_SIZE - row;    // row=0 → y=5, row=4 → y=1
            
            printf("Processing matrix[%d][%d] = %d → Karel position (%d,%d)\n", 
                   row, col, matrix[row][col], karel_x, karel_y);
            
            // Move Karel to this position
            move_to_position(karel_x, karel_y);
            
            // Update matrix to show Karel's current position
            int old_value = matrix[row][col];
            update_matrix_at_karel_position(matrix, 3); // 3 = Karel position
            
            // Check if matrix indicates beeper should be here
            if (old_value == 1) {
                printf("Matrix indicates beeper at (%d,%d) - checking...\n", karel_x, karel_y);
                
                if (beepers_present()) {
                    karel_pick_beeper();
                    total_beepers++;
                    printf("*** BEEPER COLLECTED! Total: %d ***\n", total_beepers);
                    
                    // Mark as visited with beeper collected
                    matrix[row][col] = 2; // 2 = visited
                } else {
                    printf("Warning: Matrix said beeper here but none found!\n");
                }
            } else {
                // No beeper expected, mark as visited
                matrix[row][col] = 2; // 2 = visited
            }
            
            printf("Matrix[%d][%d] now = %d\n", row, col, matrix[row][col]);
        }
    }
    
    printf("\n*** Matrix traversal complete! ***\n");
    printf("Total beepers found using 2D array: %d\n", total_beepers);
    printf("All 25 matrix cells have been processed.\n");
}

// Print matrix with both array and Karel coordinate systems
void print_coordinate_mapping() {
    printf("\n=== Coordinate System Mapping ===\n");
    printf("Array Index → Karel Coordinates:\n");
    
    for (int row = 0; row < MATRIX_SIZE; row++) {
        for (int col = 0; col < MATRIX_SIZE; col++) {
            int karel_x = col + 1;
            int karel_y = MATRIX_SIZE - row;
            printf("matrix[%d][%d] ↔ Karel(%d,%d)  ", row, col, karel_x, karel_y);
        }
        printf("\n");
    }
    printf("\n");
}

void studentCode() {
    static bool traversal_complete = false;
    
    if (!traversal_complete) {
        printf("Karel starting position: (%d, %d) - Direction: %s\n", 
               karel_get_x(), karel_get_y(), DIRECTION_NAMES[karel_get_direction()]);
        
        // Show coordinate mapping
        print_coordinate_mapping();
        
        // Initialize the 2D matrix
        initialize_matrix(world_matrix);
        
        // Print the initial matrix
        printf("Initial matrix state:");
        print_matrix(world_matrix);
        
        // Traverse the world using the matrix
        traverse_matrix_with_array(world_matrix);
        
        // Print the final matrix state
        printf("Final matrix state:");
        print_matrix(world_matrix);
        
        printf("\nExercise complete! Karel successfully used 2D arrays to:\n");
        printf("- Map the world state\n");
        printf("- Guide navigation\n");
        printf("- Track visited positions\n");
        printf("- Count collected beepers: %d\n", total_beepers);
        
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

// Helper function to turn to a specific direction
void face_direction(int target_direction) {
    while (karel_get_direction() != target_direction) {
        karel_turn_left();
    }
}


// Check current position for beeper and count it
void check_and_count_beeper() {
    printf("Checking position (%d, %d) - ", karel_get_x(), karel_get_y());
    
    if (beepers_present()) {
        total_beepers++;
        printf("BEEPER FOUND! Total count: %d\n", total_beepers);
        // Optionally pick up the beeper
        // karel_pick_beeper();
    } else {
        printf("No beeper\n");
    }
}

// Traverse one complete row from left to right
void traverse_row(int row_number) {
    printf("\n=== Starting traversal of row %d ===\n", row_number);
    
    // Move to start of row (column 1)
    move_to_position(1, row_number);
    
    // Traverse each column in the row
    for (int col = 1; col <= MATRIX_SIZE; col++) {
        printf("Visiting cell (%d, %d) in row %d\n", col, row_number, row_number);
        
        // Move to current column
        move_to_position(col, row_number);
        
        // Check for beeper at this position
        check_and_count_beeper();
    }
    
    printf("=== Completed row %d ===\n\n", row_number);
}

// Main matrix traversal function implementing nested loops
void matrix_traversal() {
    printf("\n*** Starting matrix traversal ***\n");
    printf("Traversing 5x5 matrix systematically...\n");
    total_beepers = 0;
    
    // Nested loop structure:
    // Outer loop: iterate through rows (1 to 5)
    // Inner loop: iterate through columns (1 to 5) - implemented in traverse_row
    for (int row = 1; row <= MATRIX_SIZE; row++) {
        traverse_row(row);
    }
    
    printf("*** Matrix traversal complete! ***\n");
    printf("Total beepers found in 5x5 matrix: %d\n", total_beepers);
    printf("All 25 cells have been visited.\n");
}

// Print matrix visualization
void print_matrix_state() {
    printf("\nMatrix State (5x5):\n");
    printf("   ");
    for (int col = 1; col <= 5; col++) {
        printf("%d ", col);
    }
    printf("\n");
    
    for (int row = 5; row >= 1; row--) {
        printf("%d: ", row);
        for (int col = 1; col <= 5; col++) {
            if (karel_get_x() == col && karel_get_y() == row) {
                printf("K "); // Karel's current position
            } else {
                // Check if there's a beeper at this position
                bool has_beeper = (col == 3 && row == 1) || (col == 2 && row == 2) ||
                                (col == 1 && row == 3) || (col == 4 && row == 3) ||
                                (col == 3 && row == 4) || (col == 2 && row == 5) ||
                                (col == 5 && row == 5);
                printf("%s ", has_beeper ? "B" : ".");
            }
        }
        printf("\n");
    }
    printf("K = Karel, B = Beeper, . = Empty\n\n");
}
