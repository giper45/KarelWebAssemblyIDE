# Command Sequence Array

Instead of hardcoding movement sequences, programmers often store commands in arrays for flexibility and reusability. This approach lets you change behavior by modifying data rather than code. In this exercise, Karel must execute a complex movement pattern by reading commands from an array. You'll build a simple command interpreter using enums and arrays, a common pattern in game scripting, automation, macro recording, and even compilers.

Karel starts at position (1,1) facing East, with 3 beepers in his bag. There’s a beeper at (4,2) to pick up, and Karel should place a beeper at (3,4). The goal: execute a sequence of actions to pick up and place beepers, ending at (4,4).

Define your commands using an enum:
```c
enum Command {
    MOVE,
    TURN_LEFT,
    TURN_RIGHT,
    PICK_BEEPER,
    PUT_BEEPER
};
```
Store the sequence in an array:
```c
enum Command commands[] = {
    MOVE, MOVE, TURN_RIGHT, MOVE, PICK_BEEPER,
    TURN_LEFT, MOVE, MOVE, TURN_LEFT, MOVE,
    PUT_BEEPER, TURN_RIGHT, MOVE
};
```
Use a switch statement to interpret each command:
```c
switch (command) {
    case MOVE: karel_move(); break;
    case TURN_LEFT: karel_turn_left(); break;
    // ...
}
```
You’ll need to implement a helper for right turns:
```c
void turn_right() {
    karel_turn_left();
    karel_turn_left();
    karel_turn_left();
}
```
And a function to execute each command:
```c
void execute_command(enum Command cmd) {
    switch (cmd) {
        case MOVE: karel_move(); break;
        case TURN_LEFT: karel_turn_left(); break;
        case TURN_RIGHT: turn_right(); break;
        case PICK_BEEPER: karel_pick_beeper(); break;
        case PUT_BEEPER: karel_put_beeper(); break;
    }
}
```
Finally, loop through the array to execute the sequence:
```c
void execute_sequence(enum Command commands[], int length) {
    for (int i = 0; i < length; i++) {
        execute_command(commands[i]);
    }
}
```
In your `studentCode()`, define the sequence and call `execute_sequence`. Karel should follow the pattern: move forward 2 steps, turn right, move 1, pick up beeper, turn left, move 2, turn left, move 1, put beeper, turn right, move 1.

**Success criteria:**  
- Karel executes the entire sequence correctly  
- Picks up the beeper at (4,2)  
- Places a beeper at (3,4)  
- Uses enums and arrays  
- Ends at (4,4)

**Advanced challenge:**  
Try extending the pattern by using structs for commands with parameters, adding conditional commands (like `PICK_IF_PRESENT`), or supporting loops with `REPEAT_START` and `REPEAT_END`. This makes your interpreter more powerful and closer to real-world scripting systems.

This pattern is widely used in game scripting, automation, macro recording, compilers, and network protocols—representing actions as data makes programs more flexible and easier