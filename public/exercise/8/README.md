# Find First Beeper and Stop
Learn to use conditional loops to search for a specific target and stop when found.

Karel is standing at the beginning of a long street with beepers scattered at various positions. Your task is to make Karel walk forward until finding the first beeper, then stop at that position without picking it up.

## Your Task
Write code that makes Karel:
1. Start walking forward along the street
2. Check each position for the presence of a beeper
3. Continue moving while no beeper is present
4. Stop immediately when reaching the first beeper
5. Remain at the beeper position (do not pick it up)

## New Programming Concepts
- **Conditional Loops**: Using while loops with negated conditions
- **Search Algorithms**: Finding the first occurrence of a target
- **Loop Termination**: Stopping when a condition is met
- **Negated Conditions**: Using `!beepers_present()` for loop control

## Functions You'll Use
- `beepers_present()` - Check if there's a beeper at current location
- `!beepers_present()` - Negated condition: true when NO beeper is present
- `front_is_clear()` - Ensure safe movement
- `karel_move()` - Move to next position
- `printf()` - Display search progress

## Key Programming Pattern
```c
// Continue moving while condition is true
while (!beepers_present() && front_is_clear()) {
    karel_move();
    // Update search status
}
```

## Strategy Suggestions
1. **Negative Condition Logic**: Use `!beepers_present()` to continue searching
2. **Safety First**: Always check `front_is_clear()` to avoid wall collisions
3. **Status Reporting**: Print position updates during the search
4. **Clear Termination**: Stop immediately when beeper is found

## Success Criteria
- Karel must stop at the first beeper position
- Karel should not pick up the beeper (just stop there)
- No movement beyond the first beeper
- No runtime errors from hitting walls
- Clear feedback about the search progress

## Code Structure
Your `studentCode()` function should:
1. Use a conditional loop to search for beepers
2. Move forward while no beeper is present and path is clear
3. Stop when beeper is found or wall is reached
4. Provide status messages during the search

## Loop Control Strategy
The key insight is using the negation operator `!`:
- `beepers_present()` returns true when beeper exists
- `!beepers_present()` returns true when NO beeper exists
- Loop continues while `!beepers_present()` is true
- Loop stops when `beepers_present()` becomes true

## Example Scenario
- Street has beepers at positions: 4, 7, 9
- Karel starts at (1,1) and walks forward
- Karel stops at (4,1) when first beeper is found
- Output shows: "First beeper found at position (4,1)!"

## Debugging Tips
1. **Print current position** at each step to track progress
2. **Verify loop condition** - ensure `!beepers_present()` works correctly
3. **Test boundary conditions** - what happens if no beeper exists?
4. **Check wall handling** - ensure proper stopping at street end

## Common Pitfalls
- Using `beepers_present()` instead of `!beepers_present()` in loop condition
- Forgetting to check `front_is_clear()` leading to wall collisions
- Moving after finding beeper instead of stopping immediately
- Not handling the case where no beeper exists on the street
