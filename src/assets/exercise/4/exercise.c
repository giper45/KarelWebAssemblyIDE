#include "karel.h"
#define REFRESH_RATE 1.0 // 1 second for smooth updates

const char* DIRECTION_NAMES[] = {"Est", "Nord", "Ovest", "Sud"};

void setup() {
    karel_init();
    
    // Place beepers at various locations
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
    
    if (timeSec - lastMoveTime > REFRESH_RATE) { // Check frequently for smooth timing
        // Check for beepers and collect them
        if (beepers_present()) {
            karel_pick_beeper();
            printf("Beeper collected! Bag has %d beepers", karel_get_bag_beepers());
        }
        
        // TODO: Student should implement systematic movement
        // This is placeholder movement - replace with proper search pattern
        if (front_is_clear()) {
            karel_move();
        } else {
            karel_turn_left();
        }
        
        lastMoveTime = timeSec;
    }
}
