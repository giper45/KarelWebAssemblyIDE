# Karel Scope & Global Variables

## Objective
Understand variable scope, global vs local variables, and visibility rules by managing Karel's state information across multiple functions.

## Background
Variable scope determines where variables can be accessed in your program:
- **Global Variables**: Accessible throughout the entire program
- **Local Variables**: Only accessible within their function
- **Static Variables**: Retain values between function calls
- **Function Parameters**: Local to the function, passed by value or reference

## Your Task
1. Use global variables to track Karel's journey statistics
2. Create functions with local variables for temporary calculations
3. Demonstrate static variables that persist between function calls
4. Show scope conflicts and variable shadowing
5. Practice proper variable organization and naming

## Key Concepts
- **Global Scope**: Variables declared outside all functions
- **Function Scope**: Variables declared inside functions
- **Block Scope**: Variables declared inside { } blocks
- **Static Variables**: `static int count = 0;` - persist between calls
- **Variable Shadowing**: Local variables hiding global ones

## Scope Applications with Karel
- Global counters for total moves, turns, beepers collected
- Local variables for function-specific calculations
- Static variables for function call counting
- Parameter passing for coordinate calculations

## Karel State Management
- Global position tracking and statistics
- Local path-finding calculations
- Static counters for operation frequencies
- Function-specific temporary variables

## Tips
- Use global variables sparingly - only for truly global state
- Prefer local variables when data is only needed in one function
- Use static variables for counters that need to persist
- Choose descriptive names to avoid scope confusion
- Be careful of variable shadowing - use different names when possible
