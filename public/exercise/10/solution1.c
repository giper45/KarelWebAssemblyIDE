#include "karel.h"
#define REFRESH_RATE 0.2 // 0.2 seconds for smooth updates

const char* DIRECTION_NAMES[] = {"East", "North", "West", "South"};
void studentCode();

void setup() {
    karel_init();
    // No beepers needed for this exercise - just clear path for movement
    printf("Exercise 10: Repeat Path\n");
    printf("Karel will move forward 3 cells and back 4 times.\n");
}

static double lastMoveTime = 0;

void loop(double timeSec, double elapsedSec) {
    if(timeSec - lastMoveTime > REFRESH_RATE) { // Check frequently for smooth timing
        bool ready = drawWorld();
        if (ready) 
            studentCode();
        lastMoveTime = timeSec;
    }
}

enum Phase {
    MOVING_FORWARD,
    TURNING_AROUND,
    MOVING_BACKWARD,
    RESETTING_DIRECTION,
    COMPLETE
};

void studentCode() {
    static bool exerciseComplete = false;
    static int currentIteration = 0;
    static enum Phase currentPhase = MOVING_FORWARD;
    static int steps = 0;
    
    if (!exerciseComplete && currentIteration < 4) {
        switch (currentPhase) {
            case MOVING_FORWARD: // Forward movement phase
                if (steps == 0) {
                    printf("Starting iteration %d...\n", currentIteration + 1);
                }
                if (steps < 3 && front_is_clear()) {
                    karel_move();
                    steps++;
                    printf("Moving forward: Step %d to (%d,%d)\n", steps, karel_get_x(), karel_get_y());
                    return;
                } else {
                    // Finished forward movement, prepare to turn around
                    printf("Turning around to face West...\n");
                    currentPhase = TURNING_AROUND;
                    steps = 0;
                    return;
                }
                break;
                
            case TURNING_AROUND: // Turn around phase
                if (steps < 2) {
                    karel_turn_left();
                    steps++;
                    return;
                } else {
                    // Finished turning around, prepare for backward movement
                    currentPhase = MOVING_BACKWARD;
                    steps = 0;
                    return;
                }
                break;
                
            case MOVING_BACKWARD: // Backward movement phase
                if (steps < 3 && front_is_clear()) {
                    karel_move();
                    steps++;
                    printf("Moving backward: Step %d to (%d,%d)\n", steps, karel_get_x(), karel_get_y());
                    return;
                } else {
                    // Finished backward movement, prepare to reset direction
                    printf("Turning around to face East...\n");
                    currentPhase = RESETTING_DIRECTION;
                    steps = 0;
                    return;
                }
                break;
                
            case RESETTING_DIRECTION: // Reset direction phase
                if (steps < 2) {
                    karel_turn_left();
                    steps++;
                    return;
                } else {
                    // Finished iteration
                    printf("Iteration %d complete!\n", currentIteration + 1);
                    currentIteration++;
                    currentPhase = MOVING_FORWARD;
                    steps = 0;
                    return;
                }
                break;
                
            case COMPLETE:
                // This case won't be reached in this logic flow
                break;
        }
    } else if (!exerciseComplete) {
        printf("All 4 iterations completed! Karel back at starting position.\n");
        printf("Final position: (%d,%d) facing %s\n", karel_get_x(), karel_get_y(), DIRECTION_NAMES[karel_get_direction()]);
        exerciseComplete = true;
    }
}
