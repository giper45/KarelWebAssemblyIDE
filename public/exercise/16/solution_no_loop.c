#include "karel.h"
#define REFRESH_RATE 1.0
#define REAL_WORLD_WIDTH 10
#define REAL_WORLD_HEIGHT 8

const char* DIRECTION_NAMES[] = {"Est", "Nord", "Ovest", "Sud"};
void studentCode();

void setup() {
    karel_init();
    
    // Place beepers at specified positions
    karel_add_beeper(5, 1);
    karel_add_beeper(5, 3);
    karel_add_beeper(2, 5);
    
    // Add obstacles as walls
    karel_add_vertical_wall(3, 1, 1);   // Obstacle at (3,1)
    karel_add_vertical_wall(2, 2, 1);   // Obstacle at (2,2)
    karel_add_vertical_wall(3, 2, 1);   // Obstacle at (3,2)
    karel_add_vertical_wall(4, 3, 1);   // Obstacle at (4,3)
    karel_add_vertical_wall(1, 4, 1);   // Obstacle at (1,4)
    karel_add_vertical_wall(5, 4, 1);   // Obstacle at (5,4)
    karel_add_vertical_wall(3, 6, 1);   // Obstacle at (3,6)
    karel_add_vertical_wall(4, 6, 1);   // Obstacle at (4,6)
}

// Helper function to check beepers at specific location (simulated)
bool beepers_present_at(int x, int y) {
    // Save current position
    int orig_x = karel_get_x();
    int orig_y = karel_get_y();
    
    // If we're already at the target position
    if (orig_x == x && orig_y == y) {
        return beepers_present();
    }
    
    // We can't easily check other positions without moving Karel
    // For this exercise, we'll track known beeper positions
    static bool first_run = true;
    static bool beeper_map[REAL_WORLD_WIDTH + 1][REAL_WORLD_HEIGHT + 1];
    
    if (first_run) {
        // Initialize beeper map
        for (int i = 0; i <= REAL_WORLD_WIDTH; i++) {
            for (int j = 0; j <= REAL_WORLD_HEIGHT; j++) {
                beeper_map[i][j] = false;
            }
        }
        // Set known beeper positions
        beeper_map[5][1] = true;
        beeper_map[5][3] = true;
        beeper_map[2][5] = true;
        first_run = false;
    }
    
    return beeper_map[x][y];
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

void turn_to_direction(int target_direction) {
    while (karel_get_direction() != target_direction) {
        karel_turn_left();
    }
}

bool can_move_direction(int direction) {
    int current_dir = karel_get_direction();
    
    // Face the desired direction
    while (karel_get_direction() != direction) {
        karel_turn_left();
    }
    
    bool canMove = front_is_clear();
    
    // Restore original direction
    while (karel_get_direction() != current_dir) {
        karel_turn_left();
    }
    
    return canMove;
}

void print_world_state() {
    printf("\nCurrent World State:\n");
    printf("Karel at (%d, %d) facing %s\n", 
           karel_get_x(), karel_get_y(), DIRECTION_NAMES[karel_get_direction()]);
    printf("Beepers in bag: %d\n", karel_get_bag_beepers());
    
    printf("   ");
    for (int col = 1; col <= REAL_WORLD_WIDTH; col++) {
        printf("%d ", col);
    }
    printf("\n");
    
    for (int row = REAL_WORLD_HEIGHT; row >= 1; row--) {
        printf("%d: ", row);
        for (int col = 1; col <= REAL_WORLD_WIDTH; col++) {
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


void move_towards_target(int target_x, int target_y) {
    int current_x = karel_get_x();
    int current_y = karel_get_y();
    
    printf("Moving from (%d, %d) towards (%d, %d)\n", current_x, current_y, target_x, target_y);
    
    // If we're already at the target, do nothing
    if (current_x == target_x && current_y == target_y) {
        printf("Already at target (%d, %d)\n", target_x, target_y);
        return;
    }
    
    // Try to move horizontally first
    if (current_x != target_x) {
        if (current_x < target_x) {
            // Need to move east
            if (can_move_direction(0)) {
                turn_to_direction(0); // Face east
                karel_move();
                printf("Moved east to (%d, %d)\n", karel_get_x(), karel_get_y());
                return;
            }
        } else {
            // Need to move west
            if (can_move_direction(2)) {
                turn_to_direction(2); // Face west
                karel_move();
                printf("Moved west to (%d, %d)\n", karel_get_x(), karel_get_y());
                return;
            }
        }
    }
    
    // Try to move vertically
    if (current_y != target_y) {
        if (current_y < target_y) {
            // Need to move north
            if (can_move_direction(1)) {
                turn_to_direction(1); // Face north
                karel_move();
                printf("Moved north to (%d, %d)\n", karel_get_x(), karel_get_y());
                return;
            }
        } else {
            // Need to move south
            if (can_move_direction(3)) {
                turn_to_direction(3); // Face south
                karel_move();
                printf("Moved south to (%d, %d)\n", karel_get_x(), karel_get_y());
                return;
            }
        }
    }
    
    // If direct movement is blocked, try any available direction
    printf("Direct path blocked, trying alternative routes...\n");
    int directions[] = {0, 1, 2, 3}; // East, North, West, South
    for (int i = 0; i < 4; i++) {
        if (can_move_direction(directions[i])) {
            turn_to_direction(directions[i]);
            karel_move();
            printf("Moved in direction %d to (%d, %d)\n", directions[i], karel_get_x(), karel_get_y());
            return;
        }
    }
    
    printf("Warning: No valid moves available from (%d, %d)!\n", current_x, current_y);
}

void navigate_to_beepers() {
    // Beeper positions: (5,1), (5,3), (2,5)
    int beeper_positions[][2] = {{5, 1}, {5, 3}, {2, 5}};
    int num_beepers = 3;
    
    // Visit each beeper position
    for (int i = 0; i < num_beepers; i++) {
        int target_x = beeper_positions[i][0];
        int target_y = beeper_positions[i][1];
        
        printf("\n=== Navigating to beeper %d at (%d, %d) ===\n", i+1, target_x, target_y);
        
        // Navigate to position with step limit and progress checking
        int max_steps = 50;
        int steps = 0;
        int last_x = karel_get_x();
        int last_y = karel_get_y();
        int stuck_counter = 0;
        
        while ((karel_get_x() != target_x || karel_get_y() != target_y) && steps < max_steps) {
            move_towards_target(target_x, target_y);
            steps++;
            
            // Check if we're stuck (not moving)
            if (karel_get_x() == last_x && karel_get_y() == last_y) {
                stuck_counter++;
                if (stuck_counter > 3) {
                    printf("Karel seems stuck, trying to break free...\n");
                    // Try moving in any available direction
                    for (int dir = 0; dir < 4; dir++) {
                        if (can_move_direction(dir)) {
                            turn_to_direction(dir);
                            karel_move();
                            printf("Broke free by moving in direction %d\n", dir);
                            break;
                        }
                    }
                    stuck_counter = 0;
                }
            } else {
                stuck_counter = 0;
                last_x = karel_get_x();
                last_y = karel_get_y();
            }
        }
        
        if (steps >= max_steps) {
            printf("Failed to reach beeper at (%d, %d) after %d steps\n", target_x, target_y, max_steps);
            continue;
        }
        
        // Pick up beeper if present
        if (beepers_present()) {
            karel_pick_beeper();
            printf("*** Collected beeper at (%d, %d)! ***\n", karel_get_x(), karel_get_y());
        } else {
            printf("No beeper found at (%d, %d)\n", karel_get_x(), karel_get_y());
        }
    }
    
    printf("\n=== Beeper collection complete! ===\n");
}

void studentCode() {
    static bool missionComplete = false;
    
    if (!missionComplete) {
        printf("Karel position: (%d, %d) - Direction: %s\n", 
               karel_get_x(), karel_get_y(), DIRECTION_NAMES[karel_get_direction()]);
        
        print_world_state();
        
        navigate_to_beepers();
        
        missionComplete = true;
    }
}