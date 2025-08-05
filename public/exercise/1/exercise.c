#include "karel.h"
#define REFRESH_RATE 1.0 // 1 second for smooth updates
// Variabili globali di Karel
const char* DIRECTION_NAMES[] = {"Est", "Nord", "Ovest", "Sud"};
void studentCode();

void setup() {
    // Initialize Karel and world
    karel_init();
    
    // Put some beeper 
    karel_add_beeper(3, 2);
    karel_add_beeper(5, 4);
    karel_add_beeper(7, 3);
    karel_add_beeper(2, 6);
    karel_add_horizontal_wall(3, 3, 2); // Horizontal wall (3,2)
    karel_add_vertical_wall(5, 1, 2);   // Vertical wall (5,1)
}

static double lastMoveTime = 0;
void loop(double timeSec, double elapsedSec) {
    if(timeSec - lastMoveTime > REFRESH_RATE) { // Check frequently for smooth timing
        bool ready = drawWorld();
        if (ready)
            studentCode();
        lastMoveTime = timeSec;
    }
}

void studentCode()
{
    // Ora karel_move aggiunge azioni al buffer invece di muoversi immediatamente
    for (int i = 0; i < 2; i++)
    {
        karel_move();
    }
    karel_turn_left();
    karel_move();
}