#include "karel.h"

const char* DIRECTION_NAMES[] = {"Est", "Nord", "Ovest", "Sud"};

void setup() {
    karel_init();
    // Simple world with just the boundary walls
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
    
    static bool reachedCorner = false;
    static double lastMoveTime = 0;
    
    // Check if Karel reached the corner
    if (karel.x == WORLD_WIDTH && karel.y == WORLD_HEIGHT) {
        reachedCorner = true;
        printf("Congratulations! Karel reached the corner!");
        return;
    }
    
    if (!reachedCorner && timeSec - lastMoveTime > 0.8) {
        // Student should implement their navigation logic here
        // This is a template - the student needs to write the actual logic
        
        if (front_is_clear()) {
            karel_move();
        } else {
            karel_turn_left();
        }
        
        lastMoveTime = timeSec;
    }
}
