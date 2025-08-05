#include "karel.h"
#define REFRESH_RATE 0.1
#define REAL_WORLD_WIDTH 10
#define REAL_WORLD_HEIGHT 8

const char* DIRECTION_NAMES[] = {"East", "North", "West", "South"};

void studentCode();

void setup() {
    karel_init();
    karel_set_bag_beepers(0);
    
    // Place beepers at specified positions
    karel_add_beeper(5, 1);
    karel_add_beeper(5, 3);
    karel_add_beeper(2, 5);
    
    // Simplified obstacle setup
    karel_add_vertical_wall(4, 1, 1);   // Right of (3,1)
    karel_add_horizontal_wall(3, 3, 1); // Above (3,2)
    karel_add_vertical_wall(5, 3, 1);   // Right of (4,3)

    printf("Exercise 16: Grid Navigation with 2D Arrays\n");
    printf("Karel must navigate through obstacles to collect 3 beepers\n");
}

static double lastMoveTime = 0;

void loop(double timeSec, double elapsedSec) {
    if (timeSec - lastMoveTime > REFRESH_RATE) {
        bool ready = drawWorld();
        if (ready)
            studentCode();
        lastMoveTime = timeSec;
    }
}

// 👇 Included to support 2D grid logic and debugging
void print_world_state() {
    printf("\nCurrent World State:\n");
    printf("Karel at (%d, %d) facing %s\n", 
           karel_get_x(), karel_get_y(), DIRECTION_NAMES[karel_get_direction()]);
    printf("Beepers in bag: %d\n", karel_get_bag_beepers());
    
    printf("   ");
    for (int col = 1; col <= 6; col++) {
        printf("%d ", col);
    }
    printf("\n");
    
    for (int row = 6; row >= 1; row--) {
        printf("%d: ", row);
        for (int col = 1; col <= 6; col++) {
            if (karel_get_x() == col && karel_get_y() == row) {
                printf("K "); // Karel's position
            } else if ((col == 5 && row == 1) ||
                       (col == 5 && row == 3) ||
                       (col == 2 && row == 5)) {
                printf("B "); // Beeper
            } else {
                printf(". "); // Empty
            }
        }
        printf("\n");
    }
    printf("\n");
}

// 🧠 Student writes everything here using arrays
void studentCode() {
    // TODO: Use a 2D array to track grid state
    // Example: char grid[REAL_WORLD_WIDTH+1][REAL_WORLD_HEIGHT+1];

    // You may use the print_world_state() function to debug

    // Write code to:
    // - Track positions
    // - Navigate with walls
    // - Collect 3 beepers at:
    //     - (5,1), (5,3), (2,5)
}
