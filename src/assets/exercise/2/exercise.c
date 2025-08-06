#include "karel.h"
#define REFRESH_RATE 0.5 // 1 second for smooth updates

const char* DIRECTION_NAMES[] = {"Est", "Nord", "Ovest", "Sud"};

void setup() {
    karel_init();
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
        // TODO: Write your navigation code here
        // Goal: Reach the top-right corner at (10, 8)
        
        // Hint: First move east, then north
        // Use facing_east() and facing_north() to check direction
        
        lastMoveTime = timeSec;
    }
}
