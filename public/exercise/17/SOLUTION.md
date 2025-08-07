# Solution: Command Sequence Array

## Solution Explanation
This exercise demonstrates the command pattern using enums and arrays. Commands are represented as data, making the program more flexible and easier to modify.

## Complete Solution
```c
enum Command {
    MOVE,
    TURN_LEFT,
    TURN_RIGHT,
    PICK_BEEPER,
    PUT_BEEPER
};

void turn_right() {
    karel_turn_left();
    karel_turn_left();
    karel_turn_left();
}

void execute_command(enum Command cmd) {
    switch (cmd) {
        case MOVE:
            if (front_is_clear()) {
                karel_move();
                printf("Moved to (%d, %d)\n", karel_get_x(), karel_get_y());
            } else {
                printf("Cannot move - wall ahead!\n");
            }
            break;
            
        case TURN_LEFT:
            karel_turn_left();
            printf("Turned left - now facing %s\n", DIRECTION_NAMES[karel_get_direction()]);
            break;
            
        case TURN_RIGHT:
            turn_right();
            printf("Turned right - now facing %s\n", DIRECTION_NAMES[karel_get_direction()]);
            break;
            
        case PICK_BEEPER:
            if (beepers_present()) {
                karel_pick_beeper();
                printf("Picked up beeper at (%d, %d)\n", karel_get_x(), karel_get_y());
            } else {
                printf("No beeper to pick up at (%d, %d)\n", karel_get_x(), karel_get_y());
            }
            break;
            
        case PUT_BEEPER:
            if (karel_get_bag_beepers() > 0) {
                karel_put_beeper();
                printf("Placed beeper at (%d, %d)\n", karel_get_x(), karel_get_y());
            } else {
                printf("No beepers in bag to place!\n");
            }
            break;
            
        default:
            printf("Unknown command!\n");
            break;
    }
}

void execute_sequence(enum Command commands[], int length) {
    for (int i = 0; i < length; i++) {
        printf("Step %d: ", i + 1);
        execute_command(commands[i]);
    }
}

void studentCode() {
    static bool sequenceComplete = false;
    
    if (!sequenceComplete) {
        enum Command sequence[] = {
            MOVE, MOVE, TURN_RIGHT, MOVE, PICK_BEEPER,
            TURN_LEFT, MOVE, MOVE, TURN_LEFT, MOVE,
            PUT_BEEPER, TURN_RIGHT, MOVE
        };
        
        int length = sizeof(sequence) / sizeof(sequence[0]);
        
        printf("Starting command sequence execution...\n");
        execute_sequence(sequence, length);
        
        sequenceComplete = true;
        printf("Command sequence completed!\n");
        printf("Final position: (%d, %d)\n", karel_get_x(), karel_get_y());
    }
}
```

## Alternative Solution (State-Based Real-Time Execution)
```c
void studentCode() {
    static enum Command sequence[] = {
        MOVE, MOVE, TURN_RIGHT, MOVE, PICK_BEEPER,
        TURN_LEFT, MOVE, MOVE, TURN_LEFT, MOVE,
        PUT_BEEPER, TURN_RIGHT, MOVE
    };
    static int current_command = 0;
    static bool sequenceComplete = false;
    
    int length = sizeof(sequence) / sizeof(sequence[0]);
    
    while (!sequenceComplete && current_command < length) {
        printf("Step %d: ", current_command + 1);
        execute_command(sequence[current_command]);
        current_command++;
        
        if (current_command >= length) {
            sequenceComplete = true;
            printf("Command sequence completed!\n");
        }
    }
}
```

## Advanced Solutions
Try these advanced variations to enhance your understanding:
* 1. Command with Parameters, where commands can take parameters like distance or direction.
* 2. Conditional Commands, where commands execute only if certain conditions are met (e.g., `PICK_IF_PRESENT`).
* 3. Loop Commands, allowing commands to repeat a specified number of times or until a condition is met.

### 1. Command with Parameters
```c
struct ParameterizedCommand {
    enum Command type;
    int parameter;
};

void execute_parameterized_command(struct ParameterizedCommand cmd) {
    switch (cmd.type) {
        case MOVE:
            for (int i = 0; i < cmd.parameter && front_is_clear(); i++) {
                karel_move();
            }
            break;
        case TURN_LEFT:
            for (int i = 0; i < cmd.parameter; i++) {
                karel_turn_left();
            }
            break;
        // ... other cases
    }
}

// Usage:
struct ParameterizedCommand sequence[] = {
    {MOVE, 3},      // Move 3 steps
    {TURN_LEFT, 2}, // Turn left twice (turn around)
    {MOVE, 1}       // Move 1 step
};
```

