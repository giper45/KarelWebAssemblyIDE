# Karel String Operations

## Objective
Learn string manipulation and character arrays by implementing Karel command parsing, name management, and text-based communication systems.

## Background
Strings in C are arrays of characters terminated by '\0'. This exercise teaches:
- **String Declaration**: `char str[100]` or `char *str`
- **String Input/Output**: Reading and displaying strings
- **String Functions**: strlen, strcpy, strcat, strcmp from <string.h>
- **Command Parsing**: Breaking down user commands into actions
- **Text Processing**: Analyzing and manipulating text data

## Your Task
1. Create a command parser that reads string commands for Karel
2. Implement string validation and error checking
3. Build a naming system for Karel locations and objects
4. Practice string manipulation functions
5. Create formatted text output for Karel status reports

## Key Concepts
- **String Literals**: `"Hello World"` - stored in read-only memory
- **Character Arrays**: `char name[50]` - modifiable strings
- **String Termination**: Every string ends with '\0'
- **String Functions**: strlen(), strcpy(), strcat(), strcmp()
- **String Input**: gets(), fgets(), scanf("%s")

## String Applications with Karel
- Parse movement commands: "move 5", "turn left", "pick beeper"
- Name locations: "Home Base", "Beeper Storage", "Workshop"
- Status messages: Create descriptive output for Karel's activities
- Command validation: Check for valid command syntax

## Karel Command System Features
- Text-based movement commands
- Location naming and directory
- Error message generation
- Status report formatting
- Command history logging

## Tips
- Always ensure strings are null-terminated
- Check string bounds to prevent buffer overflow
- Use string.h functions instead of writing your own
- Compare strings with strcmp(), not == operator
- Be careful with gets() - prefer fgets() for safety
