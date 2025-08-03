#ifndef KAREL_H_
#define KAREL_H_

#include <canvas_main.h>
#include <math.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Configurazione del mondo di Karel
#define WORLD_WIDTH 10
#define WORLD_HEIGHT 8
#define CELL_SIZE 60
#define OFFSET_X 50
#define OFFSET_Y 50

// Stato di Karel
struct Karel
{
    int x, y;                                        // Posizione (1-based come nel mondo di Karel)
    int direction;                                   // 0=Est, 1=Nord, 2=Ovest, 3=Sud
    bool beepers[WORLD_WIDTH + 1][WORLD_HEIGHT + 1]; // Beeper nel mondo
    int bag_beepers;                                 // Beeper nella borsa di Karel
};

// Variabile globale Karel
static Karel karel;  // ← DEFINIZIONE NELL'HEADER

// Direzioni
extern const char *DIRECTION_NAMES[];

// Implementazioni inline

static inline void karel_init()
{
    canvas_setWidth(800);
    canvas_setHeight(600);

    // Inizializza Karel
    karel.x = 1;
    karel.y = 1;
    karel.direction = 0; // Guarda Est
    karel.bag_beepers = 10;

    // Inizializza il mondo senza beeper
    for (int i = 0; i <= WORLD_WIDTH; i++)
    {
        for (int j = 0; j <= WORLD_HEIGHT; j++)
        {
            karel.beepers[i][j] = false;
        }
    }
}

static inline void karel_add_beeper(int x, int y)
{
    if (x >= 1 && x <= WORLD_WIDTH && y >= 1 && y <= WORLD_HEIGHT)
    {
        karel.beepers[x][y] = true;
    }
}

static inline void drawGrid()
{
    canvas_setStrokeStyleZ("lightgray");
    canvas_setLineWidth(1);

    // Linee verticali
    for (int i = 0; i <= WORLD_WIDTH; i++)
    {
        double x = OFFSET_X + i * CELL_SIZE;
        canvas_beginPath();
        canvas_moveTo(x, OFFSET_Y);
        canvas_lineTo(x, OFFSET_Y + WORLD_HEIGHT * CELL_SIZE);
        canvas_stroke();
    }

    // Linee orizzontali
    for (int j = 0; j <= WORLD_HEIGHT; j++)
    {
        double y = OFFSET_Y + j * CELL_SIZE;
        canvas_beginPath();
        canvas_moveTo(OFFSET_X, y);
        canvas_lineTo(OFFSET_X + WORLD_WIDTH * CELL_SIZE, y);
        canvas_stroke();
    }

    // Bordo esterno più spesso
    canvas_setStrokeStyleZ("black");
    canvas_setLineWidth(3);
    canvas_strokeRect(OFFSET_X, OFFSET_Y, WORLD_WIDTH * CELL_SIZE, WORLD_HEIGHT * CELL_SIZE);
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

                // Disegna un diamante (beeper)
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

    // Disegna il corpo di Karel (rettangolo)
    canvas_setFillStyleZ("gray");
    canvas_fillRect(x - 15, y - 10, 30, 20);

    // Disegna la "faccia" di Karel (triangolo che indica la direzione)
    canvas_setFillStyleZ("red");
    canvas_beginPath();

    // Calcola i punti del triangolo in base alla direzione
    double dx1, dy1, dx2, dy2, dx3, dy3;
    switch (karel.direction)
    {
    case 0: // Est
        dx1 = 15;
        dy1 = 0;
        dx2 = 25;
        dy2 = -8;
        dx3 = 25;
        dy3 = 8;
        break;
    case 1: // Nord
        dx1 = 0;
        dy1 = -15;
        dx2 = -8;
        dy2 = -25;
        dx3 = 8;
        dy3 = -25;
        break;
    case 2: // Ovest
        dx1 = -15;
        dy1 = 0;
        dx2 = -25;
        dy2 = -8;
        dx3 = -25;
        dy3 = 8;
        break;
    case 3: // Sud
        dx1 = 0;
        dy1 = 15;
        dx2 = -8;
        dy2 = 25;
        dx3 = 8;
        dy3 = 25;
        break;
    }

    canvas_moveTo(x + dx1, y + dy1);
    canvas_lineTo(x + dx2, y + dy2);
    canvas_lineTo(x + dx3, y + dy3);
    canvas_closePath();
    canvas_fill(FILL_RULE_NONZERO);
}

static inline void drawInfo()
{
    // Informazioni su Karel
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

// Funzioni di movimento di Karel
static inline void karel_move()
{
    int new_x = karel.x;
    int new_y = karel.y;

    switch (karel.direction)
    {
    case 0:
        new_x++;
        break; // Est
    case 1:
        new_y++;
        break; // Nord
    case 2:
        new_x--;
        break; // Ovest
    case 3:
        new_y--;
        break; // Sud
    }

    // Controlla i limiti del mondo
    if (new_x >= 1 && new_x <= WORLD_WIDTH && new_y >= 1 && new_y <= WORLD_HEIGHT)
    {
        karel.x = new_x;
        karel.y = new_y;
    }
}

static inline void karel_turn_left()
{
    karel.direction = (karel.direction + 1) % 4;
}

static inline void karel_pick_beeper()
{
    if (karel.beepers[karel.x][karel.y])
    {
        karel.beepers[karel.x][karel.y] = false;
        karel.bag_beepers++;
    }
}

static inline void karel_put_beeper()
{
    if (karel.bag_beepers > 0)
    {
        karel.beepers[karel.x][karel.y] = true;
        karel.bag_beepers--;
    }
}

// Funzioni di controllo
static inline bool front_is_clear()
{
    int new_x = karel.x;
    int new_y = karel.y;

    switch (karel.direction)
    {
    case 0:
        new_x++;
        break; // Est
    case 1:
        new_y++;
        break; // Nord
    case 2:
        new_x--;
        break; // Ovest
    case 3:
        new_y--;
        break; // Sud
    }

    return (new_x >= 1 && new_x <= WORLD_WIDTH && new_y >= 1 && new_y <= WORLD_HEIGHT);
}

static inline bool beepers_present()
{
    return karel.beepers[karel.x][karel.y];
}



static inline bool facing_north() { return karel.direction == 1; }
static inline bool facing_south() { return karel.direction == 3; }
static inline bool facing_east() { return karel.direction == 0; }
static inline bool facing_west() { return karel.direction == 2; }
#endif // KAREL_H_