#include "karel.h"

const char* DIRECTION_NAMES[] = {"Est", "Nord", "Ovest", "Sud"};

void setup() {
    karel_init();
    
    printf("Binary Search Algorithm Demo\n");
    printf("============================\n");
    
    // Set up sorted beepers for demonstration
    karel_add_beeper(3, 3);
    karel_add_beeper(5, 3);
    karel_add_beeper(7, 3);
    karel_add_beeper(8, 3);
    
    printf("Sorted beeper positions: 3, 5, 7, 8\n");
    printf("Binary search will efficiently find target beeper\n");
    printf("by eliminating half the search space each step.\n");
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
