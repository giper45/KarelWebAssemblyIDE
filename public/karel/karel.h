#ifndef KAREL_H_
#define KAREL_H_

#include <canvas_main.h>
#include <math.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define KAREL_ERROR_START "\n\x1b[91m[KAREL_ERROR]"
#define KAREL_ERROR_END "\x1b[0m\n"

// Auto-flush printf for real-time output in WebAssembly
#ifdef __EMSCRIPTEN__
    #define printf(...) do { printf(__VA_ARGS__); fflush(stdout); } while(0)
#elif defined(__wasm__) || defined(__wasm32__)
    #define printf(...) do { printf(__VA_ARGS__); fflush(stdout); } while(0)
#endif


typedef struct {
    FILE *file;
    bool eof_written;
} KarelFileState;


#define KAREL_MAX_OPEN_FILES 32
static KarelFileState karel_file_states[KAREL_MAX_OPEN_FILES];

// Cerca lo stato associato al file
static int karel_find_file_state(FILE *file) {
    for (int i = 0; i < KAREL_MAX_OPEN_FILES; i++) {
        if (karel_file_states[i].file == file)
            return i;
    }
    return -1;
}

// Registra un nuovo file aperto
static void karel_register_file(FILE *file) {
    for (int i = 0; i < KAREL_MAX_OPEN_FILES; i++) {
        if (karel_file_states[i].file == NULL) {
            karel_file_states[i].file = file;
            karel_file_states[i].eof_written = false;
            return;
        }
    }
}

// Cancella lo stato del file chiuso
static void karel_unregister_file(FILE *file) {
    int idx = karel_find_file_state(file);
    if (idx >= 0) {
        karel_file_states[idx].file = NULL;
        karel_file_states[idx].eof_written = false;
    }
}

// Sostituisci fopen con karel_fopen
static inline FILE* karel_fopen(const char *path, const char *mode) {
    FILE *file = fopen(path, mode);
    if (file) karel_register_file(file);
    return file;
}
#ifdef fopen
#undef fopen
#endif
#define fopen karel_fopen




static inline void karel_setup_printf(const char* format, ...) {
    va_list args;
    va_start(args, format);
    vprintf(format, args);
    va_end(args);
    fflush(stdout);
}


// Funzione personalizzata per fprintf che fa flush immediato
static inline int karel_fprintf(FILE *file, const char *format, ...) {
    va_list args;
    va_start(args, format);
    int ret = vfprintf(file, format, args);
    va_end(args);
    fflush(file);
    return ret;
}

// Macro per sostituire fprintf con la versione personalizzata
#ifdef fprintf
#undef fprintf
#endif
#define fprintf karel_fprintf

/*
// Funzione personalizzata per fputs che fa flush immediato
static inline int karel_fputs(const char *str, FILE *file) {
    return karel_fprintf(file, "%s", str);
}

// Macro per sostituire fputs con la versione personalizzata
#ifdef fputs
#undef fputs
#endif
#define fputs karel_fputs
*/
// Funzione personalizzata per fclose che scrive "EOF\n" prima di chiudere
// static inline int karel_fclose(FILE *file) {
//     fprintf(file, "EOF\n");
//     fflush(file);
//     return fclose(file);
// }

// Sostituisci fclose con karel_fclose
static inline int karel_fclose(FILE *file) {
    int idx = karel_find_file_state(file);
    if (idx >= 0 && !karel_file_states[idx].eof_written) {
        fprintf(file, "EOF\n");
        fflush(file);
        karel_file_states[idx].eof_written = true;
    }
    karel_unregister_file(file);
    return fclose(file);
}

// // Macro per sostituire fclose con la versione personalizzata
#ifdef fclose
#undef fclose
#endif
#define fclose karel_fclose

// Funzione personalizzata per fgets che si ferma su "EOF\n"
static inline char* karel_fgets(char *buffer, int size, FILE *file) {
    char *ret = fgets(buffer, size, file);
    if (ret && strcmp(buffer, "EOF\n") == 0) return NULL;
    return ret;
}
// Macro per sostituire fgets con la versione personalizzata
#ifdef fgets
#undef fgets
#endif
#define fgets karel_fgets

static inline int karel_fgetc(FILE *file) {
    static char line_buffer[256];
    static int buffer_pos = 0;
    static int buffer_len = 0;

    // Se il buffer è vuoto, leggi una nuova riga
    if (buffer_pos >= buffer_len) {
        char *ret = karel_fgets(line_buffer, sizeof(line_buffer), file);
        if (!ret) return EOF;
        buffer_len = strlen(line_buffer);
        buffer_pos = 0;
    }

    // Restituisci il prossimo carattere dal buffer
    return (unsigned char)line_buffer[buffer_pos++];
}
#ifdef fgetc
#undef fgetc
#endif
#define fgetc karel_fgetc





// Karel's world configuration
#define WORLD_WIDTH 10
#define WORLD_HEIGHT 8
#define CELL_SIZE 60
#define OFFSET_X 50
#define OFFSET_Y 50


