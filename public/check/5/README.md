# Karel Variables & Data Types

## Objective
Learn about C data types and variables while controlling Karel and tracking movement statistics.

## Background
In this exercise, you'll use different C data types to track Karel's activities:
- **int**: Count moves, turns, and beepers
- **float**: Calculate distances and averages
- **char**: Store direction names and status
- **Constants**: Define world parameters

## Your Task
1. Declare variables to track Karel's movements
2. Use different data types for different purposes
3. Display statistics about Karel's journey
4. Control Karel's behavior based on collected data
5. Practice variable initialization and arithmetic operations

## Key Concepts
- **Variable Declaration**: `int move_count = 0;`
- **Data Types**: int, float, char for different data
- **Constants**: `const int MAX_MOVES = 100;`
- **Arithmetic Operations**: counting, averaging, comparisons
- **Printf Formatting**: Display statistics with proper format specifiers

## Karel Functions You'll Use
- `karel_move()` - Move Karel and increment counters
- `karel_turn_left()` - Turn Karel and track direction changes
- `karel_put_beeper()` - Place beepers and count placements
- `karel_pick_beeper()` - Collect beepers and update totals

## Tips
- Initialize counters to zero before using them
- Use meaningful variable names like `move_count`, `beeper_total`
- Track both successful and attempted actions
- Display statistics in a clear, formatted way
- Use constants for maximum values and limits
