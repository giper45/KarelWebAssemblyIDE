# Solution Karel Beeper File
As it is possible to see in the `setup` function, beepers stored in the file are random this time.


We can start by inspecting the `beepers.txt` file to see the beeper positions with the `read_strings_from_file()` function in the exercise. 

```c
void studentCode()
{
    read_strings_from_file("beepers.txt");
}

```

You will see something like this:
```
Row 1: 3,4
Row 2: 1,8
Row 3: 5,6
Row 4: 4,4
Row 5: 5,1
```

Now we can start by writing a function that takes a string, and parse it to extract the x and y coordinates of the beeper position.

```c
void parse_beeper_position(const char *line, int *x, int *y)
{
    for (int i = 0; i < strlen(line); i++)
    {
        if (line[i] == ',')
        {
            *x = atoi(line);
            *y = atoi(line + i + 1);
            return;
        }
    }
}


void test_parse(const char *filename)
{
    int x = -1, y = -1;
    FILE *file = fopen(filename, "r");
    if (!file)
    {
        perror("Error opening file for reading");
        return;
    }
    char buffer[MAX_DIM];
    int line = 0;
    
    
    while (fgets(buffer, sizeof(buffer), file))
    {
        printf("Row %d: %s", ++line, buffer);
        parse_beeper_position(buffer, &x, &y);
        printf("[PARSING] X: %d, Y: %d\n", x, y); 
        
    }
    fclose(file);
}
```

Let's analyze the `parse_beeper_position` function:
- It takes a string `line` and two pointers `x` and `y` to store the parsed coordinates.
- It iterates through the string to find the comma `,` that separates the x and y coordinates.
- It uses `atoi` to convert the string before the comma to an integer for `x` and the string after the comma to an integer for `y`. 

The `atoi` function is used to convert a string to an integer. It stops converting at the first non-numeric character, which is why it works correctly for our input format.
```c
       #include <stdlib.h>

       int atoi(const char *nptr);
       long atol(const char *nptr);
       long long atoll(const char *nptr);
```


Now we have found a way to parse the file, we can define a bidimensional array to store the beeper positions and a function to fill this array with the parsed values.
We can write two functions:
- `fill_beeper_matrix` to read the file and fill the matrix with the beeper counts.
- `print_beeper_matrix` to print the matrix.

```c
#define NO_ROWS 8
#define NO_COLS 10
int beepers_in_file[NO_COLS][NO_ROWS] = {0};

void fill_beeper_matrix(const char *filename)
{
    int x = -1, y = -1;
    FILE *file = fopen(filename, "r");
    if (!file)
    {
        perror("Error opening file for reading");
        return;
    }
    char buffer[MAX_DIM];
    
    while (fgets(buffer, sizeof(buffer), file))
    {
        parse_beeper_position(buffer, &x, &y);
        printf("X: %d, Y: %d\n", x, y);
        int row = y - 1;
        int col = x - 1;
        if (col >= 0 && col < NO_COLS && row >= 0 && row < NO_ROWS)
        {
            printf("Update beepers in file\n");
            beepers_in_file[col][row]++;
        }
    }
    fclose(file);
}

void print_beeper_matrix()
{
    for (int i = NO_ROWS - 1; i >= 0; i--)
    {
        for (int j = 0; j < NO_COLS; j++)
        {
            printf("%d ", beepers_in_file[j][i]);
        }
        printf("\n");
    }
}

#define NUM_COLS 10
void studentCode()
{
    //test_parse("beepers.txt");
    fill_beeper_matrix("beepers.txt");
    //pare("beepers.txt");
    print_beeper_matrix();
}

```

You will see something like this:
```
X: 7, Y: 7
Update beepers in file
X: 8, Y: 8
Update beepers in file
X: 10, Y: 5
Update beepers in file
X: 7, Y: 6
Update beepers in file
X: 5, Y: 8
Update beepers in file
0 0 0 0 0 0 0 0 0 0 
0 0 0 0 1 0 0 1 0 0 
0 0 0 0 0 0 1 0 0 0 
0 0 0 0 0 0 1 0 0 0 
0 0 0 0 0 0 0 0 0 1 
0 0 0 0 0 0 0 0 0 0 
0 0 0 0 0 0 0 0 0 0 
0 0 0 0 0 0 0 0 0 0 
0 0 0 0 0 0 0 0 0 0 
```

Be more careful with the difference between X, Y coordinates and row,column indices. In the example above, the first row corresponds to the first row of the matrix, but the first column corresponds to the first column of the matrix, not the first column of the world.

In addition, when we take the x coordinate from the file, this is the column index in the world, but in the matrix it is the row index. So we need to swap the x and y coordinates when filling the matrix.
```c
        int row = y - 1;
        int col = x - 1;
        ...
        beepers_in_file[col][row]++;
```

