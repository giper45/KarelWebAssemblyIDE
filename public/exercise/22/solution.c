#include "karel.h"

#define REFRESH_RATE 0.1// 1 second for smooth updates
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

void navigateAndCollectBeepers(int positions[NO_COLS][NO_ROWS])
{
    void (*moveFunction)();
    for (int i = 0; i < NO_ROWS; i++)
    {
        for (int j = 0 ; j < NO_COLS - 1; j++)
        {
            if (beepers_present())
            {
                printf("Found a beeper!\n");
                karel_pick_beeper();
                positions[karel_get_x()][karel_get_y()]++;
            }

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
    for (int i = 0; i < NO_ROWS; i++)
    {
        for (int j = 0; j < NO_COLS; j++)
        {
            printf("(%d, %d): %d\n", j + 1, i + 1, positions[j][i]);
        }
    }
}
void studentCode()
{
    int beeperPositions[NO_COLS][NO_ROWS] = {0};
    
    navigateAndCollectBeepers(beeperPositions);
}