📚 Book Library Program – Documentation
🧩 Purpose
This program loads a library of books from a file and allows the user to search for books by title or author through a terminal-based interface. Results are displayed iteratively. The overall flow is controlled through modular functions.

🧠 Program Flow Overview
The main execution flow is as follows:

✅ Argument validation – check_argv

📂 Open the input file – open_file

📚 Load the book entries into memory – populate_library

🔎 User interface for searching – user_search

🧹 Free allocated resources – free_library

🚪 Exit the program

This structure matches the structure chart you've provided.

🔍 Main Functions Description
check_argv(int argc, const char** argv)
Ensures that exactly one argument is passed (the file name).

Also handles --help and -h options by printing usage instructions and exiting.

Returns a status flag (OK or KO).

open_file(const char* name, int *status)
Opens the file in read-only mode (O_RDONLY) if the status is still valid.

Returns a file descriptor (int fd) to be used later for reading.

populate_library(int fd, int status, t_book books[LIBRARY_SIZE])
Reads lines from the file (using get_next_line) and populates the books array.

Calls add_book(line, id, books) to process each line and fill the library.

Stops reading either when end-of-file is reached or when the library is full.

add_book(const char *line, int id, t_book books[])
Processes each line:

Converts the line to lowercase.

Validates its format.

Adds the book data to the library if the format is correct.

Prints an error to stderr if the format is invalid.

user_search(t_book books[], int status)
Presents the user with a search menu:

Search by author

Search by title

Exit

Depending on the user's choice, it:

Prompts for a search string.

Calls print_book_infos(...) with the appropriate search criteria.

print_book_infos(t_book *books, const char* name, t_selection selection)
Performs the actual search loop using search_book.

Displays each matching book.

Continues to search from the last found index to allow multiple results.

search_book(t_book *books, const char* query, t_selection selection)
Implements the search logic, depending on whether it's by title or author.

Returns the index of a matching book, or -1 if none is found.

free_library(t_book *books)
Frees any dynamically allocated memory for book titles and authors.

✅ Exit Conditions
If all steps complete successfully, the program exits with OK.

Otherwise, it exits with KO, signaling a failure (e.g., invalid input or file issues).

🧠 Data Structures
The code references:

t_book: a structure that holds book metadata (likely title, author, etc.)

t_selection: an enum or flag indicating the current search mode (AUTHOR, TITLE, EXIT, IDLE)

LIBRARY_SIZE: a constant defining the maximum number of books that can be loaded