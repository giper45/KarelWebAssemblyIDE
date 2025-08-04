#include "karel.h"

const char* DIRECTION_NAMES[] = {"Est", "Nord", "Ovest", "Sud"};

// TODO: Global variables for Karel's journey statistics
// int total_moves = 0;
// int total_turns = 0;
// int beepers_collected = 0;
// float average_moves_per_minute = 0.0f;

// TODO: Global configuration variables
// int debug_enabled = 1;
// char current_mission[50] = "Exploration";

// TODO: Function to demonstrate local variables
// void calculate_distance_stats() {
//     // Local variables - only exist within this function
//     int start_x = 1, start_y = 1;  // Starting position
//     int current_x = karel.x, current_y = karel.y;
//     
//     // Calculate Manhattan distance (local calculation)
//     int distance = abs(current_x - start_x) + abs(current_y - start_y);
//     
//     printf("Distance from start: %d steps\n", distance);
//     // start_x, start_y, distance are destroyed when function exits
// }

// TODO: Function to demonstrate static variables
// void count_function_calls() {
//     static int call_count = 0;  // Retains value between calls
//     call_count++;
//     printf("This function has been called %d times\n", call_count);
// }

// TODO: Function to demonstrate variable shadowing
// void show_variable_shadowing() {
//     int total_moves = 99;  // Shadows the global variable
//     printf("Local total_moves: %d\n", total_moves);      // Shows 99
//     printf("Global total_moves: %d\n", ::total_moves);   // Shows global value
// }

// TODO: Function with parameters (local scope)
// void move_karel_safely(int steps, int max_attempts) {
//     // steps and max_attempts are local to this function
//     int attempts = 0;
//     int successful_moves = 0;
//     
//     while (successful_moves < steps && attempts < max_attempts) {
//         if (front_is_clear()) {
//             karel_move();
//             successful_moves++;
//             total_moves++;  // Modify global variable
//         } else {
//             karel_turn_left();
//             total_turns++;  // Modify global variable
//         }
//         attempts++;
//     }
//     
//     printf("Moved %d out of %d requested steps\n", successful_moves, steps);
// }

void setup() {
    karel_init();
    
    // Add some beepers for collection testing
    karel_add_beeper(4, 3);
    karel_add_beeper(7, 5);
    karel_add_beeper(2, 6);
    
    printf("Karel Scope & Variables Demo\n");
    printf("============================\n");
    
    // TODO: Initialize global variables
    // strcpy(current_mission, "Beeper Collection");
    
    printf("Mission: %s\n", "Demo Mission");  // Should use global variable
}

void draw() {
    canvas_setFillStyleZ("white");
    canvas_fillRect(0, 0, 800, 600);
    drawWalls();
    drawGrid();
    drawBeepers();
    drawKarel();
    drawInfo();
    
    // TODO: Display global statistics
    // printf("Global Stats - Moves: %d, Turns: %d, Beepers: %d\n", 
    //        total_moves, total_turns, beepers_collected);
}

void loop(double timeSec, double elapsedSec) {
    draw();
    
    static double lastActionTime = 0;
    static int demo_phase = 0;
    
    if (timeSec - lastActionTime > 2.0) {
        
        switch(demo_phase % 5) {
            case 0:
                printf("Demo: Using local variables for calculations\n");
                // TODO: Call calculate_distance_stats()
                break;
                
            case 1:
                printf("Demo: Static variable persistence\n");
                // TODO: Call count_function_calls() multiple times
                break;
                
            case 2:
                printf("Demo: Variable shadowing\n");
                // TODO: Call show_variable_shadowing()
                break;
                
            case 3:
                printf("Demo: Function parameters and safe movement\n");
                // TODO: Call move_karel_safely(3, 10)
                break;
                
            case 4:
                printf("Demo: Global state management\n");
                // TODO: Show how global variables persist across function calls
                if (beepers_present()) {
                    karel_pick_beeper();
                    // TODO: Increment beepers_collected global counter
                }
                break;
        }
        
        demo_phase++;
        lastActionTime = timeSec;
    }
}
