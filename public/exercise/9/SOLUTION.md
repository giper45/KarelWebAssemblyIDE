# Solution: Swap Beeper
This exercise demonstrates a simplified multi-phase algorithm using enums for better code readability. Karel must find a beeper, pick it up, then find an empty location to place it. The solution uses a state machine pattern with three distinct phases.


## Complete Solution
```c
enum Phase {
  SEARCHING_BEEPER,
  SEARCHING_EMPTY_CELL,
  COMPLETE
};
enum Phase {
  SEARCHING_BEEPER,
  SEARCHING_EMPTY_CELL,
  COMPLETE
};

void studentCode() {
    static enum Phase currentPhase = SEARCHING_BEEPER;
    while (currentPhase != COMPLETE)
    {
        switch (currentPhase) {
        case SEARCHING_BEEPER:
            // Search for beeper logic
            printf("Phase 1: Searching for beeper...\n");
            if (!beepers_present() && front_is_clear()) {
                karel_move();
            }
            if (beepers_present()) {
                karel_pick_beeper();
                currentPhase = SEARCHING_EMPTY_CELL;
                karel_move(); // Move immediately after pickup
            }
            break;
        case SEARCHING_EMPTY_CELL:
            printf("Phase 2: Searching for empty cell...\n");
            if (beepers_present() && front_is_clear()) {
                karel_move();
                
            }
            if (!beepers_present()) {
                printf("Empty cell found - placing beeper!\n");
                karel_put_beeper();
                currentPhase = COMPLETE;
                
            }
            break;
        case COMPLETE:
            printf("Phase 3: Operation complete!\n");
            break;
        }
        
    }
        
}


```
### Code Explanation
In C, state machines can be implemented using enums to represent different states, making the code more organized and easier to follow.
The following enum:
```c
enum Phase {
  SEARCHING_BEEPER,
  SEARCHING_EMPTY_CELL,
  COMPLETE
};
```
defines the three phases of Karel's operation:
- `SEARCHING_BEEPER`: Karel is looking for the first beeper to pick up.
- `SEARCHING_EMPTY_CELL`: Karel has picked up the beeper and is now searching for the first empty cell to place it.
- `COMPLETE`: Karel has successfully placed the beeper and the operation is finished.

The switch statement is used in C to control the flow of the program based on the current phase. 
It is possible to combine the enum with a switch statement to implement the logic for each phase:
```c
switch (currentPhase) {
    case SEARCHING_BEEPER:
        // Logic for searching beeper
        break;
    case SEARCHING_EMPTY_CELL:
        // Logic for searching empty cell
        break;
    case COMPLETE:
        // Logic for completion
        break;
}
```

We can implement this logic inside a while loop that continues until the operation is complete. The loop will check the current phase and execute the corresponding logic for searching for a beeper or an empty cell, or completing the operation.

**Why Enums Are Better:**
- **Type Safety**: Compiler prevents invalid phase values
- **Readability**: `SEARCHING_BEEPER` is clearer than `phase == 1`
- **Maintainability**: Easy to add new phases or reorder them
- **Self-Documenting**: Code explains what each phase does


### **Phase 1: SEARCHING_BEEPER - Detailed Breakdown**

```c
if (!beepers_present() && front_is_clear()) {
    karel_move();
}
if (beepers_present()) {
    karel_pick_beeper();
    currentPhase = SEARCHING_EMPTY_CELL;
    karel_move(); // Move immediately after pickup
}
```

**Step-by-Step Execution:**
- **Call 1**: Karel at (1,1), `!beepers_present()` = true, `front_is_clear()` = true → Move to (2,1), return
- **Call 2**: Karel at (2,1), `!beepers_present()` = true, `front_is_clear()` = true → Move to (3,1), return  
- **Call 3**: Karel at (3,1), `beepers_present()` = true → Pick beeper, move to (4,1), transition to phase 2

The criteria for moving forward are the following. If there is no beeper present at the current position and the front is clear, Karel will move forward. If a beeper is found, Karel picks it up and transitions to the next phase.


#### Beeper Found - Pickup and Transition**
```c
if (beepers_present()) {
    pickupX = karel_get_x();           // Store pickup location (3,1)
    pickupY = karel_get_y();
    karel_pick_beeper();         // Remove beeper from world
    printf("Beeper found at (%d, %d)! Picking up...\n", pickupX, pickupY);
    phase = SEARCHING_EMPTY_CELL; // State transition
    karel_move();                // Immediate move to next position
}
```

### Phase 2: SEARCHING_EMPTY_CELL - Detailed Breakdown**

```c
if (beepers_present() && front_is_clear()) {
    karel_move();
}
if (!beepers_present()) {
    printf("Empty cell found - placing beeper!\n");
    karel_put_beeper();
    currentPhase = COMPLETE;
}
```

**Step-by-Step Execution from (4,1):**
- **Call 1**: Karel at (4,1), `beepers_present()` = true → Move to (5,1), return
- **Call 2**: Karel at (5,1), `beepers_present()` = true → Move to (6,1), return
- **Call 3**: Karel at (6,1), `beepers_present()` = true → Move to (7,1), return
- **Call 4**: Karel at (7,1), `beepers_present()` = false → Place beeper, transition to COMPLETE

**Key Logic:**
- **Phase 1**: `if (!beepers_present())` - search for a beeper
- **Phase 2**: `if (beepers_present())` - search for an empty cell

In this phase, Karel continues to move forward as long as there are beepers present and the front is clear. When it finds an empty cell, it places the beeper and transitions to the COMPLETE phase.

#### **Beeper Placement and Completion**
```c
printf("Empty cell found - placing beeper!\n");
karel_put_beeper();      // Place beeper at (7,1)
currentPhase = COMPLETE; // Final state transition
```

In this part, Karel places the beeper at the first empty cell it finds and transitions to the COMPLETE phase, indicating that the operation is finished.

