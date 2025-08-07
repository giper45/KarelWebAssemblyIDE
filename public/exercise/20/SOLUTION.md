# Solution Karel the Calculator
We first define the BeeperInfo struct to hold the information about the beepers collected by Karel.
```c
typedef struct {
    int numBeepersFirstRow;
    int numBeepersSecondRow;
    int sumBeepers;
    double averageBeepers;
} BeeperInfo;

void printBeeperInfo(BeeperInfo info) {
    printf("First row beepers: %d\n", info.numBeepersFirstRow);
    printf("Second row beepers: %d\n", info.numBeepersSecondRow);
    printf("Total beepers: %d\n", info.sumBeepers);
    printf("Average beepers: %.2f\n", info.averageBeepers);
}
```

We have also defined a utility function `printBeeperInfo` to print the information stored in the `BeeperInfo` struct.
This will be used at the end of the `studentCode` function to display the results.

Now we implement the navigation path between the two rows and collect the beepers.
```c
#define NUM_COLS 10
#define NUM_COLS 10
void studentCode()
{
    BeeperInfo beeper_info; 
    for (int i = 0; i < NUM_COLS - 1; i ++)
    {
        if (beepers_present())
            beeper_info.numBeepersFirstRow++;
        karel_move();

    }
    karel_turn_left();
    karel_move();
    karel_turn_left();
    for (int i = 0; i < NUM_COLS - 1; i ++)
    {
        if (beepers_present())
            beeper_info.numBeepersSecondRow++;
        karel_move();

    }
    beeper_info.sumBeepers = beeper_info.numBeepersSecondRow + beeper_info.numBeepersFirstRow;
    
    beeper_info.averageBeepers = beeper_info.sumBeepers / 2;
    printBeeperInfo(beeper_info);
}
```

After collecting the beepers, we calculate the sum and average of the beepers in both rows.

Then we print the information using the `printBeeperInfo` function.

Complete solution code:
```c
#include "karel.h"
#define REFRESH_RATE 0.1 // 1 second for smooth updates
// Variabili globali di Karel
const char *DIRECTION_NAMES[] = {"Est", "Nord", "Ovest", "Sud"};
void studentCode();

void setup()
{
    // Initialize Karel and world
    karel_init();

    // Put some beeper
    karel_add_beeper(1, 1);
    karel_add_beeper(3, 1);
    karel_add_beeper(5, 1);
    karel_add_beeper(9, 1);
    karel_add_beeper(1, 2);
    karel_add_beeper(4, 2);
    karel_add_beeper(9, 2);
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

typedef struct {
    int numBeepersFirstRow;
    int numBeepersSecondRow;
    int sumBeepers;
    double averageBeepers;
} BeeperInfo;

void printBeeperInfo(BeeperInfo info) {
    printf("First row beepers: %d\n", info.numBeepersFirstRow);
    printf("Second row beepers: %d\n", info.numBeepersSecondRow);
    printf("Total beepers: %d\n", info.sumBeepers);
    printf("Average beepers: %.2f\n", info.averageBeepers);
}

#define NUM_COLS 10
void studentCode()
{
    BeeperInfo beeper_info; 
    for (int i = 0; i < NUM_COLS - 1; i ++)
    {
        if (beepers_present())
            beeper_info.numBeepersFirstRow++;
        karel_move();

    }
    karel_turn_left();
    karel_move();
    karel_turn_left();
    for (int i = 0; i < NUM_COLS - 1; i ++)
    {
        if (beepers_present())
            beeper_info.numBeepersSecondRow++;
        karel_move();

    }
    beeper_info.sumBeepers = beeper_info.numBeepersSecondRow + beeper_info.numBeepersFirstRow;
    
    beeper_info.averageBeepers = beeper_info.sumBeepers / 2;
    printBeeperInfo(beeper_info);
}
```



## How to modify the struct inside a function? 
It is possible to pass the struct by reference (using a pointer) to modify its contents inside a function.
Let's try to create functions to make the code cleaner and more modular.

```c
void incrementBeeperFirstRow(BeeperInfo *info) {
    info->numBeepersFirstRow++;
}
void incrementBeeperSecondRow(BeeperInfo *info) {
    info->numBeepersSecondRow++;
}

void calculateSumAndAverage(BeeperInfo *info) {
    info->sumBeepers = info->numBeepersSecondRow + info->numBeepersFirstRow;
    info->averageBeepers = info->sumBeepers / 2.0;
}
```

As you can see, inside the functions, we use the `->` operator to access the fields of the struct when we pass it by pointer.

Complete solution code with functions:
```c
#include "karel.h"
#define REFRESH_RATE 0.5 // 1 second for smooth updates
// Variabili globali di Karel

#define NUM_COLS 10

const char *DIRECTION_NAMES[] = {"Est", "Nord", "Ovest", "Sud"};
void studentCode();

void setup()
{
    // Initialize Karel and world
    karel_init();

     // Put some beeper
    karel_add_beeper(1, 1);
    karel_add_beeper(3, 1);
    karel_add_beeper(5, 1);
    karel_add_beeper(9, 1);
    karel_add_beeper(1, 2);
    karel_add_beeper(4, 2);
    karel_add_beeper(9, 2);
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
typedef struct {
    int numBeepersFirstRow;
    int numBeepersSecondRow;
    int sumBeepers;
    double averageBeepers;
} BeeperInfo;

void setBeepersFirstRow(BeeperInfo *info, int numBeepers) {
    info->numBeepersFirstRow = numBeepers;
}
void setBeepersSecondRow(BeeperInfo *info, int numBeepers) {
    info->numBeepersSecondRow = numBeepers;
}

void calculateSumAndAverage(BeeperInfo *info) {
    info->sumBeepers = info->numBeepersSecondRow + info->numBeepersFirstRow;
    info->averageBeepers = info->sumBeepers / 2.0;
}

void printBeeperInfo(BeeperInfo info) {
    printf("First row beepers: %d\n", info.numBeepersFirstRow);
    printf("Second row beepers: %d\n", info.numBeepersSecondRow);
    printf("Total beepers: %d\n", info.sumBeepers);
    printf("Average beepers: %.2f\n", info.averageBeepers);
}
int countBeepersInRow()
{
    int count = 0;
    for (int i = 0; i < NUM_COLS - 1; i++)
    {
        if (beepers_present())
            count++;
        karel_move();
    }
    return count;
}
void goToSecondRow()
{
    karel_turn_left();
    karel_move();
    karel_turn_left();
}


void studentCode()
{
    BeeperInfo beeper_info;
    int localCounter = 0;
    int firstRowBeepers = countBeepersInRow();
    setBeepersFirstRow(&beeper_info, firstRowBeepers); 
    goToSecondRow();
    int secondRowBeepers = countBeepersInRow();
    setBeepersSecondRow(&beeper_info, secondRowBeepers);
    calculateSumAndAverage(&beeper_info);
    printBeeperInfo(beeper_info);

}      
````

Now you can start creating more complex exercises using structs and pointers in C.