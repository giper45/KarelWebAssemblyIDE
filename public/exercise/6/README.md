# Karel Input Processing

## Objective
Learn how to read and process user input to control Karel's behavior dynamically using scanf and formatted output.

## Background
In this exercise, you'll create an interactive Karel program that:
- **Reads commands** from user input to control Karel
- **Processes different data types** (integers, characters, strings)
- **Validates input** and handles errors gracefully
- **Formats output** to provide clear feedback
- **Creates interactive menus** for Karel control

## Your Task
1. Create a command system that reads user input to control Karel
2. Process different types of input (move count, direction, commands)
3. Validate user input and provide error messages
4. Display formatted status information about Karel
5. Build an interactive menu system for Karel operations

## Key Concepts
- **scanf() for Input**: Read integers, characters, and strings
- **Input Validation**: Check for valid ranges and types
- **printf() Formatting**: Create aligned, readable output
- **Interactive Loops**: Continuous command processing
- **Error Handling**: Graceful response to invalid input

## Interactive Features You'll Build
- Command menu for Karel operations
- Dynamic movement based on user input
- Beeper placement by user coordinates
- Status reporting with formatted output
- Error messages for invalid commands

## Karel Functions You'll Use
- `karel_move()` - Execute movement commands
- `karel_turn_left()` - Turn based on user direction input
- `karel_put_beeper()` - Place beepers at user-specified locations
- `karel_pick_beeper()` - Collect beepers on command

## Tips
- Always validate input ranges (e.g., coordinates within world bounds)
- Use clear prompts to guide user input
- Provide feedback for both successful and failed operations
- Handle buffer issues when mixing scanf with other input functions
- Use meaningful format specifiers for aligned output
