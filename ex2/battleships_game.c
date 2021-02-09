/**
 * @file battleships_game.c
 * @author  benm
 * @date 22 aug 2018
 * @brief The user interface battleship game
 * @section DESCRIPTION
 * The system use the functions of battleships.c to offer to the user a battleship game
 */

// ------------------------------ includes ------------------------------
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "battleships.h"

// -------------------------- const definitions -------------------------
/**
 * Messages to the user
 */
#define INPUT_MSG "enter board size:"
#define INVALID_SIZE "not valid board size"
#define INVALID_MSG "Invalid move, try again.\n"
#define READY_MSG "Ready to play"
#define ALREADY_MSG "Already been Hit."
#define MISS_MSG "Miss."
#define HIT_MSG "Hit."
#define SUNK_MSG "Hit and sunk."
#define END_MSG "Game over"
#define INPUT_COORD_MSG "\nenter coordinates:"
/**
 * Symbols
 */
#define HIT_SYMBOL 'X'
#define MISS_SYMBOL 'o'
#define HIDDEN_SYMBOL '_'
/**
 * exit command
 */
#define EXIT_STR "exit"
/**
 * other const
 */
#define EXIT_STR_SIZE 5
#define LETTERS_SHIFT 97
#define MAX_SIZE 25
#define MIN_SIZE 5

// ------------------------------ functions -----------------------------

/**
 * A function to print the game board
 * @param board the board to print
 * @param size size of the boars
 */
void printBoard(char **board, int size)
{
    for (int i = -1; i < size; i++)
    { // begin at -1 to print the digits line
        if (i == -1)
        {
            printf("\n ");
        }
        else
        {
            printf("\n%c", i + LETTERS_SHIFT); // print the letters column
        }
        for (int j = 0; j < size; j++)
        {
            if (i == -1)
            {
                printf(",%d", j + 1);
            }
            else
            {
                printf(" %c", board[i][j]);
            }
        }
    }
}

/**
 * Free the board and ships memory
 * @param board board to free
 * @param size size of the board
 */
void freeAll(char ***pBoard, int size)
{
    for (int i = 0; i < size; i++)
    {
        free((*pBoard)[i]);
    }
    free(*pBoard);
    freeBoats();
}

/**
 * create the board
 * @param size size of the board
 * @return the board
 */
char **createBoard(int size)
{
    char **board = (char **) malloc(size * sizeof(char *));
    if (board == NULL)
    {
        exit(1);
    }
    for (int i = 0; i < size; i++)
    {
        board[i] = (char *) malloc(size * sizeof(char));
        if (board[i] == NULL)
        {
            freeAll(&board, size);
            exit(1);
        }
        for (int j = 0; j < size; j++)
        {
            board[i][j] = HIDDEN_SYMBOL;
        }
    }
    return board;
}


/**
 * main function
 * @return
 */
int main()
{
    int size;
    int sunkCounter = 0;
    printf(INPUT_MSG);
    scanf("%d", &size);
    if (size < MIN_SIZE || size > MAX_SIZE)
    {
        fprintf(stderr, INVALID_SIZE);
        exit(1);
    }

    init(size);

    char **board = createBoard(size);

    printf(READY_MSG);

    printBoard(board, size);

    while (sunkCounter < BOATS_NUMBER) // Ask coordinates until all boats sunk
    {
        int col, row;
        char cRow;
        char input[EXIT_STR_SIZE];
        printf(INPUT_COORD_MSG);
        scanf(" %[^\t\n]", input);
        if (strcmp(input, EXIT_STR) == 0)
        {
            freeAll(&board, size);
            exit(1);
        }
        int match = sscanf(input, "%c%d", &cRow, &col);
        row = (int) (cRow) - LETTERS_SHIFT; // convert to a digit row
        col--;
        if (match != 2 || col > size - 1 || row > size - 1 || col < 0 || row < 0)
        {
            fprintf(stderr, INVALID_MSG);
        }
        else if (board[row][col] == HIT_SYMBOL)
        {
            printf(ALREADY_MSG);
            printBoard(board, size);
        }
        else
        {
            int isHit = shot(row, col);
            if (isHit == MISS)
            {
                printf(MISS_MSG);
                board[row][col] = MISS_SYMBOL;
                printBoard(board, size);
            }
            else if (isHit == HIT)
            {
                printf(HIT_MSG);
                board[row][col] = HIT_SYMBOL;
                printBoard(board, size);
            }
            else if (isHit == SUNK)
            {
                printf(SUNK_MSG);
                board[row][col] = HIT_SYMBOL;
                sunkCounter++;
                printBoard(board, size);
            }
        }

    }
    printf(END_MSG);
    freeAll(&board, size);
    return 0;

}
