#include "karel.h"
// Variabili globali di Karel
const char* DIRECTION_NAMES[] = {"Est", "Nord", "Ovest", "Sud"};
void studentCode();

void setup() {
    // Initialize Karel and world
    karel_init();
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

}





