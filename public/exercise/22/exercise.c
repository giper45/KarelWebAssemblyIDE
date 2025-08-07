#include "karel.h"

#define REFRESH_RATE 0.01 // 1 second for smooth updates
// Variabili globali di Karel
const char *DIRECTION_NAMES[] = {"Est", "Nord", "Ovest", "Sud"};
void studentCode();
#define MAX_DIM 100
void setup()
{
    // Initialize Karel and world
    karel_init();

    // Put some beeper
    karel_put_beepers_random_positions(5);
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
        perror("Error opening file for writing");
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
        perror("Error opening file for writing");
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
        perror("Error opening file for reading");
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
        printf("The file could not be opened.\n");
        return;
    }

    while ((ch = fgetc(in_file)) != EOF)
    {
        printf("%c", ch);
    }

    fclose(in_file);
}

#define NUM_COLS 10
void studentCode()
{
    const char *strings[] = {
        "Hello, world!",
        "This is a test.",
        "C programming is fun.",
        "File I/O is useful."};

    write_strings_to_file("output.txt", strings, sizeof(strings) / sizeof(strings[0]));

    read_strings_from_file("output.txt");
    read_strings_from_file("output.txt");

    write_string_to_file("output.txt", 5);
    read_strings_from_file("output.txt");
}