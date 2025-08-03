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
    
    if (timeSec - lastMoveTime > 0.5) {
        // TODO: Write your code to make Karel walk in a square
        // Hint: You need to move 3 steps, then turn left, repeat 4 times
        
        // Example pattern:
        // 1. Move forward 3 times
        // 2. Turn left
        // 3. Repeat steps 1-2 four times total
        
        lastMoveTime = timeSec;
    }
}