#define KAREL_MOVE_BUFFER_SIZE 5000

void karel_write_random_positions_to_file(const char *filename, int count) {
    FILE *file = fopen(filename, "w");
    if (!file) {
        printf("[-] Cannot write file\n");
        return;
    }
    
    for (int i = 0; i < count; ++i) {
        int x = (int)(canvas_getRandomNumber() * WORLD_WIDTH) + 1;
        int y = (int)(canvas_getRandomNumber() * WORLD_HEIGHT) + 1;
        fprintf(file, "%d,%d\n", x, y);
    }

    fclose(file);
}



typedef enum {
    KAREL_ACTION_MOVE,
    KAREL_ACTION_TURN_LEFT,
    KAREL_ACTION_PICK_BEEPER,
    KAREL_ACTION_PUT_BEEPER
} KarelActionType;


typedef struct {
    KarelActionType type;
    // Eventually other parameters for future actions
} KarelAction;


typedef struct {
    KarelAction actions[KAREL_MOVE_BUFFER_SIZE];
    int front;  // Index of the first element
    int rear;   // Index where to insert the next element
    int count;  // Number of elements in the buffer
} KarelActionBuffer;

// Forward declaration - the actual struct is private
typedef struct Karel Karel;
// To check the conditions we implement a simulated state of Karel
// This allows us to simulate Karel's actions without modifying the actual state
// The buffer will be used after in the drawWorld function to render Karel each refresh rate
typedef struct {
    int x, y;
    int direction;
    bool beepers[WORLD_WIDTH + 1][WORLD_HEIGHT + 1];
    int bag_beepers;
} KarelSimulatedState;

// Karel's state - INTERNAL USE ONLY
struct Karel
{
    int x, y;                                        // Position (1-based like in Karel's world)
    int direction;                                   // 0=East, 1=North, 2=West, 3=South
    bool beepers[WORLD_WIDTH + 1][WORLD_HEIGHT + 1]; // Beepers in the world
    int bag_beepers;                                 // Beepers in Karel's bag
    // Walls: true = wall present
    bool horizontal_walls[WORLD_WIDTH + 1][WORLD_HEIGHT + 2]; // Horizontal walls (above each cell)
    bool vertical_walls[WORLD_WIDTH + 2][WORLD_HEIGHT + 1];   // Vertical walls (to the left of each cell)
} __attribute__((deprecated("Direct access to karel struct is discouraged. Use accessor functions instead.")));

// Global Karel variable - INTERNAL USE ONLY  
static Karel karel __attribute__((deprecated("Direct access to karel is discouraged. Use karel_get_x(), karel_get_y(), karel_get_direction(), karel_get_bag_beepers() instead.")));
static KarelActionBuffer karel_buffer;


// Advanced accessor functions that return simulated state (including pending actions)
// Use these for logic that needs to account for buffered actions
static inline int karel_get_x(void);
static inline int karel_get_y(void);
static inline int karel_get_bag_beepers(void);
static inline KarelSimulatedState karel_simulate_state();
// Buffering KAREL strings
#define KAREL_LOG_BUFFER_SIZE 1024
#define KAREL_LOG_STRING_SIZE 512

typedef struct {
    char message[KAREL_LOG_STRING_SIZE];
} KarelLogEntry;

typedef struct {
    KarelLogEntry entries[KAREL_LOG_BUFFER_SIZE];
    int front;
    int rear;
    int count;
} KarelLogBuffer;

static KarelLogBuffer karel_log_buffer;

typedef enum {
    KAREL_BUFFER_ACTION,
    KAREL_BUFFER_LOG
} KarelBufferEntryType;

typedef struct {
    KarelBufferEntryType type;
    union {
        KarelAction action;
        char log[KAREL_LOG_STRING_SIZE];
    };
} KarelUnifiedBufferEntry;

#define KAREL_UNIFIED_BUFFER_SIZE 4096
typedef struct {
    KarelUnifiedBufferEntry entries[KAREL_UNIFIED_BUFFER_SIZE];
    int front, rear, count;
} KarelUnifiedBuffer;

static KarelUnifiedBuffer karel_unified_buffer;

static inline void karel_log_buffer_enqueue(const char* format, ...) {
    if (karel_log_buffer.count >= KAREL_LOG_BUFFER_SIZE) return;
    va_list args;
    va_start(args, format);
    vsnprintf(karel_log_buffer.entries[karel_log_buffer.rear].message, KAREL_LOG_STRING_SIZE, format, args);
    va_end(args);
    karel_log_buffer.rear = (karel_log_buffer.rear + 1) % KAREL_LOG_BUFFER_SIZE;
    karel_log_buffer.count++;
}

static inline void karel_log_buffer_flush() {
    while (karel_log_buffer.count > 0) {
        printf("%s", karel_log_buffer.entries[karel_log_buffer.front].message);
        karel_log_buffer.front = (karel_log_buffer.front + 1) % KAREL_LOG_BUFFER_SIZE;
        karel_log_buffer.count--;
    }
}

