# Solution: Repeat Path
This exercise demonstrates how to use **enums** and **state machines** to create clean, maintainable repetitive behavior. Karel performs a forward-backward movement pattern 4 times using enum-based phases to control the sequence precisely.

## Complete Solution
```c
enum Phase {
    MOVING_FORWARD,
    TURNING_AROUND,
    MOVING_BACKWARD,
    RESETTING_DIRECTION,
    COMPLETE
};

void studentCode() {
    bool exerciseComplete = false;
    int currentIteration = 0;
    enum Phase currentPhase = MOVING_FORWARD;
    int steps = 0;
    while (!exerciseComplete)
        if (!exerciseComplete && currentIteration < 4) {
            switch (currentPhase) {
                case MOVING_FORWARD:
                    if (steps == 0) {
                        printf("Starting iteration %d...\n", currentIteration + 1);
                    }
                    if (steps < 3 && front_is_clear()) {
                        karel_move();
                        steps++;
                        printf("Moving forward: Step %d to (%d,%d)\n", steps, karel_get_x(), karel_get_y());
                    } else {
                        printf("Turning around to face West...\n");
                        currentPhase = TURNING_AROUND;
                        steps = 0;
                    }
                    break;
                    
                case TURNING_AROUND:
                    if (steps < 2) {
                        karel_turn_left();
                        steps++;
                    } else {
                        currentPhase = MOVING_BACKWARD;
                        steps = 0;
                    }
                    break;
                    
                case MOVING_BACKWARD:
                    if (steps < 3 && front_is_clear()) {
                        karel_move();
                        steps++;
                        printf("Moving backward: Step %d to (%d,%d)\n", steps, karel_get_x(), karel_get_y());
                    } else {
                        printf("Turning around to face East...\n");
                        currentPhase = RESETTING_DIRECTION;
                        steps = 0;
                    }
                    break;
                    
                case RESETTING_DIRECTION:
                    if (steps < 2) {
                        karel_turn_left();
                        steps++;
                    } else {
                        printf("Iteration %d complete!\n", currentIteration + 1);
                        currentIteration++;
                        currentPhase = MOVING_FORWARD;
                        steps = 0;
                    }
                    break;
                    
                case COMPLETE:
                    break;
            }
        } else if (!exerciseComplete) {
            printf("All 4 iterations completed! Karel back at starting position.\n");
            printf("Final position: (%d,%d) facing %s\n", karel_get_x(), karel_get_y(), DIRECTION_NAMES[karel_get_direction()]);
            exerciseComplete = true;
        }
    printf("Exercise completed!");
}
```

### 1. **Why Use Enums Instead of Numbers?**
```c
//  Hard to understand
static int phase = 0;  // What does 0 mean?
if (phase == 2) { ... }

// Self-documenting
enum Phase currentPhase = MOVING_FORWARD;
if (currentPhase == MOVING_BACKWARD) { ... }
```

**Benefits:**
- **Readable**: `MOVING_FORWARD` is clearer than `0`
- **Type-safe**: Compiler catches invalid phase assignments
- **Maintainable**: Easy to add new phases or reorder them

### 2. **State Machine Pattern**
Each phase handles one specific task:
1. **MOVING_FORWARD**: Move 3 cells east
2. **TURNING_AROUND**: Turn 180° to face west  
3. **MOVING_BACKWARD**: Move 3 cells west (back to start)
4. **RESETTING_DIRECTION**: Turn 180° to face east again

### 3. **Buffer-Friendly Movement**
```c
karel_move();
return; // Exit immediately to respect timing
```
This creates smooth animation by processing one action per frame.

## Movement Pattern Analysis

**Complete Cycle (1 iteration):**
```
Start: (1,1) facing East
→ Forward:  (1,1) → (2,1) → (3,1) → (4,1)
→ Turn:     Face West
→ Backward: (4,1) → (3,1) → (2,1) → (1,1)  
→ Reset:    Face East
```

**Total per iteration:** 6 moves + 4 turns = 10 actions
**4 iterations:** 24 moves + 16 turns = 40 actions

## Alternative Solution: Path-Based Approach
An alternative solution could use a path-based approach, where Karel follows a predefined set of coordinates and directions. This method is more complex but allows for precise control over Karel's movements.


