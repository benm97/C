/**
 * @file battleships.h
 * @author  benm
 * @date 22 aug 2018
 * @brief The battleship game logic header file
 * @section DESCRIPTION
 * Header file of battleships.c
 */

// -------------------------- const definitions -------------------------
#define BOATS_NUMBER 5
#define SUNK 2
#define HIT 1
#define MISS 0
#ifndef EX2_BATTLESHIPS_H
#define EX2_BATTLESHIPS_H

// ------------------------------ functions -----------------------------

typedef struct Boat
{
    int size;
    int **coord;
    int count;
} Boat;

/**
 * initialize the game
 * @param size size of the board
 */
void init(int size);

/**
 * Perform a shot
 * @param x x position
 * @param y y position
 * @return 0 iff miss 1 iff hit 2 iff sunk
 */
int shot(int x, int y);

/**
 * A function to free the boats array and what is included
 */
void freeBoats();

#endif //EX2_BATTLESHIPS_H

