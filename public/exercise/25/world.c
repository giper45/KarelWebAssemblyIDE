#include "karel.h"

const char* DIRECTION_NAMES[] = {"Est", "Nord", "Ovest", "Sud"};

void setup() {
    karel_init();
    
    // Place beepers in a pattern for search demonstration
    karel_add_beeper(4, 3);
    karel_add_beeper(8, 2);
    karel_add_beeper(6, 5);
    
    printf("Linear Search Algorithm Demo\n");
    printf("============================\n");
    printf("Karel will search systematically for beepers\n");
    printf("Watch the row-by-row search pattern\n");
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
