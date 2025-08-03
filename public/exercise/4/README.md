# Collect All Beepers

## Objective
Navigate the world and collect all beepers scattered throughout different locations.

## Background
Karel's world contains several beepers (diamond-shaped objects) placed at various positions. Your job is to guide Karel to find and collect all of them.

## Your Task
Write code that makes Karel:
1. Navigate through the world systematically
2. Detect when standing on a beeper
3. Pick up each beeper found
4. Continue until all beepers are collected

## New Functions
- `beepers_present()` - Returns true if there's a beeper at Karel's current location
- `karel_pick_beeper()` - Pick up a beeper from current location

## Strategy Suggestions
1. **Systematic Search**: Cover the entire world methodically
2. **Beeper Detection**: Check for beepers at each location
3. **Collection**: Pick up beepers when found
4. **Path Planning**: Ensure you visit every accessible location

## Success Criteria
All beepers should be collected and stored in Karel's beeper bag.
