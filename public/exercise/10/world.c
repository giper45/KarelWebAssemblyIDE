#include "karel.h"

const char* DIRECTION_NAMES[] = {"Est", "Nord", "Ovest", "Sud"};

// Example global variables
int global_counter = 0;
char status_message[100] = "Ready";

// Function demonstrating local variables
void local_demo() {
    int local_var = 42;  // Only exists in this function
    printf("Local variable: %d\n", local_var);
}

// Function demonstrating static variables  
void static_demo() {
    static int static_counter = 0;  // Retains value between calls
    static_counter++;
    printf("Static counter: %d\n", static_counter);
}

void setup() {
    karel_init();
    
    printf("Scope & Variables Demo\n");
    printf("=====================\n");
    printf("Global counter: %d\n", global_counter);
    printf("Status: %s\n", status_message);
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
    
    static double last_time = 0;
    
    if (timeSec - last_time > 3.0) {
        local_demo();
        static_demo();
        global_counter++;
        last_time = timeSec;
    }
}
