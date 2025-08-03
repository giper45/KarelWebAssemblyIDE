#include "karel.h"

const char* DIRECTION_NAMES[] = {"Est", "Nord", "Ovest", "Sud"};

void setup() {
    karel_init();
    
    // Place beepers at various locations for collection
    karel_add_beeper(3, 2);
    karel_add_beeper(7, 4);
    karel_add_beeper(2, 6);
    karel_add_beeper(8, 3);
    karel_add_beeper(5, 7);
    karel_add_beeper(9, 2);
}

void draw() {
    canvas_setFillStyleZ("white");
    canvas_fillRect(0, 0, 800, 600);
    drawWalls();
    drawGrid();
    drawBeepers();
    drawKarel();
    drawInfo();
}

void loop(double timeSec, double elapsedSec) {
    draw();
    
    static double lastMoveTime = 0;
    static int beepersCollected = 0;
    const int totalBeepers = 6;
    
    if (beepersCollected >= totalBeepers) {
        printf("Mission Complete! All %d beepers collected!", totalBeepers);
        return;
    }
    
    if (timeSec - lastMoveTime > 0.6) {
        // Always check for beepers first
        if (beepers_present()) {
            karel_pick_beeper();
            beepersCollected++;
            printf("Beeper collected! %d/%d collected", beepersCollected, totalBeepers);
        }
        
        // Systematic movement pattern: row by row sweep
        if (facing_east() && front_is_clear()) {
            karel_move();
        } else if (facing_east() && !front_is_clear()) {
            // End of row, go up and turn around
            karel_turn_left(); // Face north
            if (front_is_clear()) {
                karel_move();
                karel_turn_left(); // Face west
            } else {
                // At top, search is complete
                karel_turn_left(); // Face west anyway
            }
        } else if (facing_west() && front_is_clear()) {
            karel_move();
        } else if (facing_west() && !front_is_clear()) {
            // End of row going west, go up and turn around
            karel_turn_right(); // Face north
            if (front_is_clear()) {
                karel_move();
                karel_turn_right(); // Face east
            }
        } else {
            // Handle other directions by turning to face east
            while (!facing_east()) {
                karel_turn_left();
            }
        }
        
        lastMoveTime = timeSec;
    }
}

// Helper function to turn right (not built-in)
void karel_turn_right() {
    karel_turn_left();
    karel_turn_left();
    karel_turn_left();
}
