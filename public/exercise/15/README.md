# Command Sequence Array

## Objective
Learn to use arrays to store command sequences and execute them programmatically. This exercise introduces enumerated types and command pattern programming.

## Background
Instead of hardcoding movement sequences, programmers often store commands in arrays for flexibility and reusability. This approach allows you to change behavior by modifying data rather than code.

## Your Task
Karel needs to execute a complex movement pattern by reading commands from an array. You'll implement a command interpreter that can execute different types of actions.

### Command Types
Define these commands using an enum:
- `MOVE` - Move forward one step
- `TURN_LEFT` - Turn 90 degrees counter-clockwise
- `TURN_RIGHT` - Turn 90 degrees clockwise (3 left turns)
- `PICK_BEEPER` - Pick up a beeper if present
- `PUT_BEEPER` - Place a beeper if available

### Target Sequence
Execute this sequence to create a pattern:
1. Move forward 2 steps
2. Turn right
3. Move forward 1 step
4. Pick up beeper
5. Turn left
6. Move forward 2 steps
7. Turn left
8. Move forward 1 step
9. Put beeper
10. Turn right
11. Move forward 1 step

## Programming Concepts You'll Learn

### 1. Enumerated Types (enum)
```c
enum Command {
    MOVE,
    TURN_LEFT,
    TURN_RIGHT,
    PICK_BEEPER,
    PUT_BEEPER
};
```

### 2. Array of Enums
```c
enum Command commands[] = {
    MOVE, MOVE, TURN_RIGHT, MOVE, PICK_BEEPER, ...
};
```

### 3. Switch Statements
```c
switch (command) {
    case MOVE:
        karel_move();
        break;
    case TURN_LEFT:
        karel_turn_left();
        break;
    // ...
}
```

### 4. Command Pattern
A programming design pattern where commands are represented as data objects.

## Functions You'll Need to Implement

### 1. turn_right()
```c
void turn_right() {
    // Implement right turn using three left turns
}
```

### 2. execute_command()
```c
void execute_command(enum Command cmd) {
    // Use switch statement to execute the appropriate action
}
```

### 3. execute_sequence()
```c
void execute_sequence(enum Command commands[], int length) {
    // Execute all commands in the array
}
```

## Setup Information
- Karel starts at position (1,1) facing East
- Karel has 3 beepers in his bag
- There's a beeper at position (4,2) to pick up
- Karel should place a beeper at position (3,4)

## Success Criteria
- Karel executes the entire command sequence correctly
- Karel picks up the beeper at (4,2)
- Karel places a beeper at (3,4)
- Your solution uses enums and arrays
- Karel ends up at position (4,4)

## Code Structure Template
```c
enum Command {
    MOVE,
    TURN_LEFT,
    TURN_RIGHT,
    PICK_BEEPER,
    PUT_BEEPER
};

void turn_right() {
    // TODO: Implement
}

void execute_command(enum Command cmd) {
    switch (cmd) {
        case MOVE:
            // TODO: Implement
            break;
        case TURN_LEFT:
            // TODO: Implement
            break;
        // Add other cases...
    }
}

void execute_sequence(enum Command commands[], int length) {
    // TODO: Implement loop to execute all commands
}

void studentCode() {
    enum Command sequence[] = {
        MOVE, MOVE, TURN_RIGHT, MOVE, PICK_BEEPER,
        TURN_LEFT, MOVE, MOVE, TURN_LEFT, MOVE,
        PUT_BEEPER, TURN_RIGHT, MOVE
    };
    
    int length = sizeof(sequence) / sizeof(sequence[0]);
    execute_sequence(sequence, length);
}
```

## Advanced Challenge
Once you complete the basic version, try these extensions:

### 1. Command with Parameters
```c
struct Command {
    enum CommandType type;
    int parameter;  // e.g., number of steps to move
};
```

### 2. Conditional Commands
Add commands like `PICK_IF_PRESENT` that only execute if conditions are met.

### 3. Loop Commands
Add `REPEAT_START` and `REPEAT_END` to create loops within the command sequence.

## Why This Matters
This pattern is used in:
- **Game scripting** - NPCs following scripted behaviors
- **Automation** - Industrial robots executing work sequences
- **User interfaces** - Macro recording and playback
- **Compilers** - Intermediate code representation
- **Network protocols** - Command sequences in communication

The ability to represent actions as data makes programs more flexible and easier to modify.
