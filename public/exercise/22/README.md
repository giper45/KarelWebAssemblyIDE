# Karel handles beepers in files
In this exercise, Karel should read and write files containing beeper positions.

Your goal is to navigate the grid, pick up beepers from specified positions, and write their coordinates to a file.

You can choose the format of the output file, but it should clearly indicate the positions of the beepers Karel has collected.

You also have to write a function that reads the beeper positions from the file and prints them in a readable format.

Call the file `beeper_positions.txt` and you are free to choose the format of the output file, but it should clearly indicate the positions of the beepers Karel has collected.





## Place beepers from a file
In this mission the grid is empty, and Karel should place new beepers based on the positions specified in a file.
Karel has a `beepers.txt` file that contains the positions of beepers in a grid. 
Karel should read this file and place beepers at the specified positions.



### File format 
Each row contains two integers separated by a ",", representing the x and y coordinates of a beeper's position in the grid. For example:
```
1,2
3,4
5,6
```

In the example, the first beeper is at position (1,2), the second at (3,4), and the third at (5,6).
The final grid should look like this:
TBD 






## Background concepts on file handling
Let's start by introducing preliminary concepts on files in C
programming. A file is a sequence of bytes stored on a disk, and it can be used to store data persistently. In C, files are handled using the `FILE` type, which is defined in the `stdio.h` header file.

> NOTE: in the Karel world, we are limited to use functions on file. Supported functions are:
> - `fopen`
> - `fclose`
> - `fprintf`
> - `fputs`
> - `fgets`
> - `fgetc`


Other functions could also works, but they are not guaranteed to work in the Karel world.

## Opening and Closing Files
There are two relevant functions to open and close files in C:
- `fopen`: Opens a file and returns a pointer to a `FILE` object.
- `fclose`: Closes a file and releases the resources associated with it.

The fopen function takes two arguments: the name of the file and the mode in which to open it. The three primary modes are:
- `"r"`: Read mode (file must exist).
- `"w"`: Write mode (creates a new file or truncates an existing one).
- `"a"`: Append mode (writes to the end of the file).

When opening a file, it is important to check if the file was opened successfully. If `fopen` fails, it returns `NULL`. Always check for this condition to avoid dereferencing a null pointer.

The function returns a pointer to a `FILE` object, which is used for subsequent file operations.
After finishing with a file, it is essential to close it using `fclose` to free up system resources.

## Writing to Files
To write to a file, you can use the `fprintf` or `fputs` functions. 
- `fprintf`: Similar to `printf`, but writes formatted output to a file.
- `fputs`: Writes a string to a file.
Both functions require a `FILE` pointer as the first argument, followed by the data to write to the file.
Here is an example of how to write to a file:

```c
#include <stdio.h>
int main() {
    FILE *file = fopen("example.txt", "w");
    if (file == NULL) {
        perror("Error opening file");
        return 1;
    }

    fprintf(file, "Hello, World!\n");
    fputs("This is a test file.\n", file);

    fclose(file);
    return 0;
}
``` 

## Reading from Files
To read from a file, you can use the `fgets`, `fgetc` functions.
- `fgets`: Reads a line from a file into a string.
- `fgetc`: Reads a single character from a file.
Here is an example of how to read from a file:  

```c
#include <stdio.h>
int main() {
    FILE *file = fopen("example.txt", "r");
    if (file == NULL) {
        perror("Error opening file");
        return 1;
    }

    char buffer[100];
    while (fgets(buffer, sizeof(buffer), file) != NULL) {
        printf("%s", buffer);
    }
    fclose(file);
    return 0;
}
```
## Example in Karel World
Try to run the default code in the exercise, and see the output.
Try to modify this code to reach the goal.