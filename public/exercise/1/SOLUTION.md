# Solution: Karel First Steps

## Basic Karel Commands Examples

Here are simple examples showing how to use Karel's basic functions without loops:

### Example 1: Simple Movement
```c
void studentCode() {
    karel_move();           // Move forward one step
    karel_move();           // Move forward another step
    karel_turn_left();      // Turn 90 degrees left
    karel_move();           // Move forward in new direction
}
```

### Example 2: Safe Movement with Checks
```c
void studentCode() {
    if (front_is_clear()) {
        karel_move();       // Only move if path is clear
    }
    
    if (front_is_clear()) {
        karel_move();       // Move again if possible
    } else {
        karel_turn_left();  // Turn if blocked
    }
}
```

### Example 3: Working with Beepers
```c
void studentCode() {
    karel_move();           // Move to position with beeper
    karel_move();           // Move another step
    
    if (beepers_present()) {
        karel_pick_beeper(); // Pick up beeper if one exists
        printf("Picked up a beeper!\n");
    }
    
    karel_turn_left();      // Turn left
    karel_move();           // Move in new direction
    
    if (beepers_in_bag()) {
        karel_put_beeper();  // Place beeper if we have one
        printf("Placed a beeper!\n");
    }
}
```

### Example 4: Navigate Around Obstacle
```c
void studentCode() {
    // Try to move forward
    if (front_is_clear()) {
        karel_move();
    } else {
        // Hit a wall, go around it
        karel_turn_left();   // Turn left
        karel_move();        // Move up
        karel_turn_left();   // Turn left again (now facing west)
        karel_turn_left();   // Turn left again (now facing south)
        karel_turn_left();   // Complete turn (now facing east again)
        karel_move();        // Move forward past obstacle
    }
}
```

### Example 5: Simple Navigation Pattern
```c
void studentCode() {
    // Move in an L-shape pattern
    karel_move();           // Move east
    karel_move();           // Move east again
    karel_turn_left();      // Turn to face north
    karel_move();           // Move north
    karel_move();           // Move north again
    
    // Check current position
    printf("Karel is at position (%d, %d)\n", karel_get_x(), karel_get_y());
}
```

### Available Functions:
- `karel_move()` - Move forward one step
- `karel_turn_left()` - Turn 90 degrees counter-clockwise
- `karel_pick_beeper()` - Pick up a beeper at current position
- `karel_put_beeper()` - Place a beeper at current position
- `front_is_clear()` - Check if Karel can move forward
- `beepers_present()` - Check if there's a beeper at current position
- `beepers_in_bag()` - Check if Karel has beepers in bag
- `karel_get_x()`, `karel_get_y()` - Get current position coordinates