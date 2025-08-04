#include "karel.h"

const char* DIRECTION_NAMES[] = {"Est", "Nord", "Ovest", "Sud"};

void setup() {
    karel_init();
    
    printf("Stack & Queue Demo\n");
    printf("==================\n");
    
    // Set up visual representation
    // Stack column (vertical)
    printf("Stack (LIFO): Vertical column at x=2\n");
    
    // Queue row (horizontal)  
    printf("Queue (FIFO): Horizontal row at y=2\n");
    
    // Add some initial demonstration elements
    karel_add_beeper(2, 1);  // Bottom of stack
    karel_add_beeper(4, 2);  // Front of queue
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
}
