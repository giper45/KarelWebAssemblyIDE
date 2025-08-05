#include "karel.h"
#define REFRESH_RATE 0.3

const char *DIRECTION_NAMES[] = {"East", "North", "West", "South"};
#define GRID_SIZE 5

void studentCode();

void setup()
{
    karel_init();
    // No initial beepers - Karel will place them
    printf("Exercise 12: Zig-Zag Fill\n");
    printf("Karel will fill a 5x5 area with beepers in zig-zag pattern.\n");
}

static double lastMoveTime = 0;

void loop(double timeSec, double elapsedSec)
{
    if (timeSec - lastMoveTime > REFRESH_RATE)
    {
        bool ready = drawWorld();
        if (ready)
            studentCode();
        lastMoveTime = timeSec;
    }
}

enum Phase
{
    FILLING_ROW,
    TURNING_AROUND,
    MOVING_TO_NEXT_ROW,
    COMPLETE
};

void karel_turn_right()
{
    for (int i = 0; i < 3; i++)
        karel_turn_left();
}

void studentCode()
{
    static bool exerciseComplete = false;
    static int currentRow = 1;
    static int currentCol = 1;
    static enum Phase currentPhase = FILLING_ROW;
    static int beepersPlaced = 0;
    const int no_moves = 5;
    const int no_rows = 5;

    if (!exerciseComplete)
    {
        for (int i = 0; i < no_rows; i++)
        {
            // Place beeper at start of each row
            karel_put_beeper();
            beepersPlaced++;
            printf("Row %d: Placed beeper #%d at (%d,%d)\n", i + 1, beepersPlaced, karel_get_x(), karel_get_y());
            
            // Move across the row placing beepers
            for (int j = 0; j < no_moves - 1; j++) // no_moves - 1 perché il primo beeper è già piazzato
            {
                karel_move();
                karel_put_beeper();
                beepersPlaced++;
                printf("Row %d: Placed beeper #%d at (%d,%d)\n", i + 1, beepersPlaced, karel_get_x(), karel_get_y());
            }
            
            // IMPORTANTE: Solo se NON siamo all'ultima riga, muoviti verso l'alto
            if (i < no_rows - 1) 
            {
                if (facing_east())
                {
                    karel_turn_left();   // Gira a nord
                    karel_move();        // Muovi verso l'alto
                    karel_turn_left();   // Gira a ovest per la prossima riga
                }
                else if (facing_west())
                {
                    karel_turn_right();  // Gira a nord  
                    karel_move();        // Muovi verso l'alto
                    karel_turn_right();  // Gira a est per la prossima riga
                }
                printf("Moving to row %d, now facing %s\n", i + 2, facing_east() ? "East" : "West");
            }
            else 
            {
                // Ultima riga completata - non muoverti verso l'alto
                printf("Final row completed! Staying at position (%d,%d)\n", karel_get_x(), karel_get_y());
            }
        }
        
        printf("Zig-zag fill complete! %d beepers placed in %dx%d area.\n", beepersPlaced, no_moves, no_rows);
        printf("Final position: (%d,%d) facing %s\n", karel_get_x(), karel_get_y(), DIRECTION_NAMES[karel_get_direction()]);
        exerciseComplete = true;
    }
}