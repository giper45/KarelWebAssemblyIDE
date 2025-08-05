#include "karel.h"
#define REFRESH_RATE 1.0

const char* DIRECTION_NAMES[] = {"Est", "Nord", "Ovest", "Sud"};
void studentCode();

// TODO: Implement navigation function
void navigate_to_position(int target_x, int target_y) {
    // Navigate Karel from current position to target position
    // HINT: Move horizontally first, then vertically
    // Consider Karel's current direction and use appropriate turns
}

// TODO: Implement the main visiting function
void visit_all_positions() {
    // Define arrays with target positions
    int x_positions[] = {3, 1, 5, 4, 2};
    int y_positions[] = {2, 4, 1, 3, 5};
    
    // Calculate number of positions
    int num_positions = sizeof(x_positions) / sizeof(x_positions[0]);
    
    // Visit each position in sequence
    for (int i = 0; i < num_positions; i++) {
        printf("Moving to position (%d, %d)...\n", x_positions[i], y_positions[i]);
        
        // TODO: Navigate to position and pick up beeper
        // navigate_to_position(x_positions[i], y_positions[i]);
        // if (beepers_present()) {
        //     karel_pick_beeper();
        //     printf("Beeper collected at (%d, %d)\n", karel_get_x(), karel_get_y());
        // }
    }
}

void setup() {
    karel_init();
    
    // Place beepers at target positions
    karel_add_beeper(3, 2);
    karel_add_beeper(1, 4);
    karel_add_beeper(5, 1);
    karel_add_beeper(4, 3);
    karel_add_beeper(2, 5);
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

void studentCode() {
    static bool missionComplete = false;
    
    if (!missionComplete) {
        // TODO: Call visit_all_positions() function here
        // Remember to manage the state appropriately
        
        printf("Karel position: (%d, %d) - Direction: %s\n", 
               karel_get_x(), karel_get_y(), DIRECTION_NAMES[karel_get_direction()]);
               
        // Uncomment when ready to test:
        // visit_all_positions();
        // missionComplete = true;
    }
}
