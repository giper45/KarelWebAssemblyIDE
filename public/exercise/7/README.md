# Avoid Obstacles
Teach Karel how to navigate around obstacles using conditional logic and directional control.
Karel is at the beginning of a corridor containing several obstacles (walls). The task is to make Karel advance along the main path, avoiding each obstacle encountered by moving right when necessary.
![World Map](/exercise/7/world.png)

Write code that allows Karel to:
1. Advance along the main corridor (row 1)
2. Detect when there's a wall ahead
3. Navigate around the obstacle by moving right (up)
4. Return to the main path after bypassing the obstacle
5. Continue until reaching the end of the corridor

## Functions You'll Use
- `front_is_clear()` - Check if Karel can move forward
- `right_is_clear()` - Check if Karel can move right
- `karel_turn_left()` - Turn Karel left (used to turn right: 3 times left)
- `karel_move()` - Move Karel one position
- `facing_east()` - Check if Karel is facing east

## Avoidance Strategy
The standard algorithm for bypassing obstacles to the right:
1. **Detection**: If the front is blocked
2. **Turn Right**: Orient Karel upward
3. **Move Up**: Bypass the obstacle by moving upward
4. **Turn Right**: Orient Karel eastward
5. **Move Forward**: Continue along the parallel path
6. **Turn Right**: Orient Karel downward
7. **Move Down**: Return to the main path
8. **Turn Right**: Orient Karel eastward again

## Success Criteria
- Karel must reach the end of the corridor
- All obstacles must be correctly bypassed
- Karel must always return to the main path (row 1)
- No runtime errors from invalid movements

## Code Structure
Your `studentCode()` function should:
1. Check if the front is clear
2. If blocked, execute the avoidance sequence
3. If clear, continue advancing
4. Handle completion when reaching the end

## Suggested Helper Function
```c
void turn_right() {
    karel_turn_left();
    karel_turn_left();
    karel_turn_left();
}
```

## Example Scenario
- Corridor with obstacles at positions: 3, 6, 8
- Karel starts at (1,1) facing east
- Karel bypasses each obstacle by temporarily moving to row 2
- Karel ends at the end of the corridor in row 1

## Debugging Tips
1. **Print Karel's position** at each movement
2. **Track direction** to verify correct orientation
3. **Check the avoidance pattern** step by step
4. **Verify return** to main path after each obstacle
