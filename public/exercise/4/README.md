# Collect All Beepers along the Street

## Objective
Navigate along a street and collect all beepers using conditional logic and proper movement control.

## Background
Karel's world contains beepers scattered along a horizontal street. Your job is to guide Karel to systematically move through the street and collect every beeper found.

## Your Task
Write code that makes Karel:
1. Move along the street from left to right
2. Check each position for beepers
3. Pick up beepers only when they are present
4. Continue until reaching the end wall
5. Use proper conditional logic to avoid errors

## New Functions You'll Use
- `beepers_present()` - Returns true if there's a beeper at Karel's current location
- `karel_pick_beeper()` - Pick up a beeper from current location
- `front_is_clear()` - Check if Karel can move forward (no wall ahead)

## Key Programming Concepts
- **Conditional Logic**: Use `if` statements to check conditions
- **Error Prevention**: Only pick beepers when they exist
- **Loop Control**: Continue moving until hitting a wall
- **State Checking**: Verify world conditions before taking actions

## Strategy Suggestions
1. **Check then Pick**: Always verify beeper presence before picking
2. **Move Safely**: Check for walls before moving
3. **Systematic Approach**: Cover every position methodically
4. **Error Handling**: Avoid attempting invalid operations

## Success Criteria
- All beepers in the street should be collected
- Karel should stop at the end wall
- No runtime errors from invalid operations
- Karel's beeper bag should contain all collected beepers

## Code Structure
Your `studentCode()` function should:
1. Check current position for beepers and pick if present
2. Check if front is clear before moving
3. Move forward when possible
4. Stop when reaching the wall
