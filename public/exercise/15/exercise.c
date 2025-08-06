#include "karel.h"
#define REFRESH_RATE 0.5

const char *DIRECTION_NAMES[] = {"Est", "Nord", "Ovest", "Sud"};
void studentCode();

void setup()
{
    karel_init();

    // Karel starts with 3 beepers in bag
    karel_set_bag_beepers(3);

    // Place a beeper for Karel to pick up at (4,2)
    karel_add_beeper(4, 2);
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

// TODO: Define the Command enum
enum Command
{
    MOVE,
    TURN_LEFT,
    TURN_RIGHT,
    PICK_BEEPER,
    PUT_BEEPER
};

// TODO: Implement helper function for turning right
void turn_right()
{
    // HINT: Right turn = 3 left turns
}

// TODO: Implement command execution function
void execute_command(enum Command cmd)
{
    switch (cmd)
    {
    case MOVE:
        // TODO: Check if front is clear, then move
        break;
    case TURN_LEFT:
        // TODO: Turn left
        break;
    case TURN_RIGHT:
        // TODO: Turn right
        break;
    case PICK_BEEPER:
        // TODO: Pick beeper if present
        break;
    case PUT_BEEPER:
        // TODO: Put beeper if available
        break;
    default:
        printf("Unknown command!\n");
        break;
    }
}

// TODO: Implement sequence execution function
void execute_sequence(enum Command commands[], int length)
{
    // Execute each command in the array
    for (int i = 0; i < length; i++)
    {
        printf("Executing command %d...\n", i + 1);
        // TODO: Execute commands[i]
    }
}


void studentCode()
{
    bool sequenceComplete = false;

    if (!sequenceComplete)
    {
        // Define the command sequence
        enum Command sequence[] = {
            MOVE, MOVE, TURN_RIGHT, MOVE, PICK_BEEPER,
            TURN_LEFT, MOVE, MOVE, TURN_LEFT, MOVE,
            PUT_BEEPER, TURN_RIGHT, MOVE};

        int length = sizeof(sequence) / sizeof(sequence[0]);

        printf("Starting command sequence execution...\n");
        printf("Karel position: (%d, %d) - Direction: %s\n",
               karel_get_x(), karel_get_y(), DIRECTION_NAMES[karel_get_direction()]);

        // TODO: Execute the sequence
        // execute_sequence(sequence, length);

        sequenceComplete = true;
        printf("Command sequence completed!\n");
    }
}
