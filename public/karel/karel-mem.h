#ifndef KAREL_H_
#define KAREL_H_

#include <canvas_main.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

// Configurazione del mondo di Karel
#define WORLD_WIDTH 10
#define WORLD_HEIGHT 8
#define CELL_SIZE 60
#define OFFSET_X 50
#define OFFSET_Y 50
#define KAREL_STATE_FILE "/karel_state.dat"


// Direzioni
extern const char *DIRECTION_NAMES[];

// Struttura per salvare lo stato di Karel
typedef struct {
    int x, y;
    int direction;
    int bag_beepers;
    bool beepers[WORLD_WIDTH + 1][WORLD_HEIGHT + 1];
} KarelState;

// Funzioni per gestire lo stato di Karel tramite memfs
static inline KarelState karel_load_state() {
    KarelState state = {0};
    
    // Prova a leggere lo stato dal file
    FILE* file = fopen(KAREL_STATE_FILE, "rb");
    if (file) {
        fread(&state, sizeof(KarelState), 1, file);
        fclose(file);
        printf("Karel state loaded from memfs\n");
        printf(" bag beeper: %d\n", state.bag_beepers);
    } else {
        // Stato iniziale se il file non esiste
        state.x = 1;
        state.y = 1;
        state.direction = 0;
        state.bag_beepers = 10;
        for (int i = 0; i <= WORLD_WIDTH; i++) {
            for (int j = 0; j <= WORLD_HEIGHT; j++) {
                state.beepers[i][j] = false;
            }
        }
        printf("Karel state initialized (file not found)\n");
    }
    return state;
}

static inline void karel_save_state(const KarelState* state) {
    FILE* file = fopen(KAREL_STATE_FILE, "wb");
    if (file) {
        fwrite(state, sizeof(KarelState), 1, file);
        fclose(file);
        printf("Karel state saved to memfs\n");
    } else {
        printf("Failed to save Karel state\n");
    }
}

// Variabile globale per lo stato corrente
static KarelState g_karel_state;

static inline void karel_init() {
    canvas_setWidth(800);
    canvas_setHeight(600);
    printf("KAREL INIT\n");
    
    // Carica lo stato da memfs
    g_karel_state = karel_load_state();
}

static inline void karel_add_beeper(int x, int y) {
    g_karel_state = karel_load_state();
    if (x >= 1 && x <= WORLD_WIDTH && y >= 1 && y <= WORLD_HEIGHT) {
        g_karel_state.beepers[x][y] = true;
    }
    karel_save_state(&g_karel_state);
}

static inline void karel_move() {
    g_karel_state = karel_load_state();
    int new_x = g_karel_state.x;
    int new_y = g_karel_state.y;

    switch (g_karel_state.direction) {
        case 0: new_x++; break; // Est
        case 1: new_y++; break; // Nord
        case 2: new_x--; break; // Ovest
        case 3: new_y--; break; // Sud
    }

    if (new_x >= 1 && new_x <= WORLD_WIDTH && new_y >= 1 && new_y <= WORLD_HEIGHT) {
        g_karel_state.x = new_x;
        g_karel_state.y = new_y;
    }
    karel_save_state(&g_karel_state);
}

static inline void karel_turn_left() {
    g_karel_state = karel_load_state();
    g_karel_state.direction = (g_karel_state.direction + 1) % 4;
    karel_save_state(&g_karel_state);
}

static inline void karel_pick_beeper() {
    g_karel_state = karel_load_state();
    if (g_karel_state.beepers[g_karel_state.x][g_karel_state.y]) {
        g_karel_state.beepers[g_karel_state.x][g_karel_state.y] = false;
        g_karel_state.bag_beepers++;
    }
    karel_save_state(&g_karel_state);
}

static inline void karel_put_beeper() {
    g_karel_state = karel_load_state();
    if (g_karel_state.bag_beepers > 0) {
        g_karel_state.beepers[g_karel_state.x][g_karel_state.y] = true;
        g_karel_state.bag_beepers--;
    }
    karel_save_state(&g_karel_state);
}

// Funzioni di controllo
static inline bool front_is_clear() {
    g_karel_state = karel_load_state();
    int new_x = g_karel_state.x;
    int new_y = g_karel_state.y;

    switch (g_karel_state.direction) {
        case 0: new_x++; break; // Est
        case 1: new_y++; break; // Nord
        case 2: new_x--; break; // Ovest
        case 3: new_y--; break; // Sud
    }

    return (new_x >= 1 && new_x <= WORLD_WIDTH && new_y >= 1 && new_y <= WORLD_HEIGHT);
}

static inline bool beepers_present() {
    g_karel_state = karel_load_state();
    return g_karel_state.beepers[g_karel_state.x][g_karel_state.y];
}

// Funzioni di disegno
static inline void karel_refresh_state() {
    g_karel_state = karel_load_state();
}