static inline void karel_log_buffer_flush_one() {
    if (karel_log_buffer.count > 0) {
        // Usa vprintf per evitare ricorsione se printf è ridefinito
        #ifdef __EMSCRIPTEN__
            #define printf(...) do { printf(__VA_ARGS__); fflush(stdout); } while(0)
        #elif defined(__wasm__) || defined(__wasm32__)
            #define printf(...) do { printf(__VA_ARGS__); fflush(stdout); } while(0)
        #endif
        // printf("karel_buffer_count: %d\n", karel_buffer.count);
        // printf("Karel log buffer: %d entries\n", karel_log_buffer.count);
        // printf("Karel log buffer front: %d, rear: %d\n", karel_log_buffer.front, karel_log_buffer.rear);
        // printf("Karel buffer front : %d, rear: %d, count: %d\n", karel_buffer.front, karel_buffer.rear, karel_buffer.count);
        // printf("%s", karel_log_buffer.entries[karel_log_buffer.front].message);
        karel_log_buffer.front = (karel_log_buffer.front + 1) % KAREL_LOG_BUFFER_SIZE;
        karel_log_buffer.count--;
    }
}
#ifdef printf
#undef printf
#endif
#define printf(...) karel_buffer_enqueue_log(__VA_ARGS__)

// In drawWorld (o dove vuoi sincronizzare l'output), svuota il buffer:
static inline void karel_flush_print_buffer() {
    karel_log_buffer_flush();
}

// Control functions
static inline bool karel_real_front_is_clear()
{
    #pragma GCC diagnostic push
    #pragma GCC diagnostic ignored "-Wdeprecated-declarations"
    int new_x = karel.x;
    int new_y = karel.y;

    switch (karel.direction)
    {
    case 0: // East
        new_x++;
        // Check vertical wall to the right of current cell
        if (karel.vertical_walls[karel.x + 1][karel.y]) return false;
        break;
    case 1: // North
        new_y++;
        // Check horizontal wall above current cell
        if (karel.horizontal_walls[karel.x][karel.y + 1]) return false;
        break;
    case 2: // West
        new_x--;
        // Check vertical wall to the left of current cell
        if (karel.vertical_walls[karel.x][karel.y]) return false;
        break;
    case 3: // South
        new_y--;
        // Check horizontal wall below current cell
        if (karel.horizontal_walls[karel.x][karel.y]) return false;
        break;
    }

    return (new_x >= 1 && new_x <= WORLD_WIDTH && new_y >= 1 && new_y <= WORLD_HEIGHT);
    #pragma GCC diagnostic pop
}

static inline void karel_buffer_init() {
    karel_buffer.front = 0;
    karel_buffer.rear = 0;
    karel_buffer.count = 0;
}

static inline bool karel_buffer_is_empty() {
    return karel_buffer.count == 0;
}

static inline bool karel_buffer_is_full() {
    return karel_buffer.count >= KAREL_MOVE_BUFFER_SIZE;
}

static inline void karel_buffer_enqueue(KarelActionType action_type) {
    if (karel_buffer_is_full()) {
        // printf("Karel buffer is full! Cannot add more actions.\n");
        return;
    }
    
    karel_buffer.actions[karel_buffer.rear].type = action_type;
    karel_buffer.rear = (karel_buffer.rear + 1) % KAREL_MOVE_BUFFER_SIZE;
    karel_buffer.count++;
    
    // printf("Action enqueued. Buffer count: %d\n", karel_buffer.count);
}

static inline bool karel_buffer_dequeue(KarelAction* action) {
    if (karel_buffer_is_empty()) {
        return false;
    }
    
    *action = karel_buffer.actions[karel_buffer.front];
    karel_buffer.front = (karel_buffer.front + 1) % KAREL_MOVE_BUFFER_SIZE;
    karel_buffer.count--;
    
    // printf("Action dequeued. Buffer count: %d\n", karel_buffer.count);
    return true;
}

static inline void karel_buffer_enqueue_action(KarelActionType action_type) {
    if (karel_unified_buffer.count >= KAREL_UNIFIED_BUFFER_SIZE) {
        karel_setup_printf(KAREL_ERROR_START " Karel action buffer is full!!! Are you doing an infinite loop?" KAREL_ERROR_END);
        return;
    }
    karel_unified_buffer.entries[karel_unified_buffer.rear].type = KAREL_BUFFER_ACTION;
    karel_unified_buffer.entries[karel_unified_buffer.rear].action.type = action_type;
    karel_unified_buffer.rear = (karel_unified_buffer.rear + 1) % KAREL_UNIFIED_BUFFER_SIZE;
    karel_unified_buffer.count++;
}

static inline void karel_buffer_enqueue_log(const char* format, ...) {
            karel_setup_printf(KAREL_ERROR_START " Karel log buffer is full!!! Are you doing an infinite loop?" KAREL_ERROR_END);
    if (karel_unified_buffer.count >= KAREL_UNIFIED_BUFFER_SIZE) {
        karel_setup_printf(KAREL_ERROR_START " Karel log buffer is full!!! Are you doing an infinite loop?" KAREL_ERROR_END);
        return;
    }
    karel_unified_buffer.entries[karel_unified_buffer.rear].type = KAREL_BUFFER_LOG;
    va_list args;
    va_start(args, format);
    vsnprintf(karel_unified_buffer.entries[karel_unified_buffer.rear].log, KAREL_LOG_STRING_SIZE, format, args);
    va_end(args);
    karel_unified_buffer.rear = (karel_unified_buffer.rear + 1) % KAREL_UNIFIED_BUFFER_SIZE;
    karel_unified_buffer.count++;
}



// Directions
extern const char *DIRECTION_NAMES[];

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wdeprecated-declarations"
// Inline implementations
// Internal initialization function that bypasses deprecation warnings

static inline void karel_set_bag_beepers(int beepers) {
    karel.bag_beepers = beepers;
}
static inline void karel_internal_init_state() {
    // Initialize Karel
    karel.x = 1;
    karel.y = 1;
    karel.direction = 0; // Facing East
    karel.bag_beepers = 10;

    // Initialize world without beepers
    for (int i = 0; i <= WORLD_WIDTH; i++) {
        for (int j = 0; j <= WORLD_HEIGHT; j++) {
            karel.beepers[i][j] = false;
        }
    }
    
    // Initialize walls
    for (int i = 0; i <= WORLD_WIDTH; i++) {
        for (int j = 0; j <= WORLD_HEIGHT + 1; j++) {
            karel.horizontal_walls[i][j] = false;
        }
    }
    for (int i = 0; i <= WORLD_WIDTH + 1; i++) {
        for (int j = 0; j <= WORLD_HEIGHT; j++) {
            karel.vertical_walls[i][j] = false;
        }
    }
    
}



static inline void karel_init()
{
    canvas_setWidth(800);
    canvas_setHeight(600);

    // Initialize Karel
    karel_internal_init_state();

    karel_buffer_init();
}

static inline int karel_get_x(void) {
    KarelSimulatedState simulated = karel_simulate_state();
    return simulated.x;
}

static inline int karel_get_y(void) {
    KarelSimulatedState simulated = karel_simulate_state();
    return simulated.y;
}
static inline int karel_get_direction(void) {
    KarelSimulatedState simulated = karel_simulate_state();
    return simulated.direction;
}
static inline int karel_get_bag_beepers(void) {
    KarelSimulatedState simulated = karel_simulate_state();
    return simulated.bag_beepers;
}

static inline void karel_execute_action(KarelAction action) {

    switch (action.type) {
        case KAREL_ACTION_MOVE:
            if (karel_real_front_is_clear()) {
                switch (karel.direction) {
                case 0: karel.x++; break; // East
                case 1: karel.y++; break; // North
                case 2: karel.x--; break; // West
                case 3: karel.y--; break; // South
                }
            } else {
                printf(KAREL_ERROR_START " Karel cannot move forward due to walls or boundaries!!!" KAREL_ERROR_END);
            }
            break;
            
        case KAREL_ACTION_TURN_LEFT:
            karel.direction = (karel.direction + 1) % 4;
            break;
            
        case KAREL_ACTION_PICK_BEEPER:
            if (karel.beepers[karel.x][karel.y]) {
                karel.beepers[karel.x][karel.y] = false;
                karel.bag_beepers++;
            } else {
                printf(KAREL_ERROR_START " Karel cannot pick up a beeper because there are none at the current position!!!" KAREL_ERROR_END);
            }
            break;
            
        case KAREL_ACTION_PUT_BEEPER:
            if (karel.bag_beepers > 0) {
                karel.beepers[karel.x][karel.y] = true;
                karel.bag_beepers--;
            } else {
                printf(KAREL_ERROR_START " Karel cannot put down a beeper because the bag is empty!!!" KAREL_ERROR_END);
            }
            break;
    }
}

static inline void karel_process_next_action() {
    KarelAction action;
    if (karel_buffer_dequeue(&action)) {
        karel_execute_action(action);
    }
}

static inline void karel_process_action_log() {
    if (karel_unified_buffer.count > 0) {
        KarelUnifiedBufferEntry* entry = &karel_unified_buffer.entries[karel_unified_buffer.front];
    if (entry->type == KAREL_BUFFER_ACTION) {
        karel_execute_action(entry->action);
    } else if (entry->type == KAREL_BUFFER_LOG) {
        // Usa la vera printf qui!
        #undef printf
        #ifdef __EMSCRIPTEN__
            #define printf(...) do { printf(__VA_ARGS__); fflush(stdout); } while(0)
        #elif defined(__wasm__) || defined(__wasm32__)
            #define printf(...) do { printf(__VA_ARGS__); fflush(stdout); } while(0)
        #endif
        printf("%s", entry->log);
        #undef printf
        #define printf(...) karel_buffer_enqueue_log(__VA_ARGS__)
    }
    karel_unified_buffer.front = (karel_unified_buffer.front + 1) % KAREL_UNIFIED_BUFFER_SIZE;
    karel_unified_buffer.count--;
}
}

static inline void karel_add_beeper(int x, int y)
{
    if (x >= 1 && x <= WORLD_WIDTH && y >= 1 && y <= WORLD_HEIGHT)
    {
        karel.beepers[x][y] = true;
    }
}

// Functions to add walls
static inline void karel_add_horizontal_wall(int x, int y, int length = 1)
{
    // Adds horizontal walls above cells from (x, y) for 'length' cells along the x-axis
    for (int i = 0; i < length; i++)
    {
        int wall_x = x + i;
        if (wall_x >= 1 && wall_x <= WORLD_WIDTH && y >= 1 && y <= WORLD_HEIGHT + 1)
        {
            karel.horizontal_walls[wall_x][y] = true;
        }
    }
}

static inline void karel_add_vertical_wall(int x, int y, int length = 1)
{
    // Adds vertical walls to the left of cells from (x, y) for 'length' cells along the y-axis
    for (int i = 0; i < length; i++)
    {
        int wall_y = y + i;
        if (x >= 1 && x <= WORLD_WIDTH + 1 && wall_y >= 1 && wall_y <= WORLD_HEIGHT)
        {
            karel.vertical_walls[x][wall_y] = true;
        }
    }
}

static inline void karel_put_beepers_random_positions(int count) {
    for (int i = 0; i < count; i++) {
        int x = (int)(canvas_getRandomNumber() * WORLD_WIDTH) + 1;
        int y = (int)(canvas_getRandomNumber() * WORLD_HEIGHT) + 1;
        karel_add_beeper(x, y);
    }
}
static inline void drawGrid()
{
    canvas_setStrokeStyleZ("lightgray");
    canvas_setLineWidth(1);

    // Vertical lines
    for (int i = 0; i <= WORLD_WIDTH; i++)
    {
        double x = OFFSET_X + i * CELL_SIZE;
        canvas_beginPath();
        canvas_moveTo(x, OFFSET_Y);
        canvas_lineTo(x, OFFSET_Y + WORLD_HEIGHT * CELL_SIZE);
        canvas_stroke();
    }

    // Horizontal lines
    for (int j = 0; j <= WORLD_HEIGHT; j++)
    {
        double y = OFFSET_Y + j * CELL_SIZE;
        canvas_beginPath();
        canvas_moveTo(OFFSET_X, y);
        canvas_lineTo(OFFSET_X + WORLD_WIDTH * CELL_SIZE, y);
        canvas_stroke();
    }

    // Thicker outer border
    canvas_setStrokeStyleZ("black");
    canvas_setLineWidth(3);
    canvas_strokeRect(OFFSET_X, OFFSET_Y, WORLD_WIDTH * CELL_SIZE, WORLD_HEIGHT * CELL_SIZE);
}

static inline void drawWalls()
{
    canvas_setStrokeStyleZ("red");
    canvas_setLineWidth(4);
    
    // Draw horizontal walls
    for (int i = 1; i <= WORLD_WIDTH; i++)
    {
        for (int j = 1; j <= WORLD_HEIGHT + 1; j++)
        {
            if (karel.horizontal_walls[i][j])
            {
                double x1 = OFFSET_X + (i - 1) * CELL_SIZE;
                double x2 = OFFSET_X + i * CELL_SIZE;
                double y = OFFSET_Y + (WORLD_HEIGHT - j + 1) * CELL_SIZE;
                
                canvas_beginPath();
                canvas_moveTo(x1, y);
                canvas_lineTo(x2, y);
                canvas_stroke();
            }
        }
    }
    
    // Draw vertical walls
    for (int i = 1; i <= WORLD_WIDTH + 1; i++)
    {
        for (int j = 1; j <= WORLD_HEIGHT; j++)
        {
            if (karel.vertical_walls[i][j])
            {
                double x = OFFSET_X + (i - 1) * CELL_SIZE;
                double y1 = OFFSET_Y + (WORLD_HEIGHT - j) * CELL_SIZE;
                double y2 = OFFSET_Y + (WORLD_HEIGHT - j + 1) * CELL_SIZE;
                
                canvas_beginPath();
                canvas_moveTo(x, y1);
                canvas_lineTo(x, y2);
                canvas_stroke();
            }
        }
    }
}

static inline void drawBeepers()
{
    canvas_setFillStyleZ("blue");

    for (int i = 1; i <= WORLD_WIDTH; i++)
    {
        for (int j = 1; j <= WORLD_HEIGHT; j++)
        {
            if (karel.beepers[i][j])
            {
                double x = OFFSET_X + (i - 1) * CELL_SIZE + CELL_SIZE / 2;
                double y = OFFSET_Y + (WORLD_HEIGHT - j) * CELL_SIZE + CELL_SIZE / 2;

                // Draw a diamond (beeper)
                canvas_beginPath();
                canvas_moveTo(x, y - 15);
                canvas_lineTo(x + 15, y);
                canvas_lineTo(x, y + 15);
                canvas_lineTo(x - 15, y);
                canvas_closePath();
                canvas_fill(FILL_RULE_NONZERO);
            }
        }
    }
}


static inline void drawKarel()
{
    double x = OFFSET_X + (karel.x - 1) * CELL_SIZE + CELL_SIZE / 2;
    double y = OFFSET_Y + (WORLD_HEIGHT - karel.y) * CELL_SIZE + CELL_SIZE / 2;

    // Base/Dark purple pedestal raised (without body)
    canvas_setFillStyleZ("#4C1D95");  // Dark purple
    canvas_fillRect(x - 20, y - 15, 40, 30);  // Higher rectangle
    
    // Pedestal border for depth
    canvas_setFillStyleZ("#3B1A78");
    canvas_fillRect(x - 20, y - 15, 40, 3);   // Top
    canvas_fillRect(x - 20, y - 15, 3, 30);   // Left
    canvas_fillRect(x + 17, y - 15, 3, 30);   // Right
    canvas_fillRect(x - 20, y + 12, 40, 3);   // Bottom

    // // "WA" text centered in the pedestal
    // canvas_setFillStyleZ("white");
    // canvas_setFontZ("bold 12px Arial");
    // canvas_fillText("WA", 2, x - 10, y + 5);

    // Dark blue head positioned above the purple rectangle
    canvas_setFillStyleZ("#1E3A8A");  // Dark blue
    canvas_fillRect(x - 15, y - 30, 30, 18);  // Main head
    canvas_fillRect(x - 12, y - 32, 24, 4);   // Rounded top
    canvas_fillRect(x - 10, y - 34, 20, 4);   // More rounded top

    // // Dark gray metallic antennas
    // canvas_setFillStyleZ("#4B5563");  // Dark gray metallic
    // canvas_fillRect(x - 17, y - 36, 3, 8);    // Left antenna
    // canvas_fillRect(x + 14, y - 36, 3, 8);    // Right antenna
    
    // // Antenna tips
    // canvas_fillRect(x - 16, y - 38, 1, 4);    // Left tip
    // canvas_fillRect(x + 15, y - 38, 1, 4);    // Right tip

    // Eyes
    canvas_setFillStyleZ("white");
    canvas_fillRect(x - 12, y - 28, 6, 6);    // Left eye base
    canvas_fillRect(x + 6, y - 28, 6, 6);     // Right eye base
    
    canvas_setFillStyleZ("#90EE90");  // Light green
    canvas_fillRect(x - 11, y - 27, 4, 4);    // Left iris
    canvas_fillRect(x + 7, y - 27, 4, 4);     // Right iris
    
    // Pupils removed for a simpler look

    // Friendly smile
    // canvas_setFillStyleZ("white");
    // canvas_fillRect(x - 6, y - 20, 12, 2);    // Smile base
    // canvas_fillRect(x - 5, y - 18, 2, 1);     // Left corner
    // canvas_fillRect(x + 3, y - 18, 2, 1);     // Right corner
    // Direction indicator - orange arrow more visible
    canvas_setFillStyleZ("#eb0f0fff");  // Orange for contrast
    
    // Directional arrow based on direction using canvas_beginPath
      // Directional arrow based on direction using canvas_beginPath
    // Larger directional arrow moved laterally
    canvas_beginPath();
    switch (karel.direction) {
    case 0: // East - arrow points right
        canvas_moveTo(x + 30, y);        // Arrow tip (even further away)
        canvas_lineTo(x + 21, y - 6);    // Upper side
        canvas_lineTo(x + 24, y - 3);    // Upper indent
        canvas_lineTo(x + 17, y - 3);    // Upper base
        canvas_lineTo(x + 17, y + 3);    // Lower base
        canvas_lineTo(x + 24, y + 3);    // Lower indent
        canvas_lineTo(x + 21, y + 6);    // Lower side
        break;
    case 1: // North - arrow points up
        canvas_moveTo(x, y - 50);        // Arrow tip (even higher)
        canvas_lineTo(x - 6, y - 41);    // Left side
        canvas_lineTo(x - 3, y - 44);    // Left indent
        canvas_lineTo(x - 3, y - 37);    // Left base
        canvas_lineTo(x + 3, y - 37);    // Right base
        canvas_lineTo(x + 3, y - 44);    // Right indent
        canvas_lineTo(x + 6, y - 41);    // Right side
        break;
    case 2: // West - arrow points left
        canvas_moveTo(x - 30, y);        // Arrow tip (even further away)
        canvas_lineTo(x - 21, y - 6);    // Upper side
        canvas_lineTo(x - 24, y - 3);    // Upper indent
        canvas_lineTo(x - 17, y - 3);    // Upper base
        canvas_lineTo(x - 17, y + 3);    // Lower base
        canvas_lineTo(x - 24, y + 3);    // Lower indent
        canvas_lineTo(x - 21, y + 6);    // Lower side
        break;
    case 3: // South - arrow points down
        canvas_moveTo(x, y + 30);        // Arrow tip (even lower)
        canvas_lineTo(x - 6, y + 21);    // Left side
        canvas_lineTo(x - 3, y + 24);    // Left indent
        canvas_lineTo(x - 3, y + 17);    // Left base
        canvas_lineTo(x + 3, y + 17);    // Right base
        canvas_lineTo(x + 3, y + 24);    // Right indent
        canvas_lineTo(x + 6, y + 21);    // Right side
        break;
    }
    canvas_closePath();
    canvas_fill(FILL_RULE_NONZERO);
}

// static inline void drawKarel()
// {
//     double x = OFFSET_X + (karel.x - 1) * CELL_SIZE + CELL_SIZE / 2;
//     double y = OFFSET_Y + (WORLD_HEIGHT - karel.y) * CELL_SIZE + CELL_SIZE / 2;

//     // Draw Karel's body (rectangle)
//     canvas_setFillStyleZ("gray");
//     canvas_fillRect(x - 15, y - 10, 30, 20);

//     // Draw Karel's "face" (triangle indicating direction)
//     canvas_setFillStyleZ("red");
//     canvas_beginPath();

//     // Calculate triangle points based on direction
//     double dx1, dy1, dx2, dy2, dx3, dy3;
//     switch (karel.direction)
//     {
//     case 0: // East
//         dx1 = 15;
//         dy1 = 0;
//         dx2 = 25;
//         dy2 = -8;
//         dx3 = 25;
//         dy3 = 8;
//         break;
//     case 1: // North
//         dx1 = 0;
//         dy1 = -15;
//         dx2 = -8;
//         dy2 = -25;
//         dx3 = 8;
//         dy3 = -25;
//         break;
//     case 2: // West
//         dx1 = -15;
//         dy1 = 0;
//         dx2 = -25;
//         dy2 = -8;
//         dx3 = -25;
//         dy3 = 8;
//         break;
//     case 3: // South
//         dx1 = 0;
//         dy1 = 15;
//         dx2 = -8;
//         dy2 = 25;
//         dx3 = 8;
//         dy3 = 25;
//         break;
//     }

//     canvas_moveTo(x + dx1, y + dy1);
//     canvas_lineTo(x + dx2, y + dy2);
//     canvas_lineTo(x + dx3, y + dy3);
//     canvas_closePath();
//     canvas_fill(FILL_RULE_NONZERO);
// }

static inline void drawInfo()
{
    // Information about Karel
    canvas_setFillStyleZ("black");
    canvas_setFontZ("16px Arial");
    canvas_setTextAlign(TEXT_ALIGN_LEFT);
    canvas_setTextBaseline(TEXT_BASELINE_TOP);

    char info[100];
    snprintf(info, sizeof(info), "Karel - Position: (%d,%d)", karel.x, karel.y);
    canvas_fillText(info, strlen(info), 50, 10);

    snprintf(info, sizeof(info), "Direction: %s", DIRECTION_NAMES[karel.direction]);
    canvas_fillText(info, strlen(info), 50, 30);

    snprintf(info, sizeof(info), "Beeper in the bag: %d", karel.bag_beepers);
    canvas_fillText(info, strlen(info), 300, 10);
}

static inline bool drawWorld()
{
    // karel_process_next_action();
    karel_process_action_log();
    // karel_log_buffer_flush_one();
    canvas_setFillStyleZ("white");
    canvas_fillRect(0, 0, 800, 600);
    drawWalls();
    drawGrid();
    drawBeepers();
    drawKarel();
    drawInfo();
    return karel_unified_buffer.count == 0;

}

// static inline void drawWorldRect(f64 x, f64 y, f64 w, f64 h)
// {
//     canvas_setFillStyleZ("white");
//     canvas_fillRect(0, 0, 800, 600);
//     drawWalls();
//     drawGrid();
//     drawBeepers();
//     drawKarel();
//     drawInfo();

// }


static inline void karel_turn_left()
{
    // karel.direction = (karel.direction + 1) % 4;
    karel_buffer_enqueue_action(KAREL_ACTION_TURN_LEFT);
}

static inline void karel_pick_beeper()
{
    karel_buffer_enqueue_action(KAREL_ACTION_PICK_BEEPER);
    // if (karel.beepers[karel.x][karel.y])
    // {
    //     karel.beepers[karel.x][karel.y] = false;
    //     karel.bag_beepers++;
    // }
}

