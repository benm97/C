/**
 * @file battleships.c
 * @author  benm
 * @date 22 aug 2018
 * @brief The battleship game logic
 * @section DESCRIPTION
 * The system implements function for a battleship game (description in the header file)
 */

// ------------------------------ includes ------------------------------
#include <stdlib.h>
#include "battleships.h"

// -------------------------- const definitions -------------------------

#define NULL_COORD (-1)
/**
 * True/False symbols
 */
#define TRUE 1
#define FALSE 0
/**
 * Boats sizes
 */
#define BOAT1_SIZE 5
#define BOAT2_SIZE 4
#define BOAT3_SIZE 3
#define BOAT4_SIZE 3
#define BOAT5_SIZE 2

// ------------------------------ functions -----------------------------

Boat *myBoats; //Global array for the boats
int boardSize;

/**
 * A function to free coord array of a boat
 * @param boat the boat we want to free coord's
 */
void freeCoord(Boat *boat)
{
    for (int i = 0; i < boat->size; i++)
    {
        free(boat->coord[i]);
    }
    free(boat->coord);
}

/**
 * A function to free the boats array and what is included
 */
void freeBoats()
{
    for (int boatIndex = 0; boatIndex < BOATS_NUMBER; boatIndex++)
    {
        freeCoord(myBoats + boatIndex);
    }
    free(myBoats);
}

/**
 * A function that's tell if a position is free or if thee is a ship
 * @param x x position
 * @param y y position
 * @return 1 iff free, 0 else
 */
int isAvailable(int x, int y)
{
    if (x >= boardSize || y >= boardSize)
    {
        return 0;
    }
    for (int boatIndex = 0; boatIndex < BOATS_NUMBER; boatIndex++)
    {
        for (int i = 0; i < myBoats[boatIndex].size; i++)
        {
            if (myBoats[boatIndex].coord[i][0] == x && myBoats[boatIndex].coord[i][1] == y)
            {
                return 0;
            }
        }
    }
    return 1;
}

/**
 * Init a boat
 * @param boat boat to init
 * @param boatSize size of the boat
 */
void initBoat(Boat *boat, int boatSize)
{
    boat->size = boatSize;
    boat->coord = (int **) malloc(sizeof(int *) * boatSize);
    if (boat->coord == NULL)
    {
        freeBoats();
        exit(1);
    }
    for (int i = 0; i < boatSize; i++)
    {
        boat->coord[i] = (int *) malloc(sizeof(int) * 2);
        if (boat->coord[i] == NULL)
        {
            freeBoats();
            exit(1);
        }
        boat->coord[i][0] = NULL_COORD;
        boat->coord[i][1] = NULL_COORD;
    }
}

/**
 * Put a boat at random position
 * @param boat boat to place
 */
void putBoat(Boat *boat)
{
    // Choose a random position until that's work
    int flag = TRUE;
    while (flag)
    {
        flag = FALSE;
        int orientation = rand() % 2;
        int x = rand() % (boardSize);
        int y = rand() % (boardSize);
        if (orientation == 0)
        {
            for (int i = 0; i < boat->size; i++)
            {
                if (isAvailable(x + i, y) == 0)
                {
                    flag = TRUE;
                    freeCoord(boat);
                    initBoat(boat, boat->size);
                    break;
                }
                boat->coord[i][0] = x + i;
                boat->coord[i][1] = y;
            }
        }
        else if (orientation == 1)
        {
            for (int i = 0; i < boat->size; i++)
            {
                if (isAvailable(x, y + i) == 0)
                {
                    flag = TRUE;
                    freeCoord(boat);
                    initBoat(boat, boat->size);
                    break;
                }
                boat->coord[i][0] = x;
                boat->coord[i][1] = y + i;
            }
        }

    }
}

/**
 * initialize the game
 * @param size size of the board
 */
void init(int size)
{
    // Creating the boats
    boardSize = size;
    myBoats = (Boat *) malloc(BOATS_NUMBER * sizeof(Boat));
    if (myBoats == NULL)
    {
        free(myBoats);
    }
    initBoat(myBoats, BOAT1_SIZE);
    initBoat(myBoats + 1, BOAT2_SIZE);
    initBoat(myBoats + 2, BOAT3_SIZE);
    initBoat(myBoats + 3, BOAT4_SIZE);
    initBoat(myBoats + 4, BOAT5_SIZE);
    for (int i = 0; i < BOATS_NUMBER; i++)
    {
        putBoat(myBoats + i);
    }

}

/**
 * Perform a shot
 * @param x x position
 * @param y y position
 * @return 0 iff miss 1 iff hit 2 iff sunk
 */
int shot(int x, int y)
{
    for (int boatIndex = 0; boatIndex < BOATS_NUMBER; boatIndex++)
    {
        for (int i = 0; i < myBoats[boatIndex].size; i++)
        {
            if (myBoats[boatIndex].coord[i][0] == x && myBoats[boatIndex].coord[i][1] == y)
            {
                (myBoats + boatIndex)->count++;
                if (myBoats[boatIndex].count == myBoats[boatIndex].size)
                {
                    return SUNK;
                }
                else
                {
                    return HIT;
                }
            }
        }
    }
    return MISS;
}
