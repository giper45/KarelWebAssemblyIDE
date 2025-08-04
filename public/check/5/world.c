#include "karel.h"

const char* DIRECTION_NAMES[] = {"Est", "Nord", "Ovest", "Sud"};

// Example variables demonstrating different data types
int total_moves = 0;
float average_speed = 0.0f;
char current_status = 'R';  // R=Running, S=Stopped, T=Turning

void setup() {
    karel_init();
    
    printf("Karel Data Types Demo\n");
    printf("====================\n");
    printf("int size: %zu bytes\n", sizeof(int));
    printf("float size: %zu bytes\n", sizeof(float));
    printf("char size: %zu bytes\n", sizeof(char));
    printf("\n");
}

void draw() {
    canvas_setFillStyleZ("white");
    canvas_fillRect(0, 0, 800, 600);
    drawWalls();
    drawGrid();
    drawBeepers();
    drawKarel();
    drawInfo();
    
    // Display current statistics
    printf("Status: %c | Moves: %d | Speed: %.2f\n", 
           current_status, total_moves, average_speed);
}

void loop(double timeSec, double elapsedSec) {
    draw();
}
