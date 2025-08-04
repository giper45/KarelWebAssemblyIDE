#include "karel.h"
#include <string.h>
#include <ctype.h>

const char* DIRECTION_NAMES[] = {"Est", "Nord", "Ovest", "Sud"};

// TODO: String arrays for command parsing
// char command_buffer[100];
// char command_word[20];
// char parameter[20];

// TODO: Location names array
// char location_names[10][30] = {
//     "Home Base",
//     "Beeper Storage", 
//     "Workshop",
//     "Garden",
//     "Parking Area"
// };

// TODO: Karel's name and status
// char karel_name[50] = "Karel-2000";
// char current_status[100] = "Ready for commands";
// char last_command[100] = "None";

// TODO: Command history
// char command_history[5][100];
// int history_count = 0;

// TODO: Function to parse command string
// int parse_command(char* input, char* cmd, char* param) {
//     // Split input into command and parameter
//     // Return 1 if successful, 0 if invalid format
// }

// TODO: Function to validate command
// int is_valid_command(char* cmd) {
//     // Check if cmd is one of: "move", "turn", "pick", "put", "goto"
//     // Return 1 if valid, 0 if invalid
// }

// TODO: Function to add command to history
// void add_to_history(char* command) {
//     // Add command to circular buffer history
// }

// TODO: Function to show command history
// void show_history() {
//     // Display recent commands
// }

// TODO: Function to execute parsed command
// void execute_command(char* cmd, char* param) {
//     // Execute the parsed command with parameter
// }

// TODO: Function to get location name
// char* get_location_name(int x, int y) {
//     // Return appropriate location name based on coordinates
// }

void setup() {
    karel_init();
    
    // Add beepers at named locations
    karel_add_beeper(2, 2);  // Home Base
    karel_add_beeper(8, 6);  // Beeper Storage
    karel_add_beeper(5, 4);  // Workshop
    
    printf("Karel String Operations Demo\n");
    printf("============================\n");
    printf("Robot Name: %s\n", "Karel-2000");  // Should use karel_name
    printf("Status: %s\n", "Initializing");   // Should use current_status
    
    // TODO: Initialize strings
    // strcpy(current_status, "Ready for string commands");
    // strcpy(last_command, "System initialization");
}

void draw() {
    canvas_setFillStyleZ("white");
    canvas_fillRect(0, 0, 800, 600);
    drawWalls();
    drawGrid();
    drawBeepers();
    drawKarel();
    drawInfo();
    
    // TODO: Display string-based status information
    // printf("Name: %s | Status: %s\n", karel_name, current_status);
    // printf("Location: %s\n", get_location_name(karel.x, karel.y));
    // printf("Last Command: %s\n", last_command);
}

void loop(double timeSec, double elapsedSec) {
    draw();
    
    static double lastActionTime = 0;
    static int demo_phase = 0;
    
    if (timeSec - lastActionTime > 3.0) {
        
        // TODO: Demonstrate different string operations
        switch(demo_phase % 6) {
            case 0:
                printf("Demo: String command parsing\n");
                // TODO: Parse sample commands like "move 3", "turn left"
                // parse_command("move 3", command_word, parameter);
                break;
                
            case 1:
                printf("Demo: String validation\n");
                // TODO: Validate different command strings
                // is_valid_command("move") should return 1
                // is_valid_command("jump") should return 0
                break;
                
            case 2:
                printf("Demo: String concatenation\n");
                // TODO: Build status messages using strcat
                // strcpy(current_status, "Moving to ");
                // strcat(current_status, get_location_name(karel.x, karel.y));
                break;
                
            case 3:
                printf("Demo: String comparison\n");
                // TODO: Compare location names and commands
                // if(strcmp(get_location_name(karel.x, karel.y), "Home Base") == 0)
                break;
                
            case 4:
                printf("Demo: String length operations\n");
                // TODO: Show string length calculations
                // printf("Karel's name length: %zu\n", strlen(karel_name));
                break;
                
            case 5:
                printf("Demo: Command history\n");
                // TODO: Show command history functionality
                // add_to_history("Demonstration cycle complete");
                // show_history();
                break;
        }
        
        demo_phase++;
        lastActionTime = timeSec;
    }
}
