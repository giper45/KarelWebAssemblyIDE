# Solution handles beepers in files
As it is possible to see in the `setup` function, beeper positions and beepers stored in the file are random this time.

## Mission 1 - write beepers positions to a file
We first collect beepers positions by navigating the grid. 
This was already done in the previous exercises, so we can use the `navigateAndCollectBeepers` function to do this. This will be a good starting point for our solution.
The final code will look like this:
```c
void studentCode()
{
    navigateAndCollectBeepers();
    write_beeper_positions_to_file("beepers.txt");
    read_beeper_positions_from_file("beepers.txt");
}

```

We use a slight variation that use the function pointers and three-way operator to define the movements depending on the direction Karel is facing.
This is an elegant approach that allows us to avoid using multiple if-else statements.
You could also use an array of function pointers for more complex scenarios, but for this case, the three-way operator is sufficient.
Before picking beepers, try to collect them in a bidimensional array, and then print the array to see the positions of the beepers.
```c
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

void checkBeeper(int positions[NO_COLS][NO_ROWS])
{
    if (beepers_present())
    {
        printf("Found a beeper!\n");
        //karel_pick_beeper();
        positions[karel_get_x() - 1][karel_get_y() - 1]++;
    }
}

void navigateAndCollectBeepers(int positions[NO_COLS][NO_ROWS])
{
    void (*moveFunction)();
    for (int i = 0; i < NO_ROWS; i++)
    {
        for (int j = 0 ; j < NO_COLS; j++)
        {
            checkBeeper(positions);
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
void printBeeperPositions(int positions[NO_COLS][NO_ROWS])
{
    for (int i = NO_ROWS -1; i  >= 0; i--)
    {
        for (int j = 0; j < NO_COLS; j++)
        {
            printf("%d ", positions[j][i]);
        }
        printf("\n");
    }
}


void studentCode()
{
    int beeperPositions[NO_COLS][NO_ROWS] = {0};
    
    navigateAndCollectBeepers(beeperPositions);
    printBeeperPositions(beeperPositions);
}
```


Ok, now uncomment the karel_pick_beeper() line in the checkBeeper function, and run the code again to clean the grid from beepers.

We now have to write a function that writes the beeper positions to a file.
The function should take the positions array and the filename as arguments, and write the positions to the file in a readable format.

```c
void write_beeper_positions_to_file(const char *filename, int positions[NO_COLS][NO_ROWS])
{
    FILE *file = fopen(filename, "w");
    if (!file)
    {
        perror("Error opening file for writing");
        return;
    }
    for (int i = 0; i < NO_ROWS; i++)
    {
        for (int j = 0; j < NO_COLS; j++)
        {
            if (positions[j][i] > 0)
            {
                fprintf(file, "Row %d: %d,%d\n", i + 1, j + 1, positions[j][i]);
            }
        }
    }
    fclose(file);
}
```

Finally, use the `read_beeper_positions_from_file` function to verify the everything is working.
### COMPLETE CODE
The complete code should look like this:

