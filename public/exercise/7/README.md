# Karel Constants & Preprocessor

## Objective
Learn about constants, #define directives, and preprocessor usage by creating configurable Karel world parameters and behavior constants.

## Background
Constants and preprocessor directives help create maintainable, configurable code:
- **#define**: Create symbolic constants and simple macros
- **const keyword**: Create read-only variables
- **Preprocessor**: Text replacement before compilation
- **Configuration**: Use constants for world settings and behavior parameters

## Your Task
1. Use #define to create symbolic constants for world configuration
2. Create const variables for Karel behavior parameters
3. Build configurable macros for common Karel operations
4. Understand the difference between #define and const
5. Practice conditional compilation with #ifdef

## Key Concepts
- **#define CONSTANT value**: Preprocessor text replacement
- **const type name = value**: Read-only variables
- **Macros**: #define with parameters for code generation
- **Conditional Compilation**: #ifdef, #ifndef, #endif
- **Header Guards**: Prevent multiple inclusion

## Configuration Areas You'll Implement
- World size and boundary constants
- Movement timing and speed settings
- Beeper limits and inventory constants
- Debug and display configuration options
- Karel behavior parameter tuning

## Karel Applications
- Configure world dimensions and limits
- Set movement delays and animation timing
- Define maximum beeper capacities
- Create debug output controls
- Standardize common operation sequences

## Tips
- Use ALL_CAPS for #define constants
- Use descriptive names: MAX_BEEPERS not just MAX
- Group related constants together
- Document what each constant controls
- Test different configurations to verify flexibility
