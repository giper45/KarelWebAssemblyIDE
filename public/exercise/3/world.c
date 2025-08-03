#include "karel.h"

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
    static int step = 0;
    static int side = 0;
    
    if (timeSec - lastMoveTime > 0.8) {
        if (side < 4) {
            if (step < 3) {
                // Move forward 3 steps for each side
                karel_move();
                step++;
            } else {
                // Turn left after completing a side
                karel_turn_left();
                step = 0;
                side++;
            }
        } else {
            // Square completed
            printf("Square completed! Karel is back at start.");
        }
        
        lastMoveTime = timeSec;
    }
}
