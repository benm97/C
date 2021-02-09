/**
 * @file my_cos.c
 * @author  benm
 * @date 9 aug 2018
 * @brief Encrypt a text
 * @section DESCRIPTION
 * The system compute the cosinus of an int
 * Input  : int
 * Output : cosinus
 */

// ------------------------------ includes ------------------------------
#include <stdio.h>
/**
 * @def INVALID_MSG a message
 * @brief message for non valid input
 */
#define INVALID_MSG "non valid x\n"

/**
 * @def LOWER_BOUND 0.01
 * @brief message for non valid input
 */
#define LOWER_BOUND 0.01
/**
 * @def PI 3.141529
 * @brief maths pi
 */
#define PI 3.141529

// ------------------------------ functions -----------------------------

double powerThree(double num)
{
    return num * num * num;
}

double sinus(double x)
{
    if (x < 0)
    {
        return -sinus(-x);
    }
    else if (x < LOWER_BOUND)
    {
        return x;
    }
    else
    {
        return 3 * sinus(x / 3.0) - 4 * powerThree(sinus(x / 3.0)); //given formula,no magic numbers
    }
}

int main()
{
    double x = 0;
    if (scanf("%lf", &x) != 1)
    {
        fprintf(stderr, INVALID_MSG);
        return (0);
    }
    printf("%lf", sinus(PI / 2.0 - x));
    return 0;

}