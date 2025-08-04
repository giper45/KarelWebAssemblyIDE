#include "karel.h"

const char* DIRECTION_NAMES[] = {"Est", "Nord", "Ovest", "Sud"};

// Global variables for user interaction
int user_command = 0;
int move_count = 1;
char command_char = 'h';  // h=help, m=move, t=turn, p=put, g=get, q=quit

void setup() {
    karel_init();
    
    printf("Karel Interactive Command System\n");
    printf("================================\n");
    printf("Available commands:\n");
    printf("  h - Show help\n");
    printf("  m - Move Karel (specify number of steps)\n");
    printf("  t - Turn Karel left\n");
    printf("  p - Put beeper\n");
    printf("  g - Get beeper\n");
    printf("  s - Show status\n");
    printf("  q - Quit\n\n");
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
    
    static double lastCommandTime = 0;
    static int demo_mode = 1;  // Start in demo mode
    
    if (demo_mode && timeSec - lastCommandTime > 3.0) {
        // TODO: Simulate user input for demonstration
        // Show how different commands would work
        
        printf("Demo: Processing command input...\n");
        
        // TODO: Demonstrate different input scenarios:
        // 1. Reading move count: scanf("%d", &move_count)
        // 2. Reading command character: scanf(" %c", &command_char)  
        // 3. Validating input ranges
        // 4. Executing commands and showing results
        
        // Example command processing structure:
        /*
        printf("Enter command (h for help): ");
        scanf(" %c", &command_char);
        
        switch(command_char) {
            case 'm':
                printf("How many steps? ");
                scanf("%d", &move_count);
                // Validate move_count is positive
                // Execute moves with front_is_clear() checking
                break;
            case 't':
                karel_turn_left();
                printf("Karel turned left\n");
                break;
            case 'p':
                karel_put_beeper();
                printf("Beeper placed\n");
                break;
            case 'g':
                if(beepers_present()) {
                    karel_pick_beeper();
                    printf("Beeper collected\n");
                } else {
                    printf("No beeper here!\n");
                }
                break;
            case 's':
                printf("Karel Status:\n");
                printf("Position: (%d, %d)\n", karel.x, karel.y);
                printf("Direction: %s\n", DIRECTION_NAMES[karel.direction]);
                printf("Beepers in bag: %d\n", karel.bag_beepers);
                break;
        }
        */
        
        lastCommandTime = timeSec;
    }
}
