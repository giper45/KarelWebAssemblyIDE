# Karel WebAssembly IDE

Welcome to the Karel WebAssembly IDE!

## How to use Karel

Karel is a robot that can:
- **Move** in the world
- **Pick up beepers** 
- **Detect obstacles**
- **Change direction**

### Main commands:
- `karel_move()` - Move Karel forward
- `karel_turn_left()` - Turn Karel left  
- `karel_pick_beeper()` - Pick up a beeper
- `front_is_clear()` - Check if the path is clear
- `beepers_present()` - Check if there are beepers

## Simple Exercises

Try these basic exercises to get familiar with Karel:

### Exercise 1: First Steps
```c
// Make Karel move forward and turn left
karel_move();
karel_turn_left();
karel_move();
```

### Exercise 2: Square Movement
```c
// Make Karel move in a square pattern
for(int i = 0; i < 4; i++) {
    karel_move();
    karel_turn_left();
}
```

### Exercise 3: Safe Movement
```c
// Move only if the path is clear
if(front_is_clear()) {
    karel_move();
} else {
    karel_turn_left();
}
```

### Exercise 4: Collect Beepers
```c
// Pick up beepers if present
if(beepers_present()) {
    karel_pick_beeper();
}
karel_move();
```

### Exercise 5: Navigate Around Obstacles
```c
// Turn right (using three left turns)
void karel_turn_right() {
    karel_turn_left();
    karel_turn_left();
    karel_turn_left();
}

// Use the turn right function
karel_turn_right();
karel_move();
```

*Happy programming!* 