```c
#include "karel.h"

#define REFRESH_RATE 0.01// 1 second for smooth updates
// Variabili globali di Karel
const char *DIRECTION_NAMES[] = {"Est", "Nord", "Ovest", "Sud"};
void studentCode();
#define MAX_DIM 100
#define NO_COLS 10 
#define NO_ROWS 8
void setup()
{
    // Initialize Karel and world
    karel_init();

    // Put some beeper
        // Put some beeper
    karel_put_beepers_random_positions(5);
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
        perror("Errore apertura file scrittura");
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
        perror("Errore apertura file scrittura");
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
        perror("Errore apertura file lettura");
        return;
    }
    char buffer[MAX_DIM];
    int line = 0;

    while (fgets(buffer, sizeof(buffer), file))
    {
        printf("Row %d: %s", ++line, buffer);
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
        printf("Il file non puo essere aperto.\n");
        return;
    }

    while ((ch = fgetc(in_file)) != EOF)
    {
        printf("%c", ch);
    }

    fclose(in_file);
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

void checkBeeper(int positions[NO_COLS][NO_ROWS])
{
    if (beepers_present())
    {
        printf("Found a beeper!\n");
        karel_pick_beeper();
        positions[karel_get_x() - 1][karel_get_y() - 1]++;
    }
}

void navigateAndCollectBeepers(int positions[NO_COLS][NO_ROWS])
{
    void (*moveFunction)();
    for (int i = 0; i < NO_ROWS; i++)
    {
        for (int j = 0 ; j < NO_COLS; j++)
        {
            checkBeeper(positions);
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
void printBeeperPositions(int positions[NO_COLS][NO_ROWS])
{
    for (int i = NO_ROWS -1; i  >= 0; i--)
    {
        for (int j = 0; j < NO_COLS; j++)
        {
            printf("%d ", positions[j][i]);
        }
        printf("\n");
    }
}
void writeBeepersToFile(const char *filename, int positions[NO_COLS][NO_ROWS])
{
    FILE *file = fopen(filename, "w");
    if (!file)
    {
        perror("Error opening file for writing");
        return;
    }
    for (int i = 0; i < NO_ROWS; i++)
    {
        for (int j = 0; j < NO_COLS; j++)
        {
            if (positions[j][i] > 0)
            {
                fprintf(file, "(%d,%d)\n", i + 1, j + 1, positions[j][i]);
            }
        }
    }
    fclose(file);
}


void studentCode()
{
    int beeperPositions[NO_COLS][NO_ROWS] = {0};
    
    navigateAndCollectBeepers(beeperPositions);
    printBeeperPositions(beeperPositions);
    printf("[+] Write to file\n");
    writeBeepersToFile("beeper_positions.txt", beeperPositions);
    printf("[+] Read from file\n");
    read_strings_from_file("beeper_positions.txt");
    
}
```



## Mission 2 

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
int beepers_in_file[NO_ROWS][NO_COLS] = {0};

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
        if (x >= 0 && x < NO_COLS && y >= 0 && y < NO_ROWS)
        {
            beepers_in_file[y][x]++;
        }
    }
    fclose(file);
}

void print_beeper_matrix()
{
    for (int i = 0; i < NO_ROWS; i++)
    {
        for (int j = 0; j < NO_COLS; j++)
        {
            printf("%d ", beepers_in_file[i][j]);
        }
        printf("\n");
    }
}
...
#define NUM_COLS 10
void studentCode()
{
    fill_beeper_matrix("beepers.txt");
    test_parse("beepers.txt");
    print_beeper_matrix();
}

```

You will see something like this:
```
Row 1: 6,6
[PARSING] X: 6, Y: 6
Row 2: 2,7
[PARSING] X: 2, Y: 7
Row 3: 6,2
[PARSING] X: 6, Y: 2
Row 4: 1,8
[PARSING] X: 1, Y: 8
Row 5: 1,1
[PARSING] X: 1, Y: 1
0 0 0 0 0 0 0 0 0 0 
0 1 0 0 0 0 0 0 0 0 
0 0 0 0 0 0 1 0 0 0 
0 0 0 0 0 0 0 0 0 0 
0 0 0 0 0 0 0 0 0 0 
0 0 0 0 0 0 0 0 0 0 
0 0 0 0 0 0 1 0 0 0 
0 0 1 0 0 0 0 0 0 0 

```

Be more careful with the difference between X, Y coordinates and row,column indices. In the example above, the first row corresponds to the first row of the matrix, but the first column corresponds to the first column of the matrix, not the first column of the world.

In addition, when we take the x coordinate from the file, this is the column index in the world, but in the matrix it is the row index. So we need to swap the x and y coordinates when filling the matrix (`beepers_in_file[y][x]++`).


Now we can proceed to the next step, which is to navigate the grid and put beepers at the positions specified in our matrix.