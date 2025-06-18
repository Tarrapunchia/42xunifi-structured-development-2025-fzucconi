#ifndef UTILS_H
# define UTILS_H
# define KO 0
# define OK 1
# define LIBRARY_SIZE 1000
# include <fcntl.h>     // per open
# include <unistd.h>    // per close
# include <stdlib.h>    // per free
# include <stdio.h>     // per perror

// LIBFT AND ALLOWED FUNCTIONS
void    free(void *ptr);
void    *malloc(unsigned n);
int     ft_strcmp(const char* s1, const char* s2);


// STRUCTS
typedef struct s_book
{
    int     id;
    char    *author;
    char    *title;
}   t_book;

typedef enum e_selection : int
{
    AUTHOR,
    TITLE,
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
int check_argv(int argc, const char** argv)

/*********************************************************************************
 * Tries to open the file passed as argument, update the status flag in the main *
 *********************************************************************************/
int open_file(const char* name, int *status)

/**********************************************************************************
* // 1. convert the string line to its corresponding lowcase string              *
* // 2. checks if the line format is OK:                                         *
* //  2.OK add the book to the library                                           *
* //  2.KO print an error msg on the stderr to warn the user that the given book *
* //       entry wasn't correctly formatted                                      *
**********************************************************************************/
void add_book(const char *line, int id, t_book books[LIBRARY_SIZE]);


/************************************************************************************
 * // Cycle since there are entries and the number of entries isn't >= LIBRARY_SIZE *
 ************************************************************************************/
int populate_library(int fd, int status, t_book books[LIBRARY_SIZE]);

/******************************************************************************
* // logic for a book search in the library, returns its index (or -1 if not *
* // found) so in the next search i can start searching from that index on,  *
* // to scout for multiple possible solutions                                *
******************************************************************************/
int search_book(t_book *books, const char* query, t_selection selection);

/***********************************************************************************
* // 1. Prints query string                                                       *
* // 2. in a cycle, invokes search book and prints the found books (or not found) *
***********************************************************************************/
void    print_book_infos(t_book *books, const char* name,  t_selection selection);

/**********************************************************************
* // 1. prints "menu" and asks the user for a choice between:        *
* //  - search by author (multiple books possibly shown)             *
* //  - search by title (multiple books possibly shown)              *
* //                                                                 *
* // 2. ask for a string to search and saves it in the variable name *
**********************************************************************/
void    user_search(t_book books[LIBRARY_SIZE], int status);

/**********************************************
 * Frees the memory allocated for the library *
 **********************************************/
void    free_library(t_book *books);
#endif
