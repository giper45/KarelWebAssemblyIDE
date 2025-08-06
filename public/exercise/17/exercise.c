#include "karel.h"
#define REFRESH_RATE 0.5
#define MATRIX_SIZE 5

const char* DIRECTION_NAMES[] = {"East", "North", "West", "South"};
void studentCode();

// Static 2D array to represent the world matrix
static int world_matrix[MATRIX_SIZE][MATRIX_SIZE];
static int total_beepers = 0;



static double lastMoveTime = 0;
static int done = 0;
void loop(double timeSec, double elapsedSec)
{
    if (timeSec - lastMoveTime > REFRESH_RATE)
    { // Check frequently for smooth timing
        bool ready = drawWorld();
        if (ready && !done)
            studentCode();
        done = 1;
        lastMoveTime = timeSec;
    }
}


// TODO: Initialize the 2D matrix with beeper locations
void initialize_matrix(int matrix[MATRIX_SIZE][MATRIX_SIZE]) {
    karel_setup_printf("Initializing 2D matrix...\n");
    
    // TODO: First, initialize all cells to 0 (empty)
    for (int row = 0; row < MATRIX_SIZE; row++) {
        for (int col = 0; col < MATRIX_SIZE; col++) {
            // TODO: Set all cells to 0
        }
    }
    
    // TODO: Set beeper locations to 1
    // Beeper positions: (2,5), (5,5), (3,4), (1,3), (4,3), (2,2), (3,1)
    // Convert Karel coordinates to array indices:
    // Karel (x,y) → array[MATRIX_SIZE-y][x-1]
    
    // Example: Karel (2,5) → array[5-5][2-1] = array[0][1]
    // TODO: Complete the matrix initialization
}

// TODO: Print the matrix in a readable format
void print_matrix(int matrix[MATRIX_SIZE][MATRIX_SIZE]) {
    karel_setup_printf("\n=== World Matrix (2D Array) ===\n");
    karel_setup_printf("Array indices:  ");
    for (int col = 0; col < MATRIX_SIZE; col++) {
        karel_setup_printf("[%d] ", col);
    }
    karel_setup_printf("\n");
    
    for (int row = 0; row < MATRIX_SIZE; row++) {
        karel_setup_printf("Row [%d]: ", row);
        for (int col = 0; col < MATRIX_SIZE; col++) {
            karel_setup_printf(" %d  ", matrix[row][col]);
        }
        
        // Show corresponding Karel coordinates
        int karel_y = MATRIX_SIZE - row;
        karel_setup_printf("Karel y=%d\n", karel_y);
    }
    
    karel_setup_printf("\nLegend: 0=Empty, 1=Beeper, 2=Visited, 3=Karel\n");
    karel_setup_printf("Karel coordinates: x=1-5, y=1-5\n\n");
}

// TODO: Convert Karel coordinates to array indices
void karel_to_array_coords(int karel_x, int karel_y, int* array_row, int* array_col) {
    // TODO: Implement coordinate conversion
    // Karel (1,1) should map to array[4][0]
    // Karel (5,5) should map to array[0][4]
    
    // Formula: array_row = MATRIX_SIZE - karel_y
    //          array_col = karel_x - 1
}

// TODO: Check what value is in the matrix at Karel's current position
int check_matrix_at_karel_position(int matrix[MATRIX_SIZE][MATRIX_SIZE]) {
    int karel_x = karel_get_x();
    int karel_y = karel_get_y();
    
    int array_row, array_col;
    karel_to_array_coords(karel_x, karel_y, &array_row, &array_col);
    
    // TODO: Return the value at matrix[array_row][array_col]
    return 0; // Placeholder
}

// TODO: Update matrix at Karel's position
void update_matrix_at_karel_position(int matrix[MATRIX_SIZE][MATRIX_SIZE], int new_value) {
    int karel_x = karel_get_x();
    int karel_y = karel_get_y();
    
    int array_row, array_col;
    karel_to_array_coords(karel_x, karel_y, &array_row, &array_col);
    
    // TODO: Set matrix[array_row][array_col] = new_value
    karel_setup_printf("Updated matrix[%d][%d] = %d at Karel position (%d,%d)\n", 
           array_row, array_col, new_value, karel_x, karel_y);
}

// Helper function to move Karel to specific position
void move_to_position(int target_x, int target_y) {
    // Simple movement implementation
    while (karel_get_x() != target_x || karel_get_y() != target_y) {
        if (karel_get_x() < target_x && front_is_clear()) {
            // Face east and move
            while (karel_get_direction() != 0) karel_turn_left();
            karel_move();
        } else if (karel_get_x() > target_x) {
            // Face west and move
            while (karel_get_direction() != 2) karel_turn_left();
            if (front_is_clear()) karel_move();
        } else if (karel_get_y() < target_y) {
            // Face north and move
            while (karel_get_direction() != 1) karel_turn_left();
            if (front_is_clear()) karel_move();
        } else if (karel_get_y() > target_y) {
            // Face south and move
            while (karel_get_direction() != 3) karel_turn_left();
            if (front_is_clear()) karel_move();
        }
    }
}

// TODO: Main function to traverse matrix using 2D array
void traverse_matrix_with_array(int matrix[MATRIX_SIZE][MATRIX_SIZE]) {
    karel_setup_printf("Starting matrix traversal using 2D array...\n");
    total_beepers = 0;
    
    // TODO: Use nested loops to traverse the matrix
    // Outer loop: iterate through array rows (0 to MATRIX_SIZE-1)
    // Inner loop: iterate through array columns (0 to MATRIX_SIZE-1)
    
    for (int row = 0; row < MATRIX_SIZE; row++) {
        for (int col = 0; col < MATRIX_SIZE; col++) {
            // TODO: Convert array indices back to Karel coordinates
            int karel_x = col + 1;
            int karel_y = MATRIX_SIZE - row;
            
            karel_setup_printf("Processing matrix[%d][%d] -> Karel position (%d,%d)\n", 
                   row, col, karel_x, karel_y);
            
            // TODO: Move Karel to this position
            // TODO: Check if matrix indicates beeper should be here
            // TODO: If beeper found, update matrix and increment counter
            // TODO: Mark position as visited in matrix
        }
    }
    
    karel_setup_printf("Matrix traversal complete! Total beepers found: %d\n", total_beepers);
}

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
    
    karel_setup_printf("Karel must use a 2D array to map and navigate the world\n");
    karel_setup_printf("Karel starting position: (%d, %d) - Direction: %s\n", 
               karel_get_x(), karel_get_y(), DIRECTION_NAMES[karel_get_direction()]);
        
    // TODO: Initialize the 2D matrix
    initialize_matrix(world_matrix);
        
    // TODO: Print the initial matrix
    print_matrix(world_matrix);

}

void studentCode() {
    static bool traversal_complete = false;
    
    if (!traversal_complete) {
        
        // TODO: Traverse the world using the matrix
        traverse_matrix_with_array(world_matrix);
        
        // TODO: Print the final matrix state
        print_matrix(world_matrix);
        
        traversal_complete = true;
    }
}
