#include "karel.h"

const char* DIRECTION_NAMES[] = {"Est", "Nord", "Ovest", "Sud"};

// Binary search variables
int target_x = 7;           // Target beeper x-coordinate
int search_left = 2;        // Left boundary of search
int search_right = 9;       // Right boundary of search  
int search_steps = 0;       // Count search operations
int found_position = -1;    // Result of search
int search_complete = 0;    // Search status flag

// TODO: Function to perform binary search for beeper at target_x
// int binary_search_beeper(int target, int left, int right) {
//     // Returns x-coordinate if found, -1 if not found
//     // Updates search_steps counter
// }

// TODO: Function to move Karel to specific x-coordinate in current row
// void move_to_x_coordinate(int target_x) {
//     // Navigate Karel to the target x position
//     // Handle both east and west movement
// }

// TODO: Function to check if beeper exists at current position
// int check_beeper_at_position() {
//     // Return 1 if beeper present, 0 if not
//     // Don't pick up the beeper, just check
// }

// TODO: Function to visualize current search bounds
// void show_search_bounds(int left, int right, int mid) {
//     // Display current search space information
// }

void setup() {
    karel_init();
    
    // Create sorted beeper arrangement for binary search
    // Beepers at x-coordinates: 2, 4, 6, 7, 9 (sorted!)
    karel_add_beeper(2, 3);
    karel_add_beeper(4, 3);
    karel_add_beeper(6, 3);
    karel_add_beeper(7, 3);  // This is our target
    karel_add_beeper(9, 3);
    
    printf("Karel Binary Search Algorithm\n");
    printf("=============================\n");
    printf("Searching for beeper at x-coordinate: %d\n", target_x);
    printf("Search range: %d to %d\n", search_left, search_right);
    printf("Sorted beeper positions: 2, 4, 6, 7, 9\n\n");
    
    // Position Karel at the starting position
    // Move to row 3 for the search
    while (karel.y < 3) {
        karel_move();
        karel_turn_left();
        karel_move();
        karel_turn_left();
        karel_turn_left();
        karel_turn_left();
    }
}

void draw() {
    canvas_setFillStyleZ("white");
    canvas_fillRect(0, 0, 800, 600);
    drawWalls();
    drawGrid();
    drawBeepers();
    drawKarel();
    drawInfo();
    
    // Display search progress
    printf("Search Steps: %d | Current Bounds: [%d, %d]\n", 
           search_steps, search_left, search_right);
    
    if (found_position != -1) {
        printf("SUCCESS: Beeper found at x=%d!\n", found_position);
    }
}

void loop(double timeSec, double elapsedSec) {
    draw();
    
    static double lastSearchTime = 0;
    
    if (timeSec - lastSearchTime > 2.0 && !search_complete) {
        
        // TODO: Implement binary search step by step
        if (search_left <= search_right) {
            // Calculate midpoint
            int mid = search_left + (search_right - search_left) / 2;
            
            printf("Searching at midpoint: x=%d\n", mid);
            
            // TODO: Move Karel to midpoint position
            // move_to_x_coordinate(mid);
            
            // TODO: Check if beeper is at current position
            // int beeper_here = check_beeper_at_position();
            
            // Simulate the check for demonstration
            int beeper_here = (mid == target_x) ? 1 : 0;
            search_steps++;
            
            if (beeper_here) {
                // Found the target!
                found_position = mid;
                search_complete = 1;
                printf("TARGET FOUND at x=%d after %d steps!\n", mid, search_steps);
            } else {
                // Need to search half of remaining space
                if (target_x < mid) {
                    // Target is in left half
                    search_right = mid - 1;
                    printf("Target < %d, searching left half [%d, %d]\n", 
                           mid, search_left, search_right);
                } else {
                    // Target is in right half  
                    search_left = mid + 1;
                    printf("Target > %d, searching right half [%d, %d]\n",
                           mid, search_left, search_right);
                }
            }
        } else {
            // Search space exhausted - target not found
            search_complete = 1;
            printf("SEARCH FAILED: Target not found after %d steps\n", search_steps);
        }
        
        lastSearchTime = timeSec;
    }
    
    // Show comparison with linear search
    if (search_complete) {
        printf("\nEfficiency Comparison:\n");
        printf("Binary Search: %d steps\n", search_steps);
        printf("Linear Search would take: up to %d steps\n", 
               search_right - search_left + 1);
        printf("Binary search is %d%% more efficient!\n",
               (int)(((float)(search_right - search_left + 1 - search_steps) / 
                     (search_right - search_left + 1)) * 100));
    }
}

// TODO: Implement the binary search functions here
