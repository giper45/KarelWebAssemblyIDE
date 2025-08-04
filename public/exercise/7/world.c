#include "karel.h"

// Example constants and preprocessor usage
#define DEMO_DELAY 2000
#define MAX_DEMO_STEPS 5

const char* DIRECTION_NAMES[] = {"Est", "Nord", "Ovest", "Sud"};

void setup() {
    karel_init();
    
    printf("Constants & Preprocessor Demo\n");
    printf("=============================\n");
    printf("Delay setting: %d ms\n", DEMO_DELAY);
    printf("Max steps: %d\n", MAX_DEMO_STEPS);
    
    #ifdef DEBUG
        printf("Debug mode is active\n");
    #else
        printf("Release mode\n");
    #endif
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
