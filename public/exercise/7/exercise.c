#include "karel.h"
#define REFRESH_RATE 0.5 // 1 second for smooth updates

const char *DIRECTION_NAMES[] = {"Est", "Nord", "Ovest", "Sud"};
void studentCode();

void setup()
{
    karel_init();
    // Create obstacles along the corridor for Karel to avoid
    // Obstacles are vertical walls that block forward movement
    karel_add_vertical_wall(3, 1, 1); // Obstacle at position 3
    karel_add_vertical_wall(6, 1, 1); // Obstacle at position 6
    karel_add_vertical_wall(8, 1, 1); // Obstacle at position 8
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


// Helper function to turn right (3 left turns)
void turn_right()
{
    karel_turn_left();
    karel_turn_left();
    karel_turn_left();
}

void studentCode()
{

        // TODO: Implement obstacle avoidance logic
        // 1. Check if front is clear
        // 2. If clear, move forward normally
        // 3. If blocked, execute avoidance maneuver:
        //    a. Turn right (up)
        //    b. Move forward to clear obstacle
        //    c. Turn right (east)
        //    d. Move forward along parallel path
        //    e. Turn right (down)
        //    f. Move forward to return to main path
        //    g. Turn right (east) to resume normal direction
        // 4. Check for mission completion at end of corridor

}