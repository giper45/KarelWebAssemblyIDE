#include "karel.h"

const char* DIRECTION_NAMES[] = {"Est", "Nord", "Ovest", "Sud"};

void setup() {
    karel_init();
    
    // Simple world setup for control structure demonstration
    karel_add_beeper(5, 3);
    karel_add_beeper(8, 6);
    
    printf("Control Structures Demo\n");
    printf("======================\n");
    printf("Demonstrating if-else, loops, and switch statements\n");
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
    
    // Example of control structures
    static int demo_step = 0;
    static double last_time = 0;
    

}
