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