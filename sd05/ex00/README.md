# 📚 Book Library Program

## 🧩 Overview

This C program loads a library of books from a file and allows the user to search for books by **title** or **author** through a command-line interface. It supports substring search, graceful handling of malformed input, and memory cleanup.

---

## 🚀 Features

- Load up to 1000 book entries from a file
- Search books by:
  - **Author**
  - **Title**
- Interactive, menu-driven terminal interface
- Input validation and file structure enforcement
- Clean memory deallocation on exit

---

## 🛠️ Compilation

Make sure you have a C compiler and the custom libft library. Compile with:

```bash
make
```

---

## 🧪 Usage

```bash
./book_library file.txt
```

To display usage instructions:

```bash
./book_library --help
./book_library -h
```

---

## 📚 Input File Format

Each line in the file should follow the format:

```
id, title, author
```

Example:

```
1, The Hobbit, J.R.R. Tolkien
2, Foundation, Isaac Asimov
```

---

## 🧠 Program Structure

### `main()`

1. Validates command-line arguments
2. Opens the input file
3. Populates the internal book array
4. Launches the interactive user search
5. Frees memory and exits

---

## 📂 File Structure

```
📁 project/
├── 📁 libft/
├── main.cpp
├── utils.h
├── file.txt         # Input file with book entries
├── Makefile         
└── README.md
```

---

## 🧩 Function Summary

### `check_argv(argc, argv)`
- Validates argument count and help flags

### `open_file(name, &status)`
- Opens the input file safely and updates status

### `populate_library(fd, status, books[])`
- Reads each line and delegates validation to `add_book(...)`

### `add_book(line, &idx, books[])`
- Converts input to lowercase
- Splits and trims fields
- Validates formatting and uniqueness of ID
- Appends to book list

### `user_search(books[], status)`
- Shows a looped menu
- Lets user search by author or title
- Ends on exit command

### `print_book_infos(books, selection)`
- Prompts user for a search string
- Calls `search_book(...)` iteratively to print matches

### `search_book(books, &i, query, selection)`
- Returns `OK` if the current book contains the substring

### `free_library(books)`
- Frees dynamically allocated strings in book entries

---

## 💾 Data Types

- `t_book`: Struct for `id`, `title`, `author`
- `t_selection`: Enum: `AUTHOR`, `TITLE`, `IDLE`, `EXIT`
- `LIBRARY_SIZE`: Max book entries (1000)
- `t_bit_flag`: Enum for entry validation (ID, LEN, CORRECT, ERROR)

---

## 📌 Notes

- The program is case-insensitive (input is lowered during processing)
- Input lines not matching the required format are reported and skipped
- Searches are substring-based (not prefix-only)

---

## 👨‍💻 Author

fzucconi
