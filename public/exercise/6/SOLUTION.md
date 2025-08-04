# Solution: Karel Input Processing

## Solution Explanation
This exercise demonstrates how to create an interactive Karel control system using scanf for input and printf for formatted output.

## Complete Solution
```c
#include "karel.h"

const char* DIRECTION_NAMES[] = {"Est", "Nord", "Ovest", "Sud"};

int user_command = 0;
int move_count = 1;
char command_char = 'h';
int target_x = 1, target_y = 1;

void show_help() {
    printf("\n=== Karel Command Help ===\n");
    printf("h - Show this help\n");
    printf("m - Move Karel (specify steps)\n");
    printf("t - Turn Karel left\n");
    printf("p - Put beeper at current position\n");
    printf("g - Get beeper from current position\n");
    printf("s - Show Karel's current status\n");
    printf("c - Move to coordinates (x,y)\n");
    printf("q - Quit\n");
    printf("=========================\n\n");
}

void show_status() {
    printf("\n=== Karel Status ===\n");
    printf("Position: (%d, %d)\n", karel.x, karel.y);
    printf("Facing: %s\n", DIRECTION_NAMES[karel.direction]);
    printf("Beepers in bag: %d\n", karel.bag_beepers);
    printf("Front clear: %s\n", front_is_clear() ? "Yes" : "No");
    printf("==================\n\n");
}

int validate_move_count(int count) {
    if (count < 1 || count > 20) {
        printf("Error: Move count must be between 1 and 20\n");
        return 0;
    }
    return 1;
}

int validate_coordinates(int x, int y) {
    if (x < 1 || x > WORLD_WIDTH || y < 1 || y > WORLD_HEIGHT) {
        printf("Error: Coordinates must be within world bounds\n");
        printf("Valid range: x(1-%d), y(1-%d)\n", WORLD_WIDTH, WORLD_HEIGHT);
        return 0;
    }
    return 1;
}

void execute_moves(int count) {
    int successful_moves = 0;
    
    for (int i = 0; i < count; i++) {
        if (front_is_clear()) {
            karel_move();
            successful_moves++;
        } else {
            printf("Blocked after %d moves - turning left\n", successful_moves);
            karel_turn_left();
            break;
        }
    }
    
    printf("Completed %d out of %d requested moves\n", successful_moves, count);
}

void process_command() {
    printf("Enter command (h for help): ");
    scanf(" %c", &command_char);
    
    switch(command_char) {
        case 'h':
            show_help();
            break;
            
        case 'm':
            printf("How many steps? ");
            scanf("%d", &move_count);
            if (validate_move_count(move_count)) {
                execute_moves(move_count);
            }
            break;
            
        case 't':
            karel_turn_left();
            printf("Karel turned left - now facing %s\n", 
                   DIRECTION_NAMES[karel.direction]);
            break;
            
        case 'p':
            karel_put_beeper();
            printf("Beeper placed at (%d, %d)\n", karel.x, karel.y);
            break;
            
        case 'g':
            if (beepers_present()) {
                karel_pick_beeper();
                printf("Beeper collected from (%d, %d)\n", karel.x, karel.y);
            } else {
                printf("No beeper at current position (%d, %d)\n", 
                       karel.x, karel.y);
            }
            break;
            
        case 's':
            show_status();
            break;
            
        case 'c':
            printf("Enter target coordinates (x y): ");
            scanf("%d %d", &target_x, &target_y);
            if (validate_coordinates(target_x, target_y)) {
                printf("Moving to (%d, %d)...\n", target_x, target_y);
                // Simple navigation logic would go here
            }
            break;
            
        case 'q':
            printf("Goodbye!\n");
            break;
            
        default:
            printf("Unknown command '%c'. Type 'h' for help.\n", command_char);
            break;
    }
}

void loop(double timeSec, double elapsedSec) {
    draw();
    
    static double lastTime = 0;
    static int initialized = 0;
    
    if (!initialized) {
        show_help();
        initialized = 1;
    }
    
    if (timeSec - lastTime > 2.0) {
        process_command();
        lastTime = timeSec;
    }
}
```

## Key Learning Points

### Input Validation Techniques
```c
// Always validate numeric input ranges
if (count < 1 || count > 20) {
    printf("Error: Invalid range\n");
    return 0;
}

// Validate coordinates within world bounds
if (x < 1 || x > WORLD_WIDTH || y < 1 || y > WORLD_HEIGHT) {
    printf("Error: Out of bounds\n");
    return 0;
}
```

### Format Specifiers for Output
- `%d` - integers with optional width: `%5d`
- `%c` - single characters
- `%s` - strings with alignment: `%-10s`
- `%.2f` - floating point with precision
- `%p` - pointer addresses

### Input Reading Best Practices
- Use space before `%c` in scanf: `scanf(" %c", &char_var)`
- Check return values: `if (scanf("%d", &num) != 1) { ... }`
- Clear input buffer when necessary
- Provide clear prompts for user guidance

## Expected Interaction
```
Enter command (h for help): m
How many steps? 3
Completed 3 out of 3 requested moves

Enter command (h for help): s
=== Karel Status ===
Position: (4, 1)
Facing: Est
Beepers in bag: 0
Front clear: Yes
==================
```
