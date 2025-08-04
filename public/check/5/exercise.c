#include "karel.h"
#include <stdio.h>

// Global constants - demonstrate const keyword
const int MAX_MOVES = 50;
const char* DIRECTION_NAMES[] = {"Est", "Nord", "Ovest", "Sud"};

// Global variables to track Karel's statistics
// TODO: Declare variables to track:
// - Number of moves made
// - Number of turns made  
// - Number of beepers picked up
// - Number of beepers put down
// - Total distance traveled (as float)

void setup() {
    karel_init();
    
    // Add some beepers for Karel to interact with
    karel_add_beeper(3, 2);
    karel_add_beeper(5, 4);
    karel_add_beeper(7, 3);
    
    // TODO: Initialize your tracking variables here
    printf("Karel Statistics Tracker Started\n");
    printf("=================================\n");
}

void draw() {
    canvas_setFillStyleZ("white");
    canvas_fillRect(0, 0, 800, 600);
    drawWalls();
    drawGrid();
    drawBeepers();
    drawKarel();
    drawInfo();
    
    // TODO: Display statistics on screen
    // Show current counts using printf statements
}

void loop(double timeSec, double elapsedSec) {
    draw();
    
    static double lastMoveTime = 0;
    
    if (timeSec - lastMoveTime > 1.0) {
        // TODO: Make Karel move and count movements
        // If front is clear, move and increment move counter
        
        // TODO: If Karel hits a wall, turn left and count turns
        
        // TODO: If standing on a beeper, pick it up and count
        
        // TODO: Every 10 moves, put down a beeper and count
        
        // TODO: Calculate and display statistics:
        // - Average moves per turn
        // - Distance traveled
        // - Beeper collection efficiency
        
        lastMoveTime = timeSec;
    }
}
