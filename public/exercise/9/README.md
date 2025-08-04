# Karel Function Library

## Objective
Create custom functions to extend Karel's capabilities while learning function definition, parameters, return values, and scope.

## Background
Functions help organize code and create reusable components. In this exercise, you'll build a library of custom Karel functions that:
- **Simplify complex movements** (like turning right, moving multiple steps)
- **Provide useful utilities** (checking safe movements, counting objects)
- **Return information** about Karel's world and status
- **Demonstrate parameter passing** and local vs global variables

## Your Task
1. Create utility functions that extend Karel's basic movements
2. Build functions that return information about Karel's environment
3. Practice parameter passing with movement functions
4. Understand local vs global variables in Karel's context
5. Create a complete "Karel library" of useful functions

## Key Concepts
- **Function Declaration**: `void karel_turn_right();`
- **Function with Parameters**: `void karel_move_steps(int steps);`
- **Function with Return Value**: `int count_beepers_around();`
- **Local Variables**: Variables declared inside functions
- **Global Variables**: Variables accessible throughout the program
- **Function Scope**: Understanding where variables can be accessed

## Karel Functions You'll Create
- `karel_turn_right()` - Turn Karel right (3 left turns)
- `karel_move_steps(int n)` - Move Karel n steps safely
- `karel_turn_around()` - Turn Karel 180 degrees
- `int count_moves_to_wall()` - Count steps to nearest wall
- `int safe_to_move()` - Check if movement is safe

## Tips
- Use descriptive function names that explain their purpose
- Always validate parameters (like checking for negative steps)
- Use local variables for temporary calculations
- Return meaningful values for query functions
- Test each function thoroughly before using it in complex scenarios
