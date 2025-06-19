#ifndef UTILS_H
# define UTILS_H
# define MOVIES_SIZE 1000

typedef struct s_movie
{
    int     id;
    char    *title;
    char    *genre;
    int     watched;
    int     rating;
    char    *date;
}   t_movie;

typedef enum e_selection : int
{
    LIST_ALL,
    SEARCH_NAME,
    SEARCH_CITY,
    ADD_movie,
    EDIT_movie,
    DELETE_movie,
    SAVE,
    EXIT = 9
}   t_selection;

typedef enum e_flags
{
    ID      = 0x01,
    TITLE   = 0x10,
    GENRE   = 0x100,
    WATCHED = 0x1000,
    RATING  = 0x10000,
    DATE    = 0x100000,
    CORRECT = 0x111111,
    ERROR   = 0x00
}   t_bit_flag;

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
t_bit_flag  check_id(int id, t_movie *movies);

/******************************************************************
 * Checks if a given title or genre is non empty after trimming   *
 * and returns ERROR if it is else TITLE or GENRE (t_bit_flag)    *
 ******************************************************************/
t_bit_flag  check_str(const char* str);

/****************************************************************************************
 * Checks that t_movie::watched is exactly 0 or 1                                       *
 * and returns ERROR if not or WHATCHED (t_bit_flag)                                    *
 ****************************************************************************************/
t_bit_flag  check_flag(const char* phone);

/****************************************************************************************
 * Checks that if marked watched, rating id an integer from 1 to 10 (otherwise 0)       *
 * dot in the domain and returns ERROR if not or RATING (t_bit_flag)                    *
 ****************************************************************************************/
t_bit_flag  check_rating(const char* mail);

/***************************************************************************************************
 * Checks the correctness of the entry passed using the t_bit_flag bitflag, invoking sequentially: *
 *     - check_id(...);                                                                            *
 *     - check_str(...); twice, once for the movie name and once for the genre                     *
 *     - check_rating(...);                                                                        *
 *     - check_flag(...);                                                                          *
 * and putting the results in & with a t_bit_flag flag initialized to 0x00                         *
 * the return is flag == CORRECT (KO if not equal, OK if equal)                                    *
 ***************************************************************************************************/
int  check_correctness(const char* line);

/**********************************************************************************
* // 1. convert the string line to its corresponding lowcase string                 *
* // 2. checks if the line format is OK using check correctness(...)                *
* //  2.OK add the movie to the movies in the first unused spot                 *
* //  2.KO print an error msg on the stderr to warn the user that the given movie *
* //       entry wasn't correctly formatted                                         *
**********************************************************************************/
void add_movie(const char *line, t_movie movies[MOVIES_SIZE]);

/**********************************************************
 * Ask for movie details and passes to add movie(...) *
 **********************************************************/
void set_movie(t_movie *movies);

/************************************************************************************
 * // Cycle since there are entries and the number of entries isn't >= MOVIES_SIZE *
 ************************************************************************************/
int populate_movies(int fd, int status, t_movie movies[MOVIES_SIZE]);

/******************************************************************************
* // logic for a movie search in the movieS, returns its index (or -1 if not *
* // found) so in the next search i can start searching from that index on,      *
* // to scout for multiple possible solutions                                    *
******************************************************************************/
int search_movie(t_movie *movies, const char* query, t_selection selection);

/***********************************************************************************************
 * Prints all the movies info iterating on the movies array using print_movie_infos(...) *
 ***********************************************************************************************/
void list_all(t_movie *movies);

/***********************************************************************************
* // 1. Prints query string                                                             *
* // 2. in a cycle, invokes search movie and prints the found movies (or not found) *
* //    keeping score of the average movie, the total number of records considered and*
* //    the total amount spent in them                                                  *
* // 3. At the end of the cicle prints the 3 parameters listed in point 2               *
***********************************************************************************/
void    print_movie_infos(t_movie *movies, const char* name,  t_selection selection);

/*******************************************************************************************
 * 1. Copies the "master" movie list in a temp movie list to use
 * 2. prints "menu" and asks the user for a choice between:                                *
 *  - list all movies by ascending id (by calling list_all(...)                            *
 *  - search by title (multiple movies possibly shown)  (using search_movie(...))       *
 *  - search by genre (multiple movies possibly shown)  (using search_movie(...))       *
 *  - search by watched/unwatched (multiple movies possibly shown)(using search_movie(...))*
 *  - add movie (using set_movie(...))                                                 *
 *  - edit movie (using search_movie and then using that id to edit the first found)   *
 *  - delete movie (same as edit movie)                                                *
 *  - save (copy the temporary movie list in the original movie list, overwrtiting it) *
 *  - exit                                                                                 *
 *******************************************************************************************/
void    user_ui(t_movie movies[MOVIES_SIZE], int status);

/**********************************************
 * Frees the memory allocated for the movieS *
 **********************************************/
void    free_movies(t_movie *movies);
#endif