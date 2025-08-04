#include "karel.h"
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
int i = 0;

static double lastMoveTime = 0;
void loop(double timeSec, double elapsedSec) {
    if(timeSec - lastMoveTime > 1.0) {
        studentCode();
        lastMoveTime = timeSec;
    }
 
}
void studentCode()
{
    drawWorld();
    karel_move();

}





