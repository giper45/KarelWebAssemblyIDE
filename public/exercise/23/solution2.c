#include "karel.h"

#define REFRESH_RATE 0.01 // 1 second for smooth updates
// Variabili globali di Karel
const char *DIRECTION_NAMES[] = {"Est", "Nord", "Ovest", "Sud"};
void studentCode();
#define MAX_DIM 100


#define NO_ROWS 8
#define NO_COLS 10
int beepers_in_file[NO_ROWS][NO_COLS] = {0};


void setup()
{
    // Initialize Karel and world
    karel_init();

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



void parse_beeper_position(const char *line, int *x, int *y)
{
    for (int i = 0; i < strlen(line); i++)
    {
        if (line[i] == ',')
        {
            *x = atoi(line);
            *y = atoi(line + i + 1);
            return;
        }
    }
}
void test_parse(const char *filename)
{
    int x = -1, y = -1;
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
        parse_beeper_position(buffer, &x, &y);
        printf("[PARSING] X: %d, Y: %d\n", x, y); 
        
    }
    fclose(file);
}
void fill_beeper_matrix(const char *filename)
{
    int x = -1, y = -1;
    FILE *file = fopen(filename, "r");
    if (!file)
    {
        perror("Error opening file for reading");
        return;
    }
    char buffer[MAX_DIM];
    
    while (fgets(buffer, sizeof(buffer), file))
    {
        parse_beeper_position(buffer, &x, &y);
        if (x >= 0 && x < NO_COLS && y >= 0 && y < NO_ROWS)
        {
            beepers_in_file[y][x]++;
        }
    }
    fclose(file);
}

void print_beeper_matrix()
{
    for (int i = 0; i < NO_ROWS; i++)
    {
        for (int j = 0; j < NO_COLS; j++)
        {
            printf("%d ", beepers_in_file[i][j]);
        }
        printf("\n");
    }
}



#define NUM_COLS 10
void studentCode()
{
    fill_beeper_matrix("beepers.txt");
    test_parse("beepers.txt");
    print_beeper_matrix();
}
