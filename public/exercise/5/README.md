# Place Beepers Along the Path

## Objective
Learn to place beepers strategically using Karel's inventory management and conditional logic to avoid errors.

## Background
Karel starts with a limited number of beepers in his bag and needs to place them along a straight path. You must carefully manage Karel's inventory to ensure beepers are placed only when available.

## Your Task
Write code that makes Karel:
1. Start with 5 beepers in his bag
2. Move along the street from left to right
3. Place one beeper at each position
4. Continue until either reaching the wall OR running out of beepers
5. Handle both conditions gracefully without errors

## New Functions You'll Use
- `beepers_in_bag()` - Returns true if Karel has beepers available to place
- `karel_put_beeper()` - Place a beeper at current location (only if bag has beepers)
- `front_is_clear()` - Check if Karel can move forward (no wall ahead)

## Key Programming Concepts
- **Inventory Management**: Check available resources before using them
- **Multiple Exit Conditions**: Stop when wall reached OR beepers exhausted
- **Error Prevention**: Only place beepers when they're available
- **Resource Conservation**: Don't waste beepers unnecessarily

## Strategy Suggestions
1. **Check Before Place**: Always verify `beepers_in_bag()` before placing
2. **Move and Place Pattern**: Establish a rhythm of movement and placement
3. **Dual Exit Logic**: Handle both wall and empty bag conditions
4. **Status Reporting**: Track progress and remaining beepers

## Success Criteria
- Beepers should be placed along the path while Karel has them
- Karel should stop when hitting a wall OR when bag is empty
- No runtime errors from invalid beeper placement
- Clear feedback about why Karel stopped

## Code Structure
Your `studentCode()` function should:
1. Check if beepers are available in bag
2. Place beeper if available
3. Check if front is clear before moving
4. Move forward when possible
5. Handle completion conditions (wall or empty bag)