```c
void studentCode() {
    static bool exerciseComplete = false;
    static int currentIteration = 0;
    static int pathStep = 0;
    
    // Define the complete path for one iteration
    static int targetX[] = {2, 3, 4, 4, 4, 3, 2, 1, 1}; // X coordinates to visit
    static int targetY[] = {1, 1, 1, 1, 1, 1, 1, 1, 1}; // Y coordinates (all same row)
    static int targetDir[] = {0, 0, 0, 1, 2, 2, 2, 2, 0}; // Directions: 0=East, 1=North, 2=West
    static int pathLength = 9;
    
    while (!exerciseComplete && currentIteration < 4) {
        if (pathStep == 0) {
            printf("Starting iteration %d...\n", currentIteration + 1);
        }
        
        // Check if we need to move to target position
        if (karel_get_x() != targetX[pathStep] || karel_get_y() != targetY[pathStep]) {
            if (karel_get_x() < targetX[pathStep] && front_is_clear()) {
                karel_move();
                printf("Moving to (%d,%d)\n", karel_get_x(), karel_get_y());
            } else if (karel_get_x() > targetX[pathStep] && front_is_clear()) {
                karel_move();
                printf("Moving to (%d,%d)\n", karel_get_x(), karel_get_y());
            }
        }
        
        // Check if we need to turn to target direction
        if (karel_get_direction() != targetDir[pathStep]) {
            karel_turn_left();
        }
        
        // Move to next step in path
        pathStep++;
        
        // Check if iteration is complete
        if (pathStep >= pathLength) {
            printf("Iteration %d complete!\n", currentIteration + 1);
            currentIteration++;
            pathStep = 0;
            
            if (currentIteration >= 4) {
                printf("All 4 iterations completed! Karel back at starting position.\n");
                exerciseComplete = true;
            }
        }
    }
}

```

## Comparison: State Machine vs Path-Based

### State Machine Approach (Recommended)
```c
 Clear phases: MOVING_FORWARD → TURNING_AROUND → MOVING_BACKWARD
 Easy to understand logic flow
 Simple to modify behavior
 Self-documenting code
```

### Path-Based Approach
```c
 Precise control over exact positions
 Good for complex routes
 Data-driven (easy to change path by modifying arrays)
 Harder to understand at first glance
 More setup code required
```

### When to Use Each Approach:

**State Machine:** 
- Simple, repetitive patterns
- When phases are distinct and logical
- For learning fundamental programming concepts

**Path-Based:**
- Complex routes with many waypoints
- When you need exact position control
- For advanced pathfinding algorithms

### 5. **Algorithm Complexity Analysis**

#### **Time Complexity:**
- **Total Operations**: O(4 × (3 + 2 + 3 + 2)) = O(40) operations
- **Per Iteration**: O(10) operations (6 moves + 4 turns)
- **Scaling**: O(n × m) where n = iterations, m = distance per iteration

#### **Space Complexity:**
- **Memory Usage**: O(1) - only uses constant static variables
- **No Recursion**: Iterative solution with fixed memory footprint
- **Efficient**: Memory usage independent of iteration count

#### **Movement Efficiency:**
```
Total distance covered: 24 cells (4 iterations × 6 cells per iteration)
Net displacement: 0 cells (returns to start)
Turn efficiency: 16 turns (minimum required for pattern)
```

## Common Mistakes to Avoid

###  Using Magic Numbers
```c
static int phase = 0;  // What does 0 mean?
if (phase == 2) { ... } // What happens in phase 2?
```

###  Using Descriptive Enums
```c
enum Phase currentPhase = MOVING_FORWARD;
if (currentPhase == MOVING_BACKWARD) { ... }
```

###  Forgetting Return Statements
```c
karel_move();
karel_move(); // This executes immediately, no animation!
```

###  Respecting Buffer Timing
```c
karel_move();
return; // Let animation play, continue next frame
```

###  Incorrect Turn Count
```c
karel_turn_left(); // Only 90°, not 180°!
```

###  Complete Turn Around
```c
karel_turn_left(); // 90°
karel_turn_left(); // Another 90° = 180° total
```

## Key Programming Lessons

### 1. **State Machines Make Complex Behavior Simple**
Instead of trying to do everything at once, break it into clear steps:
- Each phase has one job
- Transitions between phases are explicit
- Easy to debug and modify

### 2. **Enums Improve Code Quality**
- **Self-documenting**: Code explains what it does
- **Type-safe**: Compiler helps catch errors
- **Maintainable**: Easy to add new states

### 3. **Timing Matters in Real Systems**
- Real robots can't do everything instantly
- Buffer systems prevent overwhelming the hardware
- `return` statements create smooth, visible animations

## Additonal Challenges

### Change the Movement Pattern
- Change iterations from 4 to 6
- Change distance from 3 to 5 cells
- Add beeper placement at furthest point

### Change the Direction
- Variable distance each iteration (1, 2, 3, 4 cells)
- Create a square pattern instead of linear
- Add diagonal movement patterns