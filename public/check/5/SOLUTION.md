# Solution: Hello World & Basic Syntax

## Solution Explanation
This exercise demonstrates the fundamental structure of a C program and basic output operations.

## Complete Solution
```c
#include <stdio.h>

// This is a single-line comment
/* This is a
   multi-line comment */

int main() {
    // Display "Hello World!" message
    printf("Hello World!\n");
    
    // Display your name (replace with your actual name)
    printf("My name is: Student\n");
    
    // Print an integer number using %d
    printf("My favorite number is: %d\n", 42);
    
    // Print a decimal number using %f
    printf("Pi is approximately: %.2f\n", 3.14159);
    
    return 0;  // Indicates successful program execution
}
```

## Key Learning Points

### Program Structure
1. **Header inclusion**: `#include <stdio.h>` provides access to input/output functions
2. **Main function**: `int main()` is the program entry point
3. **Return statement**: `return 0;` indicates successful execution

### Printf Format Specifiers
- `%d` - for integers
- `%f` - for floating-point numbers
- `%.2f` - for floating-point with 2 decimal places
- `%c` - for characters
- `%s` - for strings

### Comments
- `//` for single-line comments
- `/* */` for multi-line comments
- Use comments to explain what your code does

## Expected Output
```
Hello World!
My name is: Student
My favorite number is: 42
Pi is approximately: 3.14
```

## Extensions to Try
1. Print different data types (char, int, float, double)
2. Use escape sequences like `\t` (tab), `\"` (quote)
3. Format numbers with different precision
4. Create formatted tables using spacing
