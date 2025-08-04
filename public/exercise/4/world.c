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
}
