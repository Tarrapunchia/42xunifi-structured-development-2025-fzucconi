# 📚 Book Library Program

## 🧩 Overview

This program loads a library of books from a file and allows the user to search for books by **title** or **author** through a command-line interface. It supports iterative search results and validates file input at runtime.

---

## 🚀 Features

- Load book entries from a file (`file.txt`)
- Search books by:
  - **Author**
  - **Title**
- Interactive menu-driven interface
- Handles malformed input gracefully
- Clean memory management

---

## 🛠️ Compilation

Ensure you have a C compiler installed (e.g., `gcc`). Then compile the program along with its dependencies:

```bash
gcc -Wall -Wextra -Werror main.cpp utils.c -o book_library
```

---

## 🧪 Usage

```bash
./book_library file.txt
```

Or, to show help:

```bash
./book_library --help
./book_library -h
```

---

## 🧠 Program Structure

### `main()`

The main execution flow:

1. Validate arguments
2. Open the book file
3. Populate the internal book library
4. Allow user interaction to search books
5. Free allocated resources and exit

---

## 📂 File Structure

```
📁 project/
├── main.cpp
├── utils.h
├── utils.c
├── file.txt         # Input file with book entries
└── README.md
```

---

## 🧩 Function Summary

### `check_argv(argc, argv)`
- Validates command-line arguments.
- Handles help flags.
- Returns status (`OK` or `KO`).

### `open_file(name, &status)`
- Opens the input file if status is valid.
- Returns file descriptor.

### `populate_library(fd, status, books[])`
- Reads the file line-by-line.
- Validates and parses book entries.
- Calls `add_book(...)` for each line.

### `add_book(line, id, books[])`
- Converts lines to lowercase.
- Checks formatting.
- Adds book to the array if valid.

### `user_search(books[], status)`
- Displays an interactive menu.
- Asks the user to choose search type.
- Prompts for a search string.
- Calls `print_book_infos(...)`.

### `print_book_infos(books, name, selection)`
- Repeatedly calls `search_book(...)` to find and display all matches.

### `search_book(books, query, selection)`
- Implements logic to search by title or author.
- Returns index of match or `-1`.

### `free_library(books)`
- Frees dynamically allocated memory for book data.

---

## 💾 Data Types

- `t_book`: Struct containing a book's metadata.
- `t_selection`: Enum or flags: `AUTHOR`, `TITLE`, `EXIT`, `IDLE`.
- `LIBRARY_SIZE`: Constant that defines the max number of books allowed.

---

## 📌 Notes

- The actual implementation of string conversion, file parsing, and user input is assumed to be in `utils.c/h`.
- Input file format must follow the expected structure for a book entry.
- The program will warn about malformed lines without crashing.

---

## 📜 License

MIT License (or your preferred license)

---

## 👨‍💻 Author

fzucconi
