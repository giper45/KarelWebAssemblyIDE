# Solution: Avoid Obstacles

## Solution Explanation
This exercise teaches obstacle navigation using a systematic avoidance algorithm that allows Karel to bypass walls by temporarily moving to a parallel path.

## Solution
```c
// Helper function to turn right (3 left turns)
void turn_right() {
    karel_turn_left();
    karel_turn_left();
    karel_turn_left();
}

void studentCode() {
    static bool missionComplete = false;
    static bool obstacleBypassed = false;
    
    if (!missionComplete) {
        // Check if front is clear and facing east (normal movement)
        if (front_is_clear() && facing_east()) {
            karel_move();
        }
        // If facing north and front is clear, turn right to face east
        else if (front_is_clear() && facing_north()) {
            turn_right();
        }
        // If blocked while facing east and haven't bypassed obstacle yet
        else if (!front_is_clear() && facing_east() && !obstacleBypassed) {
            karel_turn_left();  // Turn left to face north
            karel_move();       // Move up to bypass obstacle
            obstacleBypassed = true;
        }
        // If bypassed obstacle and blocked again (reached end)
        else if (obstacleBypassed && !front_is_clear() && facing_east()) {
            printf("Mission completed!");
            missionComplete = true;
        }
        if (!missionComplete) {
            printf("Position: (%d, %d) | Direction: %s\n", 
                karel_get_x(), karel_get_y(), DIRECTION_NAMES[karel_get_direction()]);
        }
    } 
}
```

## Key Concepts Demonstrated

### 1. **State-Based Navigation**
```c
static bool obstacleBypassed = false;
// Use state variable to track obstacle avoidance progress
```

### 2. **Directional Conditional Logic**
```c
if (front_is_clear() && facing_east()) {
    karel_move();  // Normal forward movement
} else if (front_is_clear() && facing_north()) {
    turn_right();  // Reorient to continue eastward
}
```

### 3. **Obstacle Detection and Response**
```c
if (!front_is_clear() && facing_east() && !obstacleBypassed) {
    karel_turn_left();  // Turn north to bypass
    karel_move();       // Move up
    obstacleBypassed = true;  // Mark bypass in progress
}
```

### 4. **Mission Completion Detection**
```c
if (obstacleBypassed && !front_is_clear() && facing_east()) {
    missionComplete = true;  // End reached after bypass
}
```

## How It Works

1. **Normal Movement**: Karel moves east when the path is clear
2. **Reorientation**: When facing north with clear path, turn to face east
3. **Obstacle Bypass**: When blocked facing east, turn north and move up
4. **Completion**: After bypassing at least one obstacle, if blocked again, mission is complete

## Algorithm Logic

The solution uses a simplified state machine approach:
- **obstacleBypassed**: Tracks whether Karel has encountered and bypassed an obstacle
- **Directional checks**: Combines movement direction with path clearance
- **Conditional responses**: Different actions based on current state and conditions

## Simplified Avoidance Sequence

```
Example execution with obstacle at position 3:

1. Start at (1,1) facing East
2. karel_move() → Move to (2,1) 
3. front_is_clear() && facing_east() → Move to (3,1) but blocked
4. !front_is_clear() && facing_east() && !obstacleBypassed → 
   - karel_turn_left() → Now facing North
   - karel_move() → Move to (2,2)
   - obstacleBypassed = true
5. front_is_clear() && facing_north() → 
   - turn_right() → Now facing East
6. Continue until blocked again → Mission complete
```

## Expected Output

```
Position: (1, 1) | Direction: Est
Position: (2, 1) | Direction: Est  
Position: (2, 2) | Direction: Nord
Position: (2, 2) | Direction: Est
Position: (3, 2) | Direction: Est
Position: (4, 2) | Direction: Est
...
Mission completed!
Position: (10, 2) | Direction: Est
```

## Debugging Tips
1. **Track state variables** - monitor `obstacleBypassed` flag changes
2. **Verify directional conditions** - ensure `facing_east()` and `facing_north()` work correctly
3. **Test obstacle detection** - confirm `!front_is_clear()` triggers properly
4. **Validate mission completion** - check end condition logic

## Common Mistakes to Avoid
- Not using state variables to track obstacle bypass progress
- Incorrect directional condition combinations
- Missing the `obstacleBypassed` flag update
- Not handling the mission completion condition properly
- Forgetting to check both direction and path clearance together

## Extensions
- Handle multiple obstacles in sequence
- Add visual feedback for each state transition
- Implement more sophisticated pathfinding
- Add error recovery for unexpected situations

## Learning Outcomes
- **State-Based Programming**: Using flags to track program state
- **Compound Conditions**: Combining multiple boolean conditions
- **Simplified Logic**: Achieving complex behavior with minimal code
- **Event-Driven Programming**: Responding to different environmental conditions