### 2. Command Interpreter with Error Handling
```c
typedef enum {
    SUCCESS,
    WALL_BLOCKED,
    NO_BEEPER,
    BAG_EMPTY
} CommandResult;

CommandResult execute_command_safe(enum Command cmd) {
    switch (cmd) {
        case MOVE:
            if (!front_is_clear()) return WALL_BLOCKED;
            karel_move();
            return SUCCESS;
            
        case PICK_BEEPER:
            if (!beepers_present()) return NO_BEEPER;
            karel_pick_beeper();
            return SUCCESS;
            
        case PUT_BEEPER:
            if (karel_get_bag_beepers() <= 0) return BAG_EMPTY;
            karel_put_beeper();
            return SUCCESS;
            
        default:
            execute_command(cmd); // Safe commands
            return SUCCESS;
    }
}
```

### 3. Loop Commands
```c
enum ExtendedCommand {
    MOVE, TURN_LEFT, TURN_RIGHT, PICK_BEEPER, PUT_BEEPER,
    LOOP_START, LOOP_END
};

void execute_with_loops(enum ExtendedCommand commands[], int length) {
    int i = 0;
    while (i < length) {
        if (commands[i] == LOOP_START) {
            int loop_start = i + 1;
            int loop_count = commands[i + 1]; // Next command is repeat count
            int depth = 1;
            int loop_end = i + 2;
            
            // Find matching LOOP_END
            while (depth > 0) {
                if (commands[loop_end] == LOOP_START) depth++;
                if (commands[loop_end] == LOOP_END) depth--;
                loop_end++;
            }
            
            // Execute loop body multiple times
            for (int rep = 0; rep < loop_count; rep++) {
                for (int j = loop_start + 1; j < loop_end - 1; j++) {
                    execute_command((enum Command)commands[j]);
                }
            }
            
            i = loop_end;
        } else {
            execute_command((enum Command)commands[i]);
            i++;
        }
    }
}
```

## Key Programming Concepts Demonstrated

### 1. Enumerated Types
```c
enum Command { MOVE, TURN_LEFT, TURN_RIGHT };
// Automatically assigns: MOVE=0, TURN_LEFT=1, TURN_RIGHT=2
```

### 2. Arrays of Enums
```c
enum Command sequence[] = {MOVE, TURN_LEFT, MOVE};
// Creates array of enum values
```

### 3. Switch Statements
```c
switch (command) {
    case MOVE:        // Execute when command == MOVE
        karel_move();
        break;        // Exit switch
    case TURN_LEFT:   // Execute when command == TURN_LEFT
        karel_turn_left();
        break;
}
```

### 4. Array Size Calculation
```c
int length = sizeof(sequence) / sizeof(sequence[0]);
// Works for arrays declared in same scope
```

### 5. Command Pattern
- **Encapsulation**: Commands as data objects
- **Flexibility**: Easy to modify behavior by changing data
- **Reusability**: Same execution engine for different sequences

## Real-World Applications

### Game Development
```c
// NPC behavior scripting
enum NPCAction { WALK, ATTACK, DEFEND, CAST_SPELL };
enum NPCAction ai_sequence[] = {WALK, WALK, ATTACK, DEFEND};
```

### Robotics
```c
// Robot assembly line commands
enum RobotCommand { GRAB, MOVE_TO, PLACE, ROTATE };
enum RobotCommand assembly_sequence[] = {GRAB, MOVE_TO, ROTATE, PLACE};
```

### User Interface
```c
// Macro recording in editors
enum UICommand { TYPE_TEXT, PRESS_KEY, CLICK_MOUSE };
// Record user actions as command sequence
```

### Network Protocols
```c
// HTTP-like protocol commands
enum Protocol { GET, POST, PUT, DELETE };
enum Protocol request_sequence[] = {GET, POST, PUT};
```

This exercise teaches fundamental concepts for building flexible, data-driven systems where behavior is determined by data rather than hardcoded logic.
