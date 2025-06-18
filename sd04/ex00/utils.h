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

#endif
