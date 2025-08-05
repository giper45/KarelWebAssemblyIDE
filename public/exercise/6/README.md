# Count Beepers Along the Street

## Objective
Learn to count beepers while moving through a street and display the total count.

## Background
Karel is standing at the beginning of a street with an unknown number of beepers scattered along the path. Your task is to traverse the street, count all beepers encountered, and display the final count.

## Your Task
Write code that makes Karel:
1. Start at the beginning of the street
2. Move through the street from left to right
3. Count each beeper encountered (without picking them up)
4. Continue until reaching the end wall
5. Display the final count

## New Programming Concepts
- **Counting Logic**: Track quantities using variables
- **Sequential Processing**: Process items one by one in order
- **Variable Updates**: Increment counters when conditions are met

## Functions You'll Use
- `beepers_present()` - Check if there's a beeper at current location
- `front_is_clear()` - Navigate through the street
- `karel_move()` - Move to next position
- `printf()` - Display the count results

## Strategy Suggestions
1. **Count Without Collecting**: Check beepers but don't pick them up
2. **Track Progress**: Use a variable to maintain count
3. **Clear Reporting**: Provide status updates during counting

## Success Criteria
- All beepers in the street should be counted
- Karel should reach the end wall
- The correct total count should be displayed
- Clear feedback about the counting process

## Code Structure
Your `studentCode()` function should:
1. Check current position for beepers and increment counter
2. Move forward until wall is reached
3. Display the final count when complete

## Example Scenario
- Street contains beepers at positions: 3, 5, 6, 8, 9
- Karel counts: 5 beepers total
- Output shows: "Total beepers counted: 5"