static inline void drawGrid() {
    canvas_setStrokeStyleZ("lightgray");
    canvas_setLineWidth(1);

    for (int i = 0; i <= WORLD_WIDTH; i++) {
        double x = OFFSET_X + i * CELL_SIZE;
        canvas_beginPath();
        canvas_moveTo(x, OFFSET_Y);
        canvas_lineTo(x, OFFSET_Y + WORLD_HEIGHT * CELL_SIZE);
        canvas_stroke();
    }

    for (int j = 0; j <= WORLD_HEIGHT; j++) {
        double y = OFFSET_Y + j * CELL_SIZE;
        canvas_beginPath();
        canvas_moveTo(OFFSET_X, y);
        canvas_lineTo(OFFSET_X + WORLD_WIDTH * CELL_SIZE, y);
        canvas_stroke();
    }

    canvas_setStrokeStyleZ("black");
    canvas_setLineWidth(3);
    canvas_strokeRect(OFFSET_X, OFFSET_Y, WORLD_WIDTH * CELL_SIZE, WORLD_HEIGHT * CELL_SIZE);
}

static inline void drawBeepers() {
    canvas_setFillStyleZ("blue");

    for (int i = 1; i <= WORLD_WIDTH; i++) {
        for (int j = 1; j <= WORLD_HEIGHT; j++) {
            if (g_karel_state.beepers[i][j]) {
                double x = OFFSET_X + (i - 1) * CELL_SIZE + CELL_SIZE / 2;
                double y = OFFSET_Y + (WORLD_HEIGHT - j) * CELL_SIZE + CELL_SIZE / 2;

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

static inline void drawKarel() {
    double x = OFFSET_X + (g_karel_state.x - 1) * CELL_SIZE + CELL_SIZE / 2;
    double y = OFFSET_Y + (WORLD_HEIGHT - g_karel_state.y) * CELL_SIZE + CELL_SIZE / 2;

    canvas_setFillStyleZ("gray");
    canvas_fillRect(x - 15, y - 10, 30, 20);

    canvas_setFillStyleZ("red");
    canvas_beginPath();

    double dx1, dy1, dx2, dy2, dx3, dy3;
    switch (g_karel_state.direction) {
        case 0: dx1=15; dy1=0; dx2=25; dy2=-8; dx3=25; dy3=8; break;  // Est
        case 1: dx1=0; dy1=-15; dx2=-8; dy2=-25; dx3=8; dy3=-25; break; // Nord
        case 2: dx1=-15; dy1=0; dx2=-25; dy2=-8; dx3=-25; dy3=8; break; // Ovest
        case 3: dx1=0; dy1=15; dx2=-8; dy2=25; dx3=8; dy3=25; break;   // Sud
    }

    canvas_moveTo(x + dx1, y + dy1);
    canvas_lineTo(x + dx2, y + dy2);
    canvas_lineTo(x + dx3, y + dy3);
    canvas_closePath();
    canvas_fill(FILL_RULE_NONZERO);
}

static inline void drawInfo() {
    canvas_setFillStyleZ("black");
    canvas_setFontZ("16px Arial");
    canvas_setTextAlign(TEXT_ALIGN_LEFT);
    canvas_setTextBaseline(TEXT_BASELINE_TOP);

    char info[100];
    snprintf(info, sizeof(info), "Karel - Position: (%d,%d)", g_karel_state.x, g_karel_state.y);
    canvas_fillText(info, strlen(info), 50, 10);

    snprintf(info, sizeof(info), "Direction: %d", g_karel_state.direction);
    canvas_fillText(info, strlen(info), 50, 30);

    snprintf(info, sizeof(info), "Beeper in the bag: %d", g_karel_state.bag_beepers);
    canvas_fillText(info, strlen(info), 300, 10);
}

static inline void karel_print() {
    g_karel_state = karel_load_state();
    printf("Karel position: (%d, %d)\n", g_karel_state.x, g_karel_state.y);
    printf("Direction: %d\n", g_karel_state.direction);
    printf("Beepers in bag: %d\n", g_karel_state.bag_beepers);
}

// Funzione per resettare lo stato (per debug)
static inline void karel_reset() {
    g_karel_state = karel_load_state();
    g_karel_state.x = 1;
    g_karel_state.y = 1;
    g_karel_state.direction = 0;
    g_karel_state.bag_beepers = 10;
    for (int i = 0; i <= WORLD_WIDTH; i++) {
        for (int j = 0; j <= WORLD_HEIGHT; j++) {
            g_karel_state.beepers[i][j] = false;
        }
    }
    karel_save_state(&g_karel_state);
    printf("Karel state reset\n");
}

static inline bool facing_north() { 
    g_karel_state = karel_load_state(); 
    return g_karel_state.direction == 1; 
}
static inline bool facing_south() { 
    g_karel_state = karel_load_state(); 
    return g_karel_state.direction == 3; 
}
static inline bool facing_east() { 
    g_karel_state = karel_load_state(); 
    return g_karel_state.direction == 0; 
}
static inline bool facing_west() { 
    g_karel_state = karel_load_state(); 
    return g_karel_state.direction == 2; 
}

#endif // KAREL_H_