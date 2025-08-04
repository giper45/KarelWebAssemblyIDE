#include "karel.h"

const char* DIRECTION_NAMES[] = {"Est", "Nord", "Ovest", "Sud"};

// Global variables for behavior control
int behavior_mode = 0;  // 0=explore, 1=collect, 2=organize, 3=return
int actions_taken = 0;

void setup() {
    karel_init();
    
    // Create a varied world for testing control structures
    karel_add_beeper(3, 2);
    karel_add_beeper(7, 4);
    karel_add_beeper(2, 6);
    karel_add_beeper(9, 3);
    karel_add_beeper(5, 7);
    
    // Add walls to create navigation challenges
    karel_add_horizontal_wall(4, 3, 2);
    karel_add_vertical_wall(6, 2, 3);
    karel_add_horizontal_wall(7, 6, 2);
    
    printf("Karel Control Structures Demo\n");
    printf("=============================\n");
}

void draw() {
    canvas_setFillStyleZ("white");
    canvas_fillRect(0, 0, 800, 600);
    drawWalls();
    drawGrid();
    drawBeepers();
    drawKarel();
    drawInfo();
    
    // Display current behavior mode
    char* mode_names[] = {"Exploring", "Collecting", "Organizing", "Returning"};
    printf("Mode: %s | Actions: %d\n", mode_names[behavior_mode], actions_taken);
}

void loop(double timeSec, double elapsedSec) {
    draw();
    
    static double lastActionTime = 0;
    
    if (timeSec - lastActionTime > 1.0) {
        
        // TODO: Implement switch statement for behavior modes
        switch(behavior_mode) {
            case 0: // Exploration mode
                // TODO: Use if-else to navigate and explore
                // If front is clear, move forward
                // If blocked, turn and try different direction
                // Switch to collect mode when beeper is found
                break;
                
            case 1: // Collection mode
                // TODO: Use while loop to collect all beepers at current location
                // Use if statement to check for beepers
                // Return to exploration when done
                break;
                
            case 2: // Organization mode  
                // TODO: Use for loop to arrange collected beepers
                // Place beepers in organized pattern
                break;
                
            case 3: // Return mode
                // TODO: Use nested loops to return to starting position
                // Navigate back to (1,1) systematically
                break;
        }
        
        // TODO: Add condition to cycle through behavior modes
        actions_taken++;
        
        // TODO: Implement nested control structures
        // Example: if in exploration mode AND actions > 10, switch mode
        
        // TODO: Use for loop for repetitive actions
        // Example: for(int i = 0; i < 3; i++) if(front_is_clear()) karel_move();
        
        // TODO: Use while loop with complex conditions
        // Example: while(front_is_clear() && !beepers_present()) karel_move();
        
        lastActionTime = timeSec;
    }
}