You can also use the first index of the matrix to represent the x coordinate and the second index to represent the y coordinate, but in this case you need to swap the indices when printing the matrix.
However, be careful to be consistent with the way you represent the coordinates in the matrix and in the world.


### Last step
Now we can proceed to the next step, which is to navigate the grid and put beepers at the positions specified in our matrix.

We are in the first position (1,1), so we have to simply do two nested loops to navigate the grid and put the beepers at the specified positions.
The code is similar to the previous exercise, let's start by just navigating the grid.


```c
void print_beeper_matrix()
{
    for (int i = NO_ROWS; i >= 0; i--)
    {
        for (int j = 0; j < NO_COLS; j++)
        {
            printf("%d ", beepers_in_file[j][i]);
        }
        printf("\n");
    }
}


void karel_turn_right()
{
    karel_turn_left();
    karel_turn_left();
    karel_turn_left();
}

void upFacingEast()
{
    karel_turn_left();
    karel_move();
    karel_turn_left();
}
void upFacingWest()
{
    karel_turn_right();
    karel_move();
    karel_turn_right();
}

void navigateAndPick()
{
    void (*moveFunction)();
    for (int i = 0; i < NO_ROWS; i++)
    {
        for (int j = 0 ; j < NO_COLS; j++)
        {
            if (j < NO_COLS -1)
                karel_move();
        }
        if (i < NO_ROWS - 1)
        {
            moveFunction = facing_east() ? upFacingEast : upFacingWest;
            moveFunction();
                
        }
        
    }
}


#define NUM_COLS 10
void studentCode()
{
    navigateAndPick();
    //test_parse("beepers.txt");
    //fill_beeper_matrix("beepers.txt");
    //pare("beepers.txt");
    //print_beeper_matrix();
}
```

Now modify the `navigateAndPick` function to do a printf when Karel is at a position where there is a beeper in the matrix, and call `karel_put_beeper()` to put a beeper at that position.

```c
#define NO_ROWS 8
#define NO_COLS 10
int beepers_in_file[NO_COLS][NO_ROWS] = {0};

void fill_beeper_matrix(const char *filename)
{
    int x = -1, y = -1;
    FILE *file = fopen(filename, "r");
    if (!file)
    {
        perror("Error opening file for reading");
        return;
    }
    char buffer[MAX_DIM];
    
    while (fgets(buffer, sizeof(buffer), file))
    {
        parse_beeper_position(buffer, &x, &y);
        printf("X: %d, Y: %d\n", x, y);
        int row = y - 1;
        int col = x - 1;
        if (col >= 0 && col < NO_COLS && row >= 0 && row < NO_ROWS)
        {
            printf("Update beepers in file\n");
            beepers_in_file[col][row]++;
        }
    }
    fclose(file);
}

void print_beeper_matrix()
{
    for (int i = NO_ROWS - 1; i >= 0; i--)
    {
        for (int j = 0; j < NO_COLS; j++)
        {
            printf("%d ", beepers_in_file[j][i]);
        }
        printf("\n");
    }
}


void karel_turn_right()
{
    karel_turn_left();
    karel_turn_left();
    karel_turn_left();
}

void upFacingEast()
{
    karel_turn_left();
    karel_move();
    karel_turn_left();
}
void upFacingWest()
{
    karel_turn_right();
    karel_move();
    karel_turn_right();
}

void navigateAndPick()
{
    void (*moveFunction)();
    for (int i = 0; i < NO_ROWS; i++)
    {
        for (int j = 0 ; j < NO_COLS; j++)
        {
            int karel_x = karel_get_x();
            int karel_y = karel_get_y();
            
            if (beepers_in_file[karel_x - 1][karel_y - 1] != 0)
            {
                printf("You should place a beeper at (%d, %d)\n", karel_x, karel_y);
                karel_put_beeper();
            }
            if (j < NO_COLS -1)
                karel_move();
        }
        if (i < NO_ROWS - 1)
        {
            moveFunction = facing_east() ? upFacingEast : upFacingWest;
            moveFunction();
                
        }
        
    }
}


#define NUM_COLS 10
void studentCode()
{
    fill_beeper_matrix("beepers.txt");
    print_beeper_matrix();
    navigateAndPick();

}

```
## Complete Code
The complete code is as follows:

