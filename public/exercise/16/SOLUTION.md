# Solution Karel the adder
We show a "bottom-up" approach to solving the problem of counting beepers in a grid using a bidimensional array.

NOTE: 
To speed-up the execution, you can modify the `REFRESH_RATE` variable in the `exercise.c` file to a lower value, like `0.01`. This will make Karel move faster and complete the exercise more quickly.

When testing, setup a slower `REFRESH_RATE` to see Karel's movements more clearly.

After completing a function, you can reduce the `REFRESH_RATE` to `0.01` to speed up the execution.


## First steps: navigate a row
We start by implementing basic functions to handle the Karel movements. 
```c
void goUpLeft() 
{
    karel_turn_left();
    karel_move();
    karel_turn_left();
}
void karel_turn_right()
{
    karel_turn_left();
    karel_turn_left();
    karel_turn_left();
}
void goUpRight()
{
    karel_turn_right();
    karel_move();
    karel_turn_right();
}

``` 

* `goUpLeft()` moves Karel up and to the left.
* `karel_turn_right()` turns Karel right by turning left three times.
* `goUpRight()` moves Karel up and to the right.

We can also implement two functions to verify if Karel should go up and right or up and left.
```c 
bool shouldGoUpRight()
{
    return (facing_west() && !front_is_clear());
}
bool shouldGoUpLeft()
{
    return (facing_east() && !front_is_clear());
}

```
After implementing these function, we can define a `navigateRow()` function to navigate through a row of the grid.
```c
void navigateRow()
{
    while (!shouldGoUpRight() && !shouldGoUpLeft())
    {
        karel_move();
    }
}
```
The function `navigateRow()` moves Karel forward until it reaches the end of the row. 

Stop here and try to run the code. Karel should be able to navigate through the first row of the grid.


### Navigate the grid
Now we can try to implement a function to navigate through the grid. The number of columns are 8, so we can use a loop to navigate through each column.
```c
#define NO_COLS 8
void navigateGrid() 
{
    for (int i = 0; i < NO_ROWS; i++)
    {
        navigateRow();
        if (i < NO_ROWS - 1)
            shouldGoUpRight() ? goUpRight() : goUpLeft(); 
    }
    
}
```

The three-way conditional operator `?` is used to decide which function to call based on the direction Karel is facing.

The navigateGrid function will move Karel through the grid, navigating each row and moving up to the next row when it reaches the end of the current row.

### Counting Beepers
Now we can implement a function to count the beepers in the grid. We will use a
bidimensional array to store the count of beepers in each cell of the grid.
We write a `navigateAndCollectBeepers()` function to collect beepers in a row.
```c
void navigateAndCollectBeepers() 
{
    for (int i = 0; i < NO_ROWS; i++)
    {
        collectBeepersInRow();
        if (i < NO_ROWS - 1)
            shouldGoUpRight() ? goUpRight() : goUpLeft(); 
    }
    
}


```
NOTE THE OFFSET: The coordinates of the grid are 1-based, but the array is 0-based, so we need to subtract 1 from the coordinates when accessing the array.

This is a common issue when working with arrays in C, especially when the grid or matrix is defined with 1-based indexing, as is often the case in mathematical contexts.

Be careful to ensure that the array indices do not go out of bounds. In this case, we assume that Karel will not move outside the grid, so we don't need to check for that.

For now we are only printing the position of the beeper, but we can later modify to update the bidimensional array with the count of beepers in each cell.




We can also write a `printMatrix()`utility function to print the bidimensional array.
```c
void printMatrix()
{
    for (int i = 0; i < NO_ROWS; i++)
    {
        for (int j = 0; j < NO_COLS; j++)
        {
            printf(" beepers[%d][%d]=%d\n", i, j , beepers[i][j]);
        }
    }
}
```

Now we can modify the `navigateGrid()` function to call `collectBeepersInRow()` and update the bidimensional array with the count of beepers in each cell.
```c
void navigateAndCollectBeepers() 
{
    for (int i = 0; i < NO_COLS; i++)
    {
        collectBeepersInRow();
        if (i < NO_COLS - 1)
            shouldGoUpRight() ? goUpRight() : goUpLeft(); 
    }
    
}

```

Now we have collected all the values in the matrix and can proceed to realizing the sums.


Let's write two functions, one for summing the first row and another for summing the first column.
```c

int sumFirstRow()
{
    int sum = 0;  
    for (int i = 0; i < NO_COLS; i++)
    {
        sum += beepers[0][i];
    }
    return sum; 
}

int sumFirstCol()
{
    int sum = 0;  
    for (int i = 0; i < NO_ROWS; i++)
    {
        sum += beepers[i][0];
    }
    return sum; 
}


void studentCode()
{
    navigateAndCollectBeepers();
    int firstRowSum = sumFirstRow();
    int firstColSum = sumFirstCol(); 
    printf("We expect that the first row contains 2 beepers, value= %d\n", firstRowSum); 
    printf("We expect that the first col contains 3 beepers, value= %d\n", firstColSum); 

    //printMatrix();
}

```
If everything is correct, Karel should print the sums of the first row (2) and first column (3) when it finishes navigating the grid.

