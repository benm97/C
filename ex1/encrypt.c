/**
 * @file encrypt.c
 * @author  benm
 * @date 9 aug 2018
 * @brief Encrypt a text
 * @section DESCRIPTION
 * The system encrypt a given text using a given key for caesar crypt
 * Input  : Text and const
 * Output : encrypted text
 */

// ------------------------------ includes ------------------------------
#include <stdio.h>

// -------------------------- const definitions -------------------------
/**
 * @def int SIZE 1024
 * @brief size of the buffer
 */
#define SIZE 128
/**
 * @def int ALPHABET_SIZE 26
 * @brief the alphabet size
 */
#define ALPHABET_SIZE 26
/**
 * @def int LOWERCASE_START 97
 * @brief lowercase start index in ascii table
 */
#define LOWERCASE_START 97
/**
 * @def int LOWERCASE_END 122
 * @brief lowercase end index in ascii table
 */
#define LOWERCASE_END 122
/**
 * @def int UPPERCASE_START 65
 * @brief uppercase start index in ascii table
 */
#define UPPERCASE_START 65
/**
 * @def int UPPERCASE_END 92
 * @brief uppercase end index in ascii table
 */
#define UPPERCASE_END 90
/**
 * @def INVALID_MSG a message
 * @brief message for non valid encrypt key
 */
#define INVALID_MSG "non valid encrypt key\n"
// ------------------------------ functions -----------------------------

/**
 * A function to encrypt a character, if it's a letter
 * @param letter char to encrypt
 * @param key the key to encrypt
 * @return encrypted char
 */
char encrypt(char letter, int key)
{
    if (key < 0)
    {
        //let's put a positive key,  (we can do this because zwe use modulo)
        key = key + ALPHABET_SIZE;
    }
    if ((letter >= LOWERCASE_START && letter <= LOWERCASE_END))
    { //If lowercase
        letter = (char) ((((int) (letter) - LOWERCASE_START + key) % ALPHABET_SIZE) +
                         LOWERCASE_START);
    }
    else if ((letter >= UPPERCASE_START && letter <= UPPERCASE_END))
    { //If uppercase
        letter = (char) ((((int) (letter) - UPPERCASE_START + key) % ALPHABET_SIZE) +
                         UPPERCASE_START);
    }
    return letter;
}

/**
 * @brief The main function. Get the key and encrypt the text.
 * @return 0, to tell the system the execution ended without errors.
 */
int main()
{
    int key = 0;
    if (scanf("%d\n", &key) != 1 || key <= -ALPHABET_SIZE ||
        key >= ALPHABET_SIZE)
    {   //Get the key and check it's valid
        fprintf(stderr, INVALID_MSG);
        return (0);
    }
    char text[SIZE] = {};
    while (fgets(text, SIZE, stdin) != NULL)
    {   //fill the buffer until EOF
        for (int i = 0; i < SIZE - 1; i++)
        {
            if (text[i] != 0)
            {
                printf("%c", encrypt(text[i], key)); //print encrypted
            }
        }

        for (int i = 0; i < SIZE; i++)
        {
            text[i] = 0;
        }
    }

    return (0);
}
