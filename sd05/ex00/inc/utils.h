#ifndef UTILS_H
# define UTILS_H
# define KO 0
# define OK 1
# define LIBRARY_SIZE 1000
# include <fcntl.h>     // per open
# include <unistd.h>    // per close
# include <stdlib.h>    // per free
# include <stdio.h>     // per perror
# include <ctype.h>
# include "libft.h"

const char instructions[] = "This program loads a library of books from a file and allows the user to search for books by **title** or **author** \nthrough a command-line interface.\n\
It supports iterative search results and validates file input at runtime.\n\
Usage: ./book_library file.txt \
       type --help or -h to repeat the infos.";

typedef enum e_flags
{
    ID      = 0x01,
    LEN     = 0x10,
    CORRECT = 0x11,
    ERROR   = 0x00
}   t_bit_flag;

// STRUCTS
typedef struct s_book
{
    int     id;
    char    *author;
    char    *title;
}   t_book;

typedef enum e_selection
{
    AUTHOR = 1,
    TITLE = 2,
    IDLE,
    EXIT = 9
}   t_selection;

/*
*   Prints an helper on the terminal to aid help the user understand how to pass
*   args to the function and how to use the terminal based ui
*/
void    print_instructions();

/****
 *  Checks if argv are passed coherentely and if you are asking for the --help *
 ****/
int check_argv(int argc, const char** argv);

/*********************************************************************************
 * Tries to open the file passed as argument, update the status flag in the main *
 *********************************************************************************/
int open_file(const char* name, int *status);

/****************************************************************************************
 * Checks if a given id is already used and returns ERROR if it is else ID (t_bit_flag) *
 ****************************************************************************************/
t_bit_flag  check_id(int id, t_book *books);

/***************************************************************************************************
 * Checks the correctness of the entry passed using the t_bit_flag bitflag, invoking sequentially: *
 *     - check_len(...);                     *
 *     - check_id(...);                                                                            *
 * and putting the results in & with a t_bit_flag flag initialized to 0x00                         *
 * the return is flag == CORRECT (KO if not equal, OK if equal)                                    *
 ***************************************************************************************************/
int  check_correctness(t_book *books, char **fields);

/**********************************************************************************
* // 1. convert the string line to its corresponding lowcase string              *
* // 2. checks if the line format is OK:                                         *
* //  2.OK add the book to the library                                           *
* //  2.KO print an error msg on the stderr to warn the user that the given book *
* //       entry wasn't correctly formatted                                      *
**********************************************************************************/
void add_book(char *line, int *id, t_book *books);


/************************************************************************************
 * // Cycle since there are entries and the number of entries isn't >= LIBRARY_SIZE *
 ************************************************************************************/
int populate_library(int fd, int status, t_book *books);

/******************************************************************************
* // logic for a book search in the library, returns its OK or KO                         *
******************************************************************************/
int search_book(t_book *books, int *i, char* query, t_selection selection);

/***********************************************************************************
* // 1. Prints query string                                                       *
* // 2. in a cycle, invokes search book and prints the found books (or not found) *
***********************************************************************************/
void    print_book_infos(t_book *books, t_selection selection);

/**********************************************************************
* // 1. prints "menu" and asks the user for a choice between:        *
* //  - search by author (multiple books possibly shown)             *
* //  - search by title (multiple books possibly shown)              *
* //  - exit program                                                 *
* // 2. ask for a string to search and saves it in the variable name *
**********************************************************************/
void    user_search(t_book books[LIBRARY_SIZE], int status);

/**********************************************
 * Frees the memory allocated for the library *
 **********************************************/
void    free_library(t_book *books);
#endif
