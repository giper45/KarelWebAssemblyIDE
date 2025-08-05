# Solution: Find First Beeper and Stop

## Solution Explanation
This exercise teaches conditional loop control using negated conditions to search for a target. Karel uses a while loop to continue moving until the first beeper is found.

## Solution
```c
void studentCode() {
    static bool searchComplete = false;
    static int stepsTaken = 0;
    
    if (!searchComplete) {
        // Continue searching while no beeper present and path is clear
        while (!beepers_present() && front_is_clear()) {
            karel_move();
            stepsTaken++;
            printf("Step %d: Moved to (%d, %d) - Searching...\n", 
                   stepsTaken, karel_get_x(), karel_get_y());
        }
        
        // Search is complete - check results
        searchComplete = true;
        
        if (beepers_present()) {
            printf("SUCCESS! First beeper found at position (%d, %d) after %d steps!\n", 
                   karel_get_x(), karel_get_y(), stepsTaken);
        } else {
            printf("Search ended at wall. No beeper found after %d steps.\n", stepsTaken);
        }
        
        printf("Position: (%d, %d) | Steps taken: %d | Beeper here: %s\n", 
               karel_get_x(), karel_get_y(), stepsTaken, 
               beepers_present() ? "YES" : "NO");
    }
}
```


## NOTES 
As you can see, Karel instantly is rendered in the first beeper. This is beacause the while loop condition checks for the presence of a beeper and the path being clear before moving. If Karel finds a beeper, it stops immediately without picking it up.
This is because in the while loop condition karel_move() is called istantly each time the condition is true, which means Karel moves forward until it finds a beeper or hits a wall.

How can we delay the Karel rendering for each karel move step? In the next exercise we will learn how to use the karel_move_with_delay() function to control the rendering of Karel's movements.


## Key Concepts Demonstrated

### 1. **Negated Loop Condition**
```c
while (!beepers_present() && front_is_clear()) {
    // Continue moving while NO beeper is present
    karel_move();
}
```

### 2. **Compound Loop Conditions**
```c
// Two conditions must both be true to continue:
// 1. !beepers_present() - no beeper at current position
// 2. front_is_clear() - safe to move forward
```

### 3. **Search Progress Tracking**
```c
static int stepsTaken = 0;
stepsTaken++;  // Count each movement step
```

### 4. **Search Result Analysis**
```c
if (beepers_present()) {
    // Found target - success case
} else {
    // Hit wall - no target found
}
```

## How It Works

1. **Loop Entry**: Start the while loop with compound condition
2. **Condition Check**: Evaluate `!beepers_present() && front_is_clear()`
3. **Movement**: If both conditions true, move forward and increment step counter
4. **Loop Exit**: When beeper found OR wall reached, exit loop
5. **Result Analysis**: Check why loop ended (beeper found vs wall reached)

## Loop Logic Breakdown

```
Loop Condition: !beepers_present() && front_is_clear()

Case 1: No beeper + Clear path = Continue (true && true = true)
Case 2: Beeper found + Clear path = Stop (false && true = false)  
Case 3: No beeper + Wall ahead = Stop (true && false = false)
Case 4: Beeper found + Wall ahead = Stop (false && false = false)
```

## Expected Output

```
Step 1: Moved to (2, 1) - Searching...
Step 2: Moved to (3, 1) - Searching...
Step 3: Moved to (4, 1) - Searching...
Step 4: Moved to (5, 1) - Searching...
SUCCESS! First beeper found at position (5, 1) after 4 steps!
Position: (5, 1) | Steps taken: 4 | Beeper here: YES
```

## Algorithm Analysis

- **Time Complexity**: O(n) where n is distance to first beeper
- **Space Complexity**: O(1) - only uses constant extra variables
- **Termination**: Guaranteed to stop (either beeper found or wall reached)
- **Efficiency**: Optimal - stops immediately when target found

## Debugging Tips
1. **Print loop iterations** - verify loop executes correct number of times
2. **Check condition logic** - ensure `!beepers_present()` works as expected
3. **Test edge cases** - street with no beepers, beeper at start position
4. **Verify termination** - confirm loop always stops eventually

## Common Mistakes to Avoid
- Using `beepers_present()` instead of `!beepers_present()` (infinite loop risk)
- Forgetting `front_is_clear()` check (wall collision error)
- Moving after loop ends (going past target)
- Not handling both termination cases (beeper found vs wall reached)

## Extensions
- Find and collect the first N beepers
- Search for beepers in a 2D grid pattern
- Implement backtracking if no beeper found
- Add performance metrics (steps per beeper found)

## Learning Outcomes
- **Negated Conditions**: Understanding `!` operator in loop control
- **Compound Conditions**: Combining multiple boolean expressions with `&&`
- **Search Algorithms**: Implementing linear search with early termination
- **Loop Design**: Creating loops that terminate based on finding targets
- **Error Handling**: Managing different termination scenarios gracefully
