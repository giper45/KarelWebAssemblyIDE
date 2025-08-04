#include "karel.h"

const char* DIRECTION_NAMES[] = {"Est", "Nord", "Ovest", "Sud"};

void setup() {
    karel_init();
    
    printf("Input Processing Demo\n");
    printf("====================\n");
    printf("This demonstrates how to read and validate user input\n");
    printf("for controlling Karel's behavior.\n\n");
    
    printf("Format specifiers demo:\n");
    printf("Integer: %d\n", 42);
    printf("Character: %c\n", 'K');
    printf("String: %s\n", "Karel");
    printf("Float: %.2f\n", 3.14f);
    printf("Right-aligned: %10d\n", 123);
    printf("Left-aligned: %-10s|\n", "Karel");
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
