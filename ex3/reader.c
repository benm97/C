/**
 * @file reader.c
 * @author  benm
 * @date 28 Aug 2018
 * @section DESCRIPTION
 * The system parse a given file and compute the heat equation.
 */

// ------------------------------ includes ------------------------------
#include <stdio.h>
#include <stdlib.h>
#include "calculator.h"
#include "heat_eqn.h"
// -------------------------- const definitions -------------------------
#define ERROR_MSG "error"
#define CORRECT_USAGE "correct usage is <filename>"
#define SEPARATOR "----\n"
#define NON_SOURCES_LINES 6
// ------------------------------ functions -----------------------------

/**
 * free all allocated memory
 * @param grid grid to free
 * @param n height of the grid
 * @param sourcesList list pf sources
 */
void freeAll(double **grid, int n, source_point *sourcesList)
{
    free(sourcesList);
    for (int j = 0; j < n; j++)
    {
        free(grid[j]);
    }
    free(grid);
}

/**
 * Get number of line in the file
 * @param file file
 * @return number of line
 */
int getLinesNumber(FILE *file)
{
    int linesNumber = 0;
    for (char c = (char) getc(file); c != EOF; c = (char) getc(file))
    {
        if (c == '\n')
        {
            linesNumber++;
        }
    }
    rewind(file);
    return linesNumber + 1;
}

/**
 * Get the sources list from the file (suppose we already read the first section)
 * @param sourcesNumber number of sources in the file
 * @param file file
 * @return a list of sources objects
 */
source_point *getSourcesList(int sourcesNumber, FILE *file)
{
    source_point *sourcesList = (source_point *) malloc(sizeof(source_point) * sourcesNumber);
    if (sourcesList == NULL)
    {
        fprintf(stderr, ERROR_MSG);
        fclose(file);
        exit(1);
    }
    for (int i = 0; i < sourcesNumber; i++)
    {
        int x, y;
        double value;
        fscanf(file, "%d, %d, %lf\n", &x, &y, &value);
        sourcesList[i].x = x;
        sourcesList[i].y = y;
        sourcesList[i].value = value;
    }
    return sourcesList;
}

/**
 * get the grid from the parsed info
 * @param n height of the grid
 * @param m width of the grid
 * @param sourcesNumber number of sources
 * @param sourcesList sources
 * @return the grid
 */
double **getGrid(int n, int m, int sourcesNumber, source_point *sourcesList)
{
    double **grid = (double **) malloc(sizeof(double *) * n);
    if (grid == NULL)
    {
        fprintf(stderr, ERROR_MSG);
        free(sourcesList);
        exit(1);
    }
    for (int i = 0; i < n; i++)
    {
        grid[i] = (double *) calloc((size_t) m, sizeof(double));
        if (grid[i] == NULL)
        {
            fprintf(stderr, ERROR_MSG);
            freeAll(grid, i, sourcesList); // Free grid until i
            exit(1);
        }
    }
    for (int j = 0; j < sourcesNumber; j++)
    {
        if (sourcesList[j].x >= n || sourcesList[j].y >= m)
        {
            fprintf(stderr, ERROR_MSG);
            freeAll(grid, n, sourcesList);
            exit(1);
        }
        grid[sourcesList[j].x][sourcesList[j].y] = sourcesList[j].value;
    }
    return grid;
}

/**
 * printing the given grid
 * @param grid grid
 * @param n height
 * @param m width
 */
void printGrid(double **grid, int n, int m)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            printf("%.4f,", grid[i][j]);

        }
        printf("\n");
    }
}

/**
 * main function
 * @param argc number of args
 * @param argv args array
 * @return 0 if ok
 */
int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        fprintf(stderr, CORRECT_USAGE);
        exit(1);
    }
    FILE *file = fopen(argv[1], "r");
    if (file == NULL)
    {
        fprintf(stderr, ERROR_MSG);
        exit(1);
    }
    int sourcesNumber = getLinesNumber(file) - NON_SOURCES_LINES;
    int m = 0, n = 0;
    fscanf(file, "%d, %d\n", &n, &m);
    fscanf(file, SEPARATOR);
    source_point *sourcesList = getSourcesList(sourcesNumber, file);
    fscanf(file, SEPARATOR);
    int n_iter, isCyclic;
    double terminate;
    fscanf(file, "%lf\n", &terminate);
    fscanf(file, "%d\n", &n_iter);
    fscanf(file, "%d\n", &isCyclic);
    fclose(file);
    double **grid = getGrid(n, m, sourcesNumber, sourcesList);
    double diff;
    do
    {
        diff = calculate(heat_eqn, grid, (size_t) n, (size_t) m, sourcesList,
                         (size_t) sourcesNumber, terminate, (unsigned int) n_iter, isCyclic);
        printf("%lf\n", diff);
        printGrid(grid, n, m);
    } while (diff >= terminate);
    freeAll(grid, n, sourcesList);
    return 0;
}


