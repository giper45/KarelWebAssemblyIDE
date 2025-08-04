#include "karel.h"

// TODO: Define world configuration constants using #define
// #define MAX_WORLD_WIDTH 15
// #define MAX_WORLD_HEIGHT 10
// #define DEFAULT_MOVE_DELAY 500
// #define MAX_BEEPER_CAPACITY 50

// TODO: Define behavior constants
// #define TURN_RIGHT_STEPS 3
// #define FULL_ROTATION_STEPS 4

// TODO: Create debug configuration
// #define DEBUG_MODE 1
// #define SHOW_COORDINATES 1
// #define VERBOSE_OUTPUT 0

// TODO: Define macros for common operations
// #define KAREL_TURN_RIGHT() for(int i=0; i<3; i++) karel_turn_left()
// #define KAREL_TURN_AROUND() for(int i=0; i<2; i++) karel_turn_left()

// TODO: Conditional compilation example
// #ifdef DEBUG_MODE
//   #define DEBUG_PRINT(msg) printf("DEBUG: %s\n", msg)
// #else
//   #define DEBUG_PRINT(msg)
// #endif

const char* DIRECTION_NAMES[] = {"Est", "Nord", "Ovest", "Sud"};

// TODO: Create const variables for runtime configuration
// const int movement_delay = DEFAULT_MOVE_DELAY;
// const int max_beepers = MAX_BEEPER_CAPACITY;

void setup() {
    karel_init();
    
    printf("Karel Constants & Preprocessor Demo\n");
    printf("===================================\n");
    
    // TODO: Display configuration using constants
    // printf("World Configuration:\n");
    // printf("- Max Width: %d\n", MAX_WORLD_WIDTH);
    // printf("- Max Height: %d\n", MAX_WORLD_HEIGHT);
    // printf("- Move Delay: %d ms\n", DEFAULT_MOVE_DELAY);
    // printf("- Beeper Capacity: %d\n", MAX_BEEPER_CAPACITY);
    
    // TODO: Show conditional compilation results
    // #ifdef DEBUG_MODE
    //     printf("Debug mode is ENABLED\n");
    // #else
    //     printf("Debug mode is DISABLED\n");
    // #endif
    
    // Add some beepers for testing
    karel_add_beeper(3, 2);
    karel_add_beeper(5, 4);
}

void draw() {
    canvas_setFillStyleZ("white");
    canvas_fillRect(0, 0, 800, 600);
    drawWalls();
    drawGrid();
    drawBeepers();
    drawKarel();
    drawInfo();
    
    // TODO: Display current configuration status
    // printf("Current Settings - Delay: %d, Capacity: %d\n", 
    //        movement_delay, max_beepers);
}

void loop(double timeSec, double elapsedSec) {
    draw();
    
    static double lastActionTime = 0;
    static int action_phase = 0;
    
    // TODO: Use constants for timing control
    if (timeSec - lastActionTime > 1.5) {  // Should use a constant here
        
        switch(action_phase % 6) {
            case 0:
                // TODO: Use macro for turning right
                printf("Demonstrating turn right macro...\n");
                // KAREL_TURN_RIGHT();
                break;
                
            case 1:
                printf("Moving forward...\n");
                if (front_is_clear()) {
                    karel_move();
                }
                break;
                
            case 2:
                // TODO: Use debug macro
                // DEBUG_PRINT("Checking for beepers");
                if (beepers_present()) {
                    karel_pick_beeper();
                    printf("Beeper collected!\n");
                }
                break;
                
            case 3:
                // TODO: Use turn around macro
                printf("Demonstrating turn around macro...\n");
                // KAREL_TURN_AROUND();
                break;
                
            case 4:
                printf("Testing conditional compilation...\n");
                // TODO: Show different behavior based on compile-time flags
                break;
                
            case 5:
                printf("Resetting for next cycle...\n");
                break;
        }
        
        action_phase++;
        lastActionTime = timeSec;
    }
}
