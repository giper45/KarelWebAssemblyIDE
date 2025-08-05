# Solution: Place Beepers

## Solution Explanation
This exercise teaches inventory management and multiple exit conditions by requiring Karel to place beepers strategically while managing limited resources.
Here is the solution code:

```c
void studentCode() {
    
    static bool missionComplete = false;
    static int startingBeepers = 5;  // Remember initial count
    
    if (!missionComplete) {
        // Place beeper at current position if available
        if (beepers_in_bag()) {
            karel_put_beeper();
            int placed = startingBeepers - karel_get_bag_beepers();
            printf("Placed beeper #%d (remaining: %d)\n", placed, karel_get_bag_beepers());
        }
        
        // Check exit conditions
        if (!beepers_in_bag()) {
            missionComplete = true;
            printf("All beepers placed! Bag is now empty.\n");
        } else if (!front_is_clear()) {
            missionComplete = true;
            printf("Wall reached with %d beepers still in bag.\n", karel_get_bag_beepers());
        } else {
            // Continue mission - move forward
            karel_move();
        }
    }
}
```

## Key Concepts Demonstrated

### 1. **Inventory Management**
```c
if (beepers_in_bag()) {
    karel_put_beeper();  // Only place when beepers available
}
```

### 2. **Multiple Exit Conditions**
```c
if (!beepers_in_bag()) {
    // Stop: bag empty
} else if (!front_is_clear()) {
    // Stop: wall reached
} else {
    // Continue: move forward
}
```

### 3. **Resource Tracking**
```c
static int beepersPlaced = 0;
beepersPlaced++;
printf("Total placed: %d, Remaining: %d\n", beepersPlaced, karel_get_bag_beepers());
```

### 4. **Safe Resource Usage**
- Always check `beepers_in_bag()` before `karel_put_beeper()`
- Handle both completion scenarios gracefully
- Provide clear feedback about mission status

## Debugging Tips
1. **Track beeper count** at each step to verify correct placement
2. **Print position and inventory** to monitor progress
3. **Test different starting amounts** (3, 7, 10 beepers)
4. **Verify no beepers are wasted** or placed incorrectly

## Common Mistakes to Avoid
- Calling `karel_put_beeper()` without checking `beepers_in_bag()`
- Not handling the empty bag condition properly
- Continuing to move after mission completion
- Forgetting to update placement counters

## Extensions
- Place beepers in specific patterns (every other square)
- Navigate more complex paths with turns
- Collect beepers from one area and redistribute to another
- Implement beeper conservation strategies

## Mission Scenarios
- **Scenario 1**: 5 beepers, 10-square street → Bag empties first
- **Scenario 2**: 5 beepers, 3-square street → Wall reached first  
- **Scenario 3**: 5 beepers, 5-square street → Perfect match
