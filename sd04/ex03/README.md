# 🎬 Movie Management Program

## 🧩 Overview

This C program allows users to manage a movie database from a file using a terminal-based interface. Users can add, edit, delete, and search for movies by different criteria. The program includes input validation, memory cleanup, and the ability to persist changes.

---

## 🚀 Features

- Load up to 1000 movie entries from a file
- Search movies by:
  - **Title**
  - **Genre**
  - **Watched/Unwatched status**
- Add, edit, and delete movie entries
- Save changes to persist the session
- Validates each movie's ID, title, genre, watched status, rating, and date
- Menu-based interactive interface

---

## 🛠️ Compilation

Compile the program along with any dependencies (e.g., libft):

```bash
gcc main.c libft.a -o movie_manager
```

---

## 🧪 Usage

```bash
./movie_manager movies.txt
```

To show help:

```bash
./movie_manager --help
./movie_manager -h
```

---

## 📚 Input File Format

Each movie must be listed on a single line with the format:

```
id, title, genre, watched, rating, date
```

Example:

```
1, The Matrix, Sci-Fi, 1, 9, 2022-01-12
2, Inception, Sci-Fi, 0, 0, 2023-06-02
```

---

## 🧠 Program Structure

### `main()`

1. Validates command-line arguments
2. Opens and reads the movie file
3. Populates the movie list
4. Launches the interactive user interface
5. Frees memory and exits

---

## 🧩 Function Summary

### `check_argv(argc, argv)`
- Validates input arguments and handles help flags

### `open_file(name, &status)`
- Opens the specified file and updates the status

### `populate_movies(fd, status, movies[])`
- Parses file lines and fills the movie list

### `check_correctness(line)`
- Verifies field validity using bit flags for ID, TITLE, GENRE, WATCHED, RATING, DATE

### `add_movie(line, movies[])`
- Adds a movie entry if valid

### `set_movie(movies)`
- Interactively prompts user to input new movie data

### `search_movie(movies, query, selection)`
- Finds the index of matching movie(s) by title, genre, or watched status

### `list_all(movies)`
- Displays all movies in the database

### `print_movie_infos(movies, name, selection)`
- Prints all matches for a query and displays summary statistics

### `user_ui(movies[], status)`
- Provides a menu for:
  - Listing all movies
  - Searching
  - Adding, editing, deleting
  - Saving or exiting

### `free_movies(movies)`
- Frees memory allocated for movie strings

---

## 💾 Data Types

- `t_movie`: Struct with `id`, `title`, `genre`, `watched`, `rating`, `date`
- `t_selection`: Enum for UI menu choices
- `t_bit_flag`: Bitmask flags used in validation

---

## 📌 Notes

- All fields are trimmed and validated
- Watched is `0` or `1`, rating is `1-10` if watched, otherwise `0`
- The program is designed for robustness and extendibility
- Invalid lines are reported without terminating execution

---

## 👨‍💻 Author

fzucconi
