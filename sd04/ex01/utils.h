#ifndef UTILS_H
# define UTILS_H
# define KO 0
# define OK 1
# define EXPENSES_SIZE 1000
# include <fcntl.h>     // per open
# include <unistd.h>    // per close
# include <stdlib.h>    // per free
# include <stdio.h>     // per perror

// LIBFT AND ALLOWED FUNCTIONS
void    free(void *ptr);
void    *malloc(unsigned n);
int     ft_strcmp(const char* s1, const char* s2);


// STRUCTS
typedef struct s_expense
{
    int     id;
    char    *category;
    char    *name;
    char    *date;
}   t_expense;

typedef enum e_selection : int
{
    CATEGORY,
    NAME,
    DATE,
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


/**********************************************************************************
* // 1. convert the string line to its corresponding lowcase string                 *
* // 2. checks if the line format is OK:                                            *
* //  2.OK add the expense to the expenses                                          *
* //  2.KO print an error msg on the stderr to warn the user that the given expense *
* //       entry wasn't correctly formatted                                         *
**********************************************************************************/
void add_expense(const char *line, int id, t_expense expenses[EXPENSES_SIZE]);


/************************************************************************************
 * // Cycle since there are entries and the number of entries isn't >= EXPENSES_SIZE *
 ************************************************************************************/
int populate_expenses(int fd, int status, t_expense expenses[EXPENSES_SIZE]);

/******************************************************************************
* // logic for a expense search in the EXPENSES, returns its index (or -1 if not *
* // found) so in the next search i can start searching from that index on,      *
* // to scout for multiple possible solutions                                    *
* // Asks for two dates if searching by date (logic check if date                *
* // is valid included)                                                          *
******************************************************************************/
int search_expense(t_expense *expenses, const char* query, t_selection selection);

/***********************************************************************************
* // 1. Prints query string                                                             *
* // 2. in a cycle, invokes search expense and prints the found expenses (or not found) *
* //    keeping score of the average expense, the total number of records considered and*
* //    the total amount spent in them                                                  *
* // 3. At the end of the cicle prints the 3 parameters listed in point 2               *
***********************************************************************************/
void    print_expense_infos(t_expense *expenses, const char* name,  t_selection selection);

/**********************************************************************
* // 1. prints "menu" and asks the user for a choice between:                *
* //  - search by category (multiple expenses possibly shown)                *
* //  - search by date (multiple expenses possibly shown)                    *
* //  - list all expenses (by calling print_expense_info on all the entries) *
* //                                                                         *
* // 2. ask for a string to search and saves it in the variable name         *
**********************************************************************/
void    user_search(t_expense expenses[EXPENSES_SIZE], int status);

/**********************************************
 * Frees the memory allocated for the EXPENSES *
 **********************************************/
void    free_expenses(t_expense *expenses);
#endif