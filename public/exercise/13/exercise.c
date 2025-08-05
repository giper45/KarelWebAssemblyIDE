#include "karel.h"
#define REFRESH_RATE 1.0 // 1 second for smooth updates

const char* DIRECTION_NAMES[] = {"Est", "Nord", "Ovest", "Sud"};
void studentCode();

// TODO: Implement these functions
void move_one_side() {
    // Move Karel forward 3 steps (one side of the square)
    // HINT: Use a loop or call karel_move() three times
}

void turn_corner() {
    // Turn Karel left to prepare for the next side
    // HINT: Use karel_turn_left() once
}

void draw_square() {
    // Use move_one_side() and turn_corner() to draw a complete square
    // HINT: A square has 4 sides, so you need to repeat the pattern 4 times
}

void setup() {
    karel_init();
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
    static bool squareComplete = false;
    
    if (!squareComplete) {
        // TODO: Call draw_square() function here
        // Remember to manage the state so the square is only drawn once
        
        printf("Karel position: (%d, %d) - Direction: %s\n", 
               karel_get_x(), karel_get_y(), DIRECTION_NAMES[karel_get_direction()]);
    }
}