```c
#include "karel.h"

#define REFRESH_RATE 0.01 // 1 second for smooth updates
// Variabili globali di Karel
const char *DIRECTION_NAMES[] = {"Est", "Nord", "Ovest", "Sud"};
void studentCode();
#define MAX_DIM 100
void setup()
{
    // Initialize Karel and world
    karel_init();
    karel_write_random_positions_to_file("beepers.txt", 5);
}

static double lastMoveTime = 0;
static int done = 0;
void loop(double timeSec, double elapsedSec)
{
    if (timeSec - lastMoveTime > REFRESH_RATE)
    { // Check frequently for smooth timing
        bool ready = drawWorld();
        if (ready && !done)
            studentCode();
        done = 1;
        lastMoveTime = timeSec;
    }
}

void write_strings_to_file(const char *filename, const char *strings[], int count)
{
    FILE *file = fopen(filename, "w");
    if (!file)
    {
        perror("Error opening file for writing");
        return;
    }
    for (int i = 0; i < count; ++i)
    {
        fprintf(file, "%s\n", strings[i]);
    }

    fclose(file);
}
void write_string_to_file(const char *filename, int count)
{
    FILE *file = fopen(filename, "w");
    if (!file)
    {
        perror("Error opening file for writing");
        return;
    }

    for (int i = 0; i < count; ++i)
    {
        fputs("HELLO\n", file);
    }

    fclose(file);
}

void read_strings_from_file(const char *filename)
{
    FILE *file = fopen(filename, "r");
    if (!file)
    {
        perror("Error opening file for reading");
        return;
    }
    char buffer[MAX_DIM];
    int line = 0;

    while (fgets(buffer, sizeof(buffer), file))
    {
        printf("Riga %d: %s", ++line, buffer);
    }
    fclose(file);
}
void read_strings_with_fgetc(const char *filename)
{
    FILE *in_file;
    char ch;

    in_file = fopen(filename, "r");

    if (in_file == NULL)
    {
        printf("The file could not be opened.\n");
        return;
    }

    while ((ch = fgetc(in_file)) != EOF)
    {
        printf("%c", ch);
    }

    fclose(in_file);
}

void parse_beeper_position(const char *line, int *x, int *y)
{
    for (int i = 0; i < strlen(line); i++)
    {
        if (line[i] == ',')
        {
            *x = atoi(line);
            *y = atoi(line + i + 1);
            return;
        }
    }
}



void test_parse(const char *filename)
{
    int x = -1, y = -1;

   
    FILE *file = fopen(filename, "r");
    if (!file)
    {
        perror("Error opening file for reading");
        return;
    }
    char buffer[MAX_DIM];
    int line = 0;
    
    
    while (fgets(buffer, sizeof(buffer), file))
    {
        printf("Row %d: %s", ++line, buffer);
        parse_beeper_position(buffer, &x, &y);
        printf("[PARSING] X: %d, Y: %d\n", x, y); 
        
    }
    fclose(file);
}

#define NO_ROWS 8
#define NO_COLS 10
int beepers_in_file[NO_COLS][NO_ROWS] = {0};

void fill_beeper_matrix(const char *filename)
{
    int x = -1, y = -1;
    FILE *file = fopen(filename, "r");
    if (!file)
    {
        perror("Error opening file for reading");
        return;
    }
    char buffer[MAX_DIM];
    
    while (fgets(buffer, sizeof(buffer), file))
    {
        parse_beeper_position(buffer, &x, &y);
        printf("X: %d, Y: %d\n", x, y);
        int row = y - 1;
        int col = x - 1;
        if (col >= 0 && col < NO_COLS && row >= 0 && row < NO_ROWS)
        {
            printf("Update beepers in file\n");
            beepers_in_file[col][row]++;
        }
    }
    fclose(file);
}

void print_beeper_matrix()
{
    for (int i = NO_ROWS - 1; i >= 0; i--)
    {
        for (int j = 0; j < NO_COLS; j++)
        {
            printf("%d ", beepers_in_file[j][i]);
        }
        printf("\n");
    }
}


void karel_turn_right()
{
    karel_turn_left();
    karel_turn_left();
    karel_turn_left();
}

void upFacingEast()
{
    karel_turn_left();
    karel_move();
    karel_turn_left();
}
void upFacingWest()
{
    karel_turn_right();
    karel_move();
    karel_turn_right();
}

void navigateAndPick()
{
    void (*moveFunction)();
    for (int i = 0; i < NO_ROWS; i++)
    {
        for (int j = 0 ; j < NO_COLS; j++)
        {
            int karel_x = karel_get_x();
            int karel_y = karel_get_y();
            
            if (beepers_in_file[karel_x - 1][karel_y - 1] != 0)
            {
                printf("You should place a beeper at (%d, %d)\n", karel_x, karel_y);
                karel_put_beeper();
            }
            if (j < NO_COLS -1)
                karel_move();
        }
        if (i < NO_ROWS - 1)
        {
            moveFunction = facing_east() ? upFacingEast : upFacingWest;
            moveFunction();
                
        }
        
    }
}


#define NUM_COLS 10
void studentCode()
{
    fill_beeper_matrix("beepers.txt");
    print_beeper_matrix();
    navigateAndPick();

}

```