Now we should place a beeper at the position corresponding to the sums of the first row and column.
After navigating the grid, Karel is at the top left corner (1, 8) and it is facing West. 
We write a function to let Karel go down to the initial position (1, 1).

```c
void karelGoDown()
{
    karel_turn_left();
    for (int i = 0; i < NO_ROWS - 1; i++)
    {
        karel_move();
    }
}
```


Now we need to move Karel to the position (firstColSum, firstRowSum) and place a beeper there.

Write a function `moveTo(int x, int y)` to move Karel to the position (x, y) in the grid.
```c
void moveTo(int row, int col)
{
    for (int i = 0; i < col; i++)
    {
        karel_move();
    }
    karel_turn_left();
    for (int j = 0; j < row; j++)
    {
        karel_move();
    }
}
```

```c
void studentCode()
{
    navigateAndCollectBeepers();
    int firstRowSum = sumFirstRow();
    int firstColSum = sumFirstCol(); 
    printf("We expect that the first row contains 2 beepers, value= %d\n", firstRowSum); 
    printf("We expect that the first col contains 3 beepers, value= %d\n", firstColSum); 
    karelGoDown();
    karel_turn_left();

    moveTo(2, 3);
    karel_put_beeper();
    karel_move();
    //printMatrix();
}
```

Here is the complete solution:
```c
#include "karel.h"
#define REFRESH_RATE 0.01 // 1 second for smooth updates
// Variabili globali di Karel
const char *DIRECTION_NAMES[] = {"Est", "Nord", "Ovest", "Sud"};
void studentCode();

void setup()
{
    // Initialize Karel and world
    karel_init();

    // Put some beeper
    karel_add_beeper(3, 2);
    karel_add_beeper(5, 4);
    karel_add_beeper(6, 3);
    karel_add_beeper(2, 5);
    karel_add_beeper(1, 1);
    karel_add_beeper(4, 1);
    karel_add_beeper(1, 5);
    karel_add_beeper(1, 7);

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
void goUpLeft() 
{
    karel_turn_left();
    karel_move();
    karel_turn_left();
}
void karel_turn_right()
{
    karel_turn_left();
    karel_turn_left();
    karel_turn_left();
}
void goUpRight()
{
    karel_turn_right();
    karel_move();
    karel_turn_right();
}


bool shouldGoUpRight()
{
    return (facing_west() && !front_is_clear());
}
bool shouldGoUpLeft()
{
    return (facing_east() && !front_is_clear());
}

void navigateRow()
{
    while (!shouldGoUpRight() && !shouldGoUpLeft())
    {
        karel_move();
    }
    
}
#define NO_COLS 10
#define NO_ROWS 8

int beepers [NO_ROWS][NO_COLS] = {0};
void printMatrix()
{
    for (int i = 0; i < NO_ROWS; i++)
    {
        for (int j = 0; j < NO_COLS; j++)
        {
            printf(" beepers[%d][%d]=%d\n", i, j , beepers[i][j]);
        }
    }
}

void collectBeepersInRow()
{
        while (!shouldGoUpRight() && !shouldGoUpLeft())
    {
        if (beepers_present())
        {
            printf("beeper found at row %d, col %d\n", karel_get_y() - 1, karel_get_x() - 1);
            beepers[karel_get_y()-1][karel_get_x() - 1] = 1;
            
        }
        karel_move();
    }
}

void navigateGrid() 
{
    for (int i = 0; i < NO_ROWS; i++)
    {
        navigateRow();
        if (i < NO_ROWS - 1)
            shouldGoUpRight() ? goUpRight() : goUpLeft(); 
    }
    
}
void navigateAndCollectBeepers() 
{
    for (int i = 0; i < NO_ROWS; i++)
    {
        collectBeepersInRow();
        if (i < NO_ROWS - 1)
            shouldGoUpRight() ? goUpRight() : goUpLeft(); 
    }
    
}

int sumFirstRow()
{
    int sum = 0;  
    for (int i = 0; i < NO_COLS; i++)
    {
        sum += beepers[0][i];
    }
    return sum; 
}

int sumFirstCol()
{
    int sum = 0;  
    for (int i = 0; i < NO_ROWS; i++)
    {
        sum += beepers[i][0];
    }
    return sum; 
}

void karelGoDown()
{
    karel_turn_left();
    for (int i = 0; i < NO_ROWS - 1; i++)
    {
        karel_move();
    }
}

void moveTo(int row, int col)
{
    for (int i = 0; i < col; i++)
    {
        karel_move();
    }
    karel_turn_left();
    for (int j = 0; j < row; j++)
    {
        karel_move();
    }
}
void studentCode()
{
    navigateAndCollectBeepers();
    int firstRowSum = sumFirstRow();
    int firstColSum = sumFirstCol(); 
    printf("We expect that the first row contains 2 beepers, value= %d\n", firstRowSum); 
    printf("We expect that the first col contains 3 beepers, value= %d\n", firstColSum); 
    karelGoDown();
    karel_turn_left();

    moveTo(2, 3);
    karel_put_beeper();
    karel_move();
    //printMatrix();
}
```