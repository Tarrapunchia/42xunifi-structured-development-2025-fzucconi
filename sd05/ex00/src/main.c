#include "utils.h"

void    print_instructions()
{
    ft_printf("%s\n", instructions);
}

int check_argv(int argc, const char** argv)
{
    if (argc != 2)
        return (perror("Error in arguments number."),
                print_instructions(),
                KO);
    if (ft_strncmp(argv[1], "--help", sizeof(argv[1])) == 0
        || ft_strncmp(argv[1], "-h", sizeof(argv[1]) == 0))
        return (print_instructions(), KO);
    return OK;
}

int open_file(const char* name, int *status)
{
    if (!(*status)) return -1;
    int fd = open(name, O_RDONLY);
    if (fd < 0)
        perror("An error occurred while opening the file");
    return fd;
}

void    str_to_lower(char *str)
{
    for (size_t i = 0; i < ft_strlen(str); i++)
        str[i] = ft_tolower(str[i]);
}

t_bit_flag  check_id(int id, t_book *books)
{
    size_t i = 0;
    for (; i < LIBRARY_SIZE && books[i].id != id; i++)
        ;
    return (LIBRARY_SIZE == i)? ID: ERROR;
}

int check_correctness(t_book *books, char **fields)
{
    int len = 0;

    for (size_t i = 0; fields[i]; i++)
        len++;
    if (len == 3 && check_id(ft_atoi(fields[0]), books) == ID)
        return OK;
    return KO;
}

void add_book(char *line, int *idx, t_book *books)
{
    // 1. convert the string line to its corresponding lowcase string
    str_to_lower(line);
    // 2. checks if the line format is OK:
    //  2.OK add the book to the library
    //  2.KO print an error msg on the stderr to warn the user that the given book
    //       entry wasn't correctly formatted
    char **fields = ft_split(line, ',');
    if (fields && check_correctness(books, fields))
    {
        books[*idx].id = ft_atoi(fields[0]);
        books[*idx].title = ft_strtrim(fields[1], " ");
        books[*idx].author = ft_strtrim(fields[2], " ");
        ft_free_matrix(fields);
        (*idx)++;
    }
    else
        ft_perror("Error in line :\"%s\"", line);

}

int populate_library(int fd, int status, t_book *books)
{
    if (!status) return KO;

    int     idx = 0;
    char    *line;
    
    // Cycle since there are entries and the number of entries isn't >= LIBRARY_SIZE
    while ((line = ft_get_next_line(fd)) != NULL && idx < LIBRARY_SIZE)
    {
        add_book(line, &idx, books);
        free(line);
    }
    close(fd);
    return OK;
}

int search_book(t_book *books, int *i, char *query, t_selection selection)
{
    char *trimmed = ft_strtrim(query, " ");
    if (!trimmed)
        return KO;

    for (; *i < LIBRARY_SIZE; (*i)++)
    {
        if (selection == AUTHOR)
        {
            if (books[*i].author && ft_strnstr(books[*i].author, trimmed, ft_strlen(books[*i].author)))
            {
                free(trimmed);
                return OK;
            }
        }
        else if (selection == TITLE)
        {
            if (books[*i].title && ft_strnstr(books[*i].title, trimmed, ft_strlen(books[*i].title)))
            {
                free(trimmed);
                return OK;
            }
        }
    }
    free(trimmed);
    return KO;
}

void    print_book_infos(t_book *books, t_selection selection)
{
    // 1. Ask query string
    char query[100] = "";
    ft_printf("Input the string to search: ");
    scanf("%99s", query);
    if (ft_strlen(query) == 0)
    {
        ft_printf("Invalid query: %s\n", query);
    }
    // ...
    // 2. in a cycle, invokes search book and prints the found books (or not found)
    else
    {
        for (int i = 0; i < LIBRARY_SIZE; i++)
        {
            if (search_book(books, &i, query, selection))
            {
                ft_printf("\t[ID]: %d\t[AUTHOR]: %s\t[TITLE]: %s\n\n", books[i].id, books[i].author, books[i].title);
            }
        };
    }
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
        ft_printf("Select your action to perform:\n");
        ft_printf("[1] : search by author\n");
        ft_printf("[2] : search by title\n");
        ft_printf("[9] : exit program\n");
        int buf = 0;
        ft_printf("Selection [1,2,9]: ");
        scanf("%d", &buf);
        selection = (t_selection)buf;
        // 2. ask for a string to search and saves it in the variable name 
        switch (selection) {
        case AUTHOR: print_book_infos(books, selection); break;
        case TITLE:  print_book_infos(books, selection); break;
        case EXIT: ft_printf("Goodbye!\n"); break; // say goodbye to the user
        default: ft_printf("Wrong input, try again.\n\n"); break;
        }
    } while(selection != EXIT);
}

void    free_library(t_book *books)
{
    for (size_t i = 0; i < LIBRARY_SIZE; i++)
    {
        if (books[i].author)
            free(books[i].author);
        if (books[i].title)
            free(books[i].title);
    }
}

int main(int argc, const char** argv) {

    int status = KO;
    status = check_argv(argc, argv);
    int fd = open_file(argv[1], &status);
    if (fd < 0) status = KO;

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