#include "karel.h"

const char* DIRECTION_NAMES[] = {"Est", "Nord", "Ovest", "Sud"};

// Global variables to track search algorithm
int search_steps = 0;
int beepers_found = 0;
int current_row = 1;
int search_complete = 0;

// TODO: Implement linear search functions

// TODO: Function to move to next position in search pattern
// void move_to_next_search_position()

// TODO: Function to search current row from left to right
// int search_current_row()

// TODO: Function to move to start of next row
// void move_to_next_row()

// TODO: Function to perform complete linear search
// int linear_search_all_beepers()

void setup() {
    karel_init();
    
    // Place beepers in various positions for search testing
    karel_add_beeper(3, 2);
    karel_add_beeper(7, 4);
    karel_add_beeper(2, 6);
    karel_add_beeper(9, 3);
    karel_add_beeper(5, 7);
    karel_add_beeper(1, 5);
    
    printf("Karel Linear Search Algorithm\n");
    printf("=============================\n");
    printf("Searching for beepers in %dx%d world...\n", WORLD_WIDTH, WORLD_HEIGHT);
}

void draw() {
    canvas_setFillStyleZ("white");
    canvas_fillRect(0, 0, 800, 600);
    drawWalls();
    drawGrid();
    drawBeepers();
    drawKarel();
    drawInfo();
    
    // Display search statistics
    printf("Search Steps: %d | Beepers Found: %d | Row: %d\n", 
           search_steps, beepers_found, current_row);
}

void loop(double timeSec, double elapsedSec) {
    draw();
    
    static double lastMoveTime = 0;
    
    if (timeSec - lastMoveTime > 0.8 && !search_complete) {
        
        // TODO: Implement the main search loop
        // 1. Check current position for beeper
        // 2. If beeper found, pick it up and increment counter
        // 3. Move to next search position
        // 4. Keep track of search steps
        // 5. When row is complete, move to next row
        // 6. Stop when entire world is searched
        
        // Increment search steps counter
        search_steps++;
        
        // Check if current position has a beeper
        if (beepers_present()) {
            karel_pick_beeper();
            beepers_found++;
            printf("Beeper found at position (%d, %d)!\n", karel.x, karel.y);
        }
        
        // TODO: Implement movement logic for systematic search
        // Move east across current row, then move to next row
        
        lastMoveTime = timeSec;
    }
    
    // Display completion message
    if (search_complete) {
        printf("Search Complete! Found %d beepers in %d steps\n", 
               beepers_found, search_steps);
        printf("Search efficiency: %.2f steps per beeper\n", 
               beepers_found > 0 ? (float)search_steps / beepers_found : 0);
    }
}

// TODO: Implement your search functions here
