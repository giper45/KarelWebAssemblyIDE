#include "karel.h"
#define REFRESH_RATE 0.5 // 1 second for smooth updates
// Variabili globali di Karel
const char* DIRECTION_NAMES[] = {"Est", "Nord", "Ovest", "Sud"};

void setup() {
    // Inizializza Karel e il mondo
    karel_init();
    
    // Aggiungi alcuni beeper nel mondo
    karel_add_beeper(3, 2);
    karel_add_beeper(5, 4);
    karel_add_beeper(7, 3);
    karel_add_beeper(2, 6);
    karel_add_horizontal_wall(3, 2, 2); // Horizontal wall (3,2)
    karel_add_vertical_wall(5, 1, 2);   // Vertical wall (5,1)
}
int i = 0;

void draw()
{
    canvas_setFillStyleZ("white");
    canvas_fillRect(0, 0, 800, 600);
    drawWalls();
    drawGrid();
    drawBeepers();
    drawKarel();
    drawInfo();

}


void loop(double timeSec, double elapsedSec) {
    draw();
    i++;
    if (i == 2)
    {
      printf("Put beeper");
      karel_put_beeper();
    }
    
    // Logica di Karel - Muoviti e raccogli beeper!
    static double lastMoveTime = 0;
    if(timeSec - lastMoveTime > REFRESH_RATE) { // Check frequently for smooth timing
        
        if(beepers_present()) {
            karel_pick_beeper();
        }
        
        // If you can go ahead continue
        if(front_is_clear()) {
            karel_move();
        } else {
            // Otherwise, turn left
            karel_turn_left();
        }
        
        lastMoveTime = timeSec;
    }
}