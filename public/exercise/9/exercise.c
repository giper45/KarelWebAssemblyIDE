#include "karel.h"

const char* DIRECTION_NAMES[] = {"Est", "Nord", "Ovest", "Sud"};

// TODO: Declare your Karel utility functions here

// TODO: Create karel_turn_right() function
// This function should turn Karel right by turning left 3 times

// TODO: Create karel_move_steps(int steps) function  
// This function should move Karel safely for 'steps' number of steps
// Stop if hitting a wall before completing all steps

// TODO: Create karel_turn_around() function
// This function should turn Karel 180 degrees

// TODO: Create int count_moves_to_wall() function
// This function should return how many steps Karel can take before hitting a wall
// Don't actually move Karel, just count

// TODO: Create int safe_to_move() function
// Return 1 if Karel can move forward safely, 0 if blocked

// TODO: Create void karel_go_to_corner() function
// Move Karel to the nearest corner of the world

void setup() {
    karel_init();
    
    // Add some beepers for testing
    karel_add_beeper(5, 3);
    karel_add_beeper(7, 6);
    
    // Add some walls for testing navigation
    karel_add_horizontal_wall(3, 3, 2);
    karel_add_vertical_wall(6, 2, 3);
    
    printf("Karel Function Library Test\n");
    printf("===========================\n");
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
    
    static double lastActionTime = 0;
    static int test_phase = 0;
    
    if (timeSec - lastActionTime > 1.5) {
        switch(test_phase) {
            case 0:
                printf("Testing karel_turn_right()...\n");
                // TODO: Test your karel_turn_right function
                break;
                
            case 1:
                printf("Testing karel_move_steps(3)...\n");
                // TODO: Test your karel_move_steps function
                break;
                
            case 2:
                printf("Testing count_moves_to_wall()...\n");
                // TODO: Test your count_moves_to_wall function
                // printf("Steps to wall: %d\n", count_moves_to_wall());
                break;
                
            case 3:
                printf("Testing karel_turn_around()...\n");
                // TODO: Test your karel_turn_around function
                break;
                
            case 4:
                printf("Testing safe_to_move()...\n");
                // TODO: Test your safe_to_move function
                // printf("Safe to move: %s\n", safe_to_move() ? "Yes" : "No");
                break;
        }
        
        test_phase++;
        if (test_phase > 4) test_phase = 0;
        lastActionTime = timeSec;
    }
}

// TODO: Implement all your functions here

// Example implementation starter:
// void karel_turn_right() {
//     karel_turn_left();
//     karel_turn_left();
//     karel_turn_left();
// }
