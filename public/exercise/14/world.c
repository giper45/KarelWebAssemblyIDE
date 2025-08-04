#include "karel.h"
#include <string.h>

const char* DIRECTION_NAMES[] = {"Est", "Nord", "Ovest", "Sud"};

// Example string operations
char robot_name[50] = "Karel";
char greeting[100];

void setup() {
    karel_init();
    
    printf("String Operations Demo\n");
    printf("=====================\n");
    
    // String manipulation examples
    strcpy(greeting, "Hello, I am ");
    strcat(greeting, robot_name);
    
    printf("%s\n", greeting);
    printf("Name length: %zu characters\n", strlen(robot_name));
    
    // Character array demonstration
    char status[] = {'R', 'e', 'a', 'd', 'y', '\0'};
    printf("Status: %s\n", status);
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
