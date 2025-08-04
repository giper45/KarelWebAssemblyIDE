# Karel Linear Search Algorithm

## Objective
Implement linear search algorithm using Karel to systematically find beepers in the world.

## Background
Linear search is a fundamental algorithm that examines each element in a sequence until finding the target. With Karel, you'll implement this by:
- **Systematically traversing** the world row by row
- **Checking each position** for beepers
- **Recording found positions** and counting discoveries
- **Understanding algorithm efficiency** through step counting

## Your Task
1. Implement linear search to find all beepers in Karel's world
2. Count the number of search steps taken
3. Record positions where beepers are found
4. Compare search efficiency with different strategies
5. Implement both "find first" and "find all" versions

## Key Concepts
- **Linear Search**: Check each position sequentially
- **Search Pattern**: Row-by-row systematic coverage
- **Algorithm Efficiency**: Count operations and compare methods
- **Early Termination**: Stop when target is found (for "find first")
- **Complete Search**: Continue until entire world is searched (for "find all")

## Algorithm Variations You'll Implement
- **Find First Beeper**: Stop at the first beeper found
- **Find All Beepers**: Continue until entire world is searched
- **Count Search Steps**: Track algorithm efficiency
- **Optimized Search**: Skip areas that can't contain beepers

## Karel Functions You'll Use
- `karel_move()` - Move to next search position
- `karel_turn_left()` - Navigate to next row
- `beepers_present()` - Check current position for target
- `karel_pick_beeper()` - Collect found items

## Tips
- Maintain systematic search pattern to avoid missing positions
- Count both successful and unsuccessful search steps
- Use variables to track current position and search progress
- Consider boundary conditions (edges of the world)
- Test with different beeper distributions to understand performance