static inline void karel_put_beeper()
{
    karel_buffer_enqueue_action(KAREL_ACTION_PUT_BEEPER);
    // if (karel.bag_beepers > 0)
    // {
    //     karel.beepers[karel.x][karel.y] = true;
    //     karel.bag_beepers--;
    // }
}


static inline void karel_move()
{
    karel_buffer_enqueue_action(KAREL_ACTION_MOVE);
}



/* CONDITIONS */

static inline bool karel_simulated_front_is_clear(KarelSimulatedState* state) {
    int new_x = state->x;
    int new_y = state->y;

    switch (state->direction) {
    case 0: // East
        new_x++;
        if (karel.vertical_walls[state->x + 1][state->y]) return false;
        break;
    case 1: // North
        new_y++;
        if (karel.horizontal_walls[state->x][state->y + 1]) return false;
        break;
    case 2: // West
        new_x--;
        if (karel.vertical_walls[state->x][state->y]) return false;
        break;
    case 3: // South
        new_y--;
        if (karel.horizontal_walls[state->x][state->y]) return false;
        break;
    }

    return (new_x >= 1 && new_x <= WORLD_WIDTH && new_y >= 1 && new_y <= WORLD_HEIGHT);
}


static inline KarelSimulatedState karel_simulate_state() {
    KarelSimulatedState simulated = {
        .x = karel.x,
        .y = karel.y,
        .direction = karel.direction,
        .bag_beepers = karel.bag_beepers
    };
    
    // Copy beeper state
    for (int i = 0; i <= WORLD_WIDTH; i++) {
        for (int j = 0; j <= WORLD_HEIGHT; j++) {
            simulated.beepers[i][j] = karel.beepers[i][j];
        }
    }
    
    // Simulate all actions in the buffer
    int temp_front = karel_unified_buffer.front;
    int temp_count = karel_unified_buffer.count;
    
    for (int i = 0; i < temp_count; i++) {
        int action_index = (temp_front + i) % KAREL_UNIFIED_BUFFER_SIZE;
        KarelUnifiedBufferEntry entry = karel_unified_buffer.entries[action_index];
        
        if (entry.type == KAREL_BUFFER_ACTION) 
        {
            switch ((KarelActionType) entry.action.type) {
                case KAREL_ACTION_MOVE:
                    // Check if it can move (using simulated state)
                    if (karel_simulated_front_is_clear(&simulated)) {
                        switch (simulated.direction) {
                        case 0: simulated.x++; break; // East
                        case 1: simulated.y++; break; // North
                        case 2: simulated.x--; break; // West
                        case 3: simulated.y--; break; // South
                        }
                    }
                    break;
                    
                case KAREL_ACTION_TURN_LEFT:
                    simulated.direction = (simulated.direction + 1) % 4;
                    break;
                    
                case KAREL_ACTION_PICK_BEEPER:
                    if (simulated.beepers[simulated.x][simulated.y]) {
                        simulated.beepers[simulated.x][simulated.y] = false;
                        simulated.bag_beepers++;
                    }
                    break;
                    
                case KAREL_ACTION_PUT_BEEPER:
                    if (simulated.bag_beepers > 0) {
                        simulated.beepers[simulated.x][simulated.y] = true;
                        simulated.bag_beepers--;
                    }
                    break;
            }
        }
    }
    
    return simulated;
}



static inline bool beepers_present() {
    KarelSimulatedState simulated = karel_simulate_state();
    return simulated.beepers[simulated.x][simulated.y];
}

static inline bool front_is_clear() {
    KarelSimulatedState simulated = karel_simulate_state();
    return karel_simulated_front_is_clear(&simulated);
}

static inline bool beepers_in_bag() {
    KarelSimulatedState simulated = karel_simulate_state();
    return simulated.bag_beepers > 0;
}

static inline bool facing_north() { 
    KarelSimulatedState simulated = karel_simulate_state();
    return simulated.direction == 1; 
}

static inline bool facing_south() { 
    KarelSimulatedState simulated = karel_simulate_state();
    return simulated.direction == 3; 
}

static inline bool facing_east() { 
    KarelSimulatedState simulated = karel_simulate_state();
    return simulated.direction == 0; 
}

static inline bool facing_west() { 
    KarelSimulatedState simulated = karel_simulate_state();
    return simulated.direction == 2; 
}

// Implementation of simulated accessor functions
static inline int karel_get_simulated_x(void) {
    KarelSimulatedState simulated = karel_simulate_state();
    return simulated.x;
}

static inline int karel_get_simulated_y(void) {
    KarelSimulatedState simulated = karel_simulate_state();
    return simulated.y;
}

static inline int karel_get_simulated_direction(void) {
    KarelSimulatedState simulated = karel_simulate_state();
    return simulated.direction;
}

static inline int karel_get_simulated_bag_beepers(void) {
    KarelSimulatedState simulated = karel_simulate_state();
    return simulated.bag_beepers;
}
#pragma GCC diagnostic pop

#endif // KAREL_H_