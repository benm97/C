/**
 * @file calculator.c
 * @author  benm
 * @date 28 Aug 2018
 * @section DESCRIPTION
 * The system compute a function on a grid until stop conditions.
 */

// ------------------------------ includes ------------------------------
#include <stdio.h>
#include <math.h>
#include "calculator.h"
// -------------------------- const definitions -------------------------
#define TRUE 1
#define FALSE 0
// ------------------------------ macros -----------------------------
#define UNUSED(x) (void)(x)
// ------------------------------ functions -----------------------------
/**
 * Check if a point is a source
 * @param sources list of the sources
 * @param num_sources size of the list
 * @param x x
 * @param y y
 * @return 1 iff source
 */
int isSource(source_point *sources, size_t num_sources, int x, int y)
{
    for (int i = 0; i < (int)num_sources; i++)
    {
        if (sources[i].x == x && sources[i].y == y)
        {
            return TRUE;
        }
    }
    return FALSE;
}

/**
 * Get the right neighbor
 * @param grid the grid
 * @param m width of the grid
 * @param is_cyclic tell how to deal with borders
 * @param i i coord
 * @param j j coord
 * @return value of the neighbor
 */
double getRight(double **grid, size_t m, int is_cyclic, int i, int j)
{
    if (is_cyclic >= TRUE || j + 1 < (int)m)
    {
        return grid[i][(j + 1) % m];
    }
    else
    {
        return 0;
    }

}

/**
 * Get the left neighbor
 * @param grid the grid
 * @param m width of the grid
 * @param is_cyclic tell how to deal with borders
 * @param i i coord
 * @param j j coord
 * @return value of the neighbor
 */
double getLeft(double **grid, size_t m, int is_cyclic, int i, int j)
{

    if (is_cyclic >= TRUE || j - 1 >= 0)
    {
        return grid[i][(j - 1 + m) % m];
    }
    else
    {
        return 0;
    }

}

/**
 * Get the bottom neighbor
 * @param grid the grid
 * @param m width of the grid
 * @param is_cyclic tell how to deal with borders
 * @param i i coord
 * @param j j coord
 * @return value of the neighbor
 */
double getDown(double **grid, size_t n, int is_cyclic, int i, int j)
{
    if (is_cyclic >= TRUE || i + 1 < (int)n)
    {
        return grid[(i + 1) % n][j];
    }
    else
    {
        return 0;
    }

}

/**
 * Get the up neighbor
 * @param grid the grid
 * @param m width of the grid
 * @param is_cyclic tell how to deal with borders
 * @param i i coord
 * @param j j coord
 * @return value of the neighbor
 */
double getUp(double **grid, size_t n, int is_cyclic, int i, int j)
{

    if (is_cyclic >= TRUE || i - 1 >= 0)
    {
        return grid[(i - 1 + n) % n][j];
    }
    else
    {
        return 0;
    }

}

/**
 * One iteration of updating the grid, and calculate diff
 * @param function function to apply
 * @param grid the grid
 * @param n height of the grid
 * @param m width of the grid
 * @param sources sources list
 * @param num_sources size of the list
 * @param is_cyclic tell how to deal with borders
 * @return the difference after this iteration
 */
double
calculateIteration(diff_func function, double **grid, size_t n, size_t m, source_point *sources,
                   size_t num_sources,
                   int is_cyclic)
{

    double sum = 0;
    for (int i = 0; i < (int)n; i++)
    {
        for (int j = 0; j < (int)m; j++)
        {
            if (isSource(sources, num_sources, i, j) == FALSE)
            {
                grid[i][j] = function(grid[i][j], getRight(grid, m, is_cyclic, i, j),
                                      getUp(grid, n, is_cyclic, i, j),
                                      getLeft(grid, m, is_cyclic, i, j),
                                      getDown(grid, n, is_cyclic, i, j));
            }

            sum += grid[i][j];
        }
    }
    return sum;
}

/**
 * A diff function that's just return the value of the cell
 * @param cell cell value
 * @param right not used, but needed for the signature
 * @param top not used, but needed for the signature
 * @param left not used, but needed for the signature
 * @param bottom not used, but needed for the signature
 * @return cell value
 */
double noEffect(double cell, double right, double top, double left, double bottom)
{
    UNUSED(right);
    UNUSED(top);
    UNUSED(left);
    UNUSED(bottom);
    return cell;
}

/**
 * Update the grid, and calculate diff
 * @param function function to apply
 * @param grid the grid
 * @param n height of the grid
 * @param m width of the grid
 * @param sources sources list
 * @param num_sources size of the list
 * @param terminate minimum diff to stop
 * @param n_iter number of iterations to stop
 * @param is_cyclic tell how to deal with borders
 * @return the last difference
 */
double calculate(diff_func function, double **grid, size_t n, size_t m, source_point *sources,
                 size_t num_sources, double terminate, unsigned int n_iter, int is_cyclic)
{
    double prevSum, sum, diff = 0, i = 0;
    prevSum = calculateIteration(noEffect, grid, n, m, sources, num_sources, is_cyclic);
    while (TRUE)
    {
        sum = calculateIteration(function, grid, n, m, sources, num_sources, is_cyclic);
        diff = fabs(sum - prevSum);
        i++;
        if ((n_iter > 0 && i > n_iter) || diff < terminate)
        {
            return diff;
        }
        prevSum = sum;

    }

}
