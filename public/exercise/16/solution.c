#include "karel.h"
#define REFRESH_RATE 0.5
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
    
    // Simplified obstacle setup - only add a few key walls to create the maze
    // Block path at (3,1) - wall to the right
    karel_add_vertical_wall(4, 1, 1);
    
    // Block path at (3,2) - wall above
    karel_add_horizontal_wall(3, 3, 1);
    
    // Block path at (4,3) - wall to the right
    karel_add_vertical_wall(5, 3, 1);
    
    printf("Exercise 16: Grid Navigation with 2D Arrays\n");
    printf("Karel must navigate through obstacles to collect 3 beepers\n");
}

// Simplified beeper tracking
bool beepers_present_at(int x, int y) {
    if (karel_get_x() == x && karel_get_y() == y) {
        return beepers_present();
    }
    
    // Track known beeper positions
    return (x == 5 && y == 1) || (x == 5 && y == 3) || (x == 2 && y == 5);
}

static double lastMoveTime = 0;

void loop(double timeSec, double elapsedSec) {
    if(timeSec - lastMoveTime > REFRESH_RATE) {
        bool ready = drawWorld();
        if (ready)
            studentCode();
        lastMoveTime = timeSec;
    }
}

// Fixed function that doesn't add extra movements to buffer
bool can_move_in_direction(int direction) {
    // Use simulated state to check movement without actually moving
    KarelSimulatedState simulated = karel_simulate_state();
    
    // Simulate facing the desired direction
    int temp_direction = simulated.direction;
    while (temp_direction != direction) {
        temp_direction = (temp_direction + 1) % 4;
    }
    
    // Check if movement is possible from simulated position
    int new_x = simulated.x;
    int new_y = simulated.y;
    
    switch (direction) {
        case 0: new_x++; break; // East
        case 1: new_y++; break; // North  
        case 2: new_x--; break; // West
        case 3: new_y--; break; // South
    }
    
    // Check bounds
    if (new_x < 1 || new_x > REAL_WORLD_WIDTH || new_y < 1 || new_y > REAL_WORLD_HEIGHT) {
        return false;
    }
    
    // For now, assume no walls (simplified check)
    // In a real implementation, you'd check the wall arrays
    return true;
}

// Safe function to turn to a direction
void face_direction(int target_direction) {
    int current = karel_get_direction();
    
    // Calculate shortest rotation
    while (current != target_direction) {
        karel_turn_left();
        current = (current + 1) % 4;
    }
}

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
            } else if (beepers_present_at(col, row)) {
                printf("B "); // Beeper
            } else {
                printf(". "); // Empty
            }
        }
        printf("\n");
    }
    printf("\n");
}

// Simplified movement function
bool try_move_towards(int target_x, int target_y) {
    int current_x = karel_get_x();
    int current_y = karel_get_y();
    
    // If already at target
    if (current_x == target_x && current_y == target_y) {
        return true;
    }
    
    // Try horizontal movement first
    if (current_x < target_x) {
        // Try moving east
        face_direction(0);
        if (front_is_clear()) {
            karel_move();
            printf("Moved east to (%d, %d)\n", karel_get_x(), karel_get_y());
            return false; // Not at target yet
        }
    } else if (current_x > target_x) {
        // Try moving west
        face_direction(2);
        if (front_is_clear()) {
            karel_move();
            printf("Moved west to (%d, %d)\n", karel_get_x(), karel_get_y());
            return false; // Not at target yet
        }
    }
    
    // Try vertical movement
    if (current_y < target_y) {
        // Try moving north
        face_direction(1);
        if (front_is_clear()) {
            karel_move();
            printf("Moved north to (%d, %d)\n", karel_get_x(), karel_get_y());
            return false; // Not at target yet
        }
    } else if (current_y > target_y) {
        // Try moving south
        face_direction(3);
        if (front_is_clear()) {
            karel_move();
            printf("Moved south to (%d, %d)\n", karel_get_x(), karel_get_y());
            return false; // Not at target yet
        }
    }
    
    // If direct path blocked, try any available direction
    printf("Direct path blocked, trying alternative routes...\n");
    for (int dir = 0; dir < 4; dir++) {
        face_direction(dir);
        if (front_is_clear()) {
            karel_move();
            printf("Moved in direction %s to (%d, %d)\n", DIRECTION_NAMES[dir], karel_get_x(), karel_get_y());
            return false; // Moved but not at target
        }
    }
    
    printf("Warning: No valid moves available!\n");
    return false;
}

void navigate_to_beeper(int target_x, int target_y) {
    printf("\n=== Navigating to beeper at (%d, %d) ===\n", target_x, target_y);
    
    int max_steps = 20;
    int steps = 0;
    
    while (steps < max_steps) {
        if (karel_get_x() == target_x && karel_get_y() == target_y) {
            // We've reached the target
            if (beepers_present()) {
                karel_pick_beeper();
                printf("*** Collected beeper at (%d, %d)! ***\n", karel_get_x(), karel_get_y());
            }
            return;
        }
        
        bool moved = try_move_towards(target_x, target_y);
        if (moved) {
            break; // Reached target
        }
        
        steps++;
    }
    
    if (steps >= max_steps) {
        printf("Failed to reach beeper at (%d, %d) after %d steps\n", target_x, target_y, max_steps);
    }
}

void studentCode() {
    static bool mission_complete = false;
    static int beeper_index = 0;
    
    if (mission_complete) {
        return;
    }
    
    // Beeper positions: (5,1), (5,3), (2,5)
    int beeper_positions[][2] = {{5, 1}, {5, 3}, {2, 5}};
    int num_beepers = 3;
    
    printf("Karel position: (%d, %d) - Direction: %s\n", 
           karel_get_x(), karel_get_y(), DIRECTION_NAMES[karel_get_direction()]);
    
    if (beeper_index == 0) {
        print_world_state();
    }
    
    if (beeper_index < num_beepers) {
        navigate_to_beeper(beeper_positions[beeper_index][0], beeper_positions[beeper_index][1]);
        
        // Check if we successfully collected the beeper
        if (karel_get_x() == beeper_positions[beeper_index][0] && 
            karel_get_y() == beeper_positions[beeper_index][1]) {
            beeper_index++;
        }
    } else {
        printf("\n=== All beepers collected! Mission complete! ===\n");
        printf("Final position: (%d, %d)\n", karel_get_x(), karel_get_y());
        printf("Beepers collected: %d\n", karel_get_bag_beepers());
        mission_complete = true;
    }
}