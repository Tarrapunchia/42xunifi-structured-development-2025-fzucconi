#include "utils.h"

int check_argv(int argc, const char** argv)
{
    if (argc != 2)
        return (perror("Error in arguments number."),
                print_instructions(),
                KO);
    if (ft_strcmp(argv[1], "--help") == 0 || ft_strcmp(argv[1], "-h") == 0)
        return (print_instructions(), KO);
    return OK;
}

int open_file(const char* name, int *status)
{
    if (!(*status)) return -1;
    int fd = open("file.txt", O_RDONLY);
    if (fd < 0)
        perror("An error occurred while opening the file");
    return fd;
}

void add_book(const char *line, int id, t_book books[LIBRARY_SIZE])
{
    // 1. convert the string line to its corresponding lowcase string
    // 2. checks if the line format is OK:
    //  2.OK add the book to the library
    //  2.KO print an error msg on the stderr to warn the user that the given book
    //       entry wasn't correctly formatted 
}

int populate_library(int fd, int status, t_book books[LIBRARY_SIZE])
{
    if (!status) return KO;

    int     id = 0;
    char    *line;
    
    // Cycle since there are entries and the number of entries isn't >= LIBRARY_SIZE
    while ((line = get_next_line(fd)) != NULL && id < LIBRARY_SIZE)
    {
        add_book(line, id, books);
        id++;
        free(line);
    }

    return OK;
}

int search_book(t_book *books, const char* query, t_selection selection)
{
    // logic for a book search in the library, returns its index (or -1 if not
    // found) so in the next search i can start searching from that index on,
    // to scout for multiple possible solutions 
}

void    print_book_infos(t_book *books, const char* name,  t_selection selection)
{
    // 1. Prints query string
    // ...
    // 2. in a cycle, invokes search book and prints the found books (or not found)
    int starting_index = 0;
    do
    {
        starting_index = search_book(books + starting_index, name, selection);
        if (starting_index != -1)
        {
            ;// prints book infos at index given
        }
    } while(starting_index != -1);
}

void    user_search(t_book books[LIBRARY_SIZE], int status)
{
    if (!status) return ;

    t_selection selection = IDLE;
    do
    {
        // 1. prints "menu" and asks the user for a choice between:
        //  - search by author (multiple books possibly shown)
        //  - search by title (multiple books possibly shown)
        //
        // 2. ask for a string to search and saves it in the variable name 
        switch (selection) {
        case AUTHOR: print_book_infos(books, name, selection); break;
        case TITLE:  print_book_infos(books, name, selection); break;
        case EXIT: ; // say goodbye to the user
        default: break;
        }
    } while(selection != EXIT);
}

void    free_library(t_book *books);

int main(int argc, const char** argv) {

    int status = KO;
    status = check_argv(argc, argv);
    int fd = open_file(argv[1], &status);

    t_book  books[LIBRARY_SIZE] = {};
    status = populate_library(fd, status, books);
    user_search(books, status);

    // free the library (authors and title)
    free_library(books);

    if (status)
        return OK;
    else
        return KO;
}