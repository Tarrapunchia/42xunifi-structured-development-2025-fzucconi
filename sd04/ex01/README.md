# 💸 Expense Tracker Program

## 🧩 Overview

This program loads a list of expenses from a file and allows the user to search and display expenses based on **category**, **name**, or **date** using a terminal-based interface. It also provides statistics like total expenses, count, and average for the selected query.

---

## 🚀 Features

- Load expense entries from a file (`file.txt`)
- Search by:
  - **Category**
  - **Name**
  - **Date range**
- View all expenses
- Summary statistics:
  - Total records found
  - Total amount spent
  - Average per entry

---

## 🛠️ Compilation

Compile with a C compiler such as `gcc`:

```bash
gcc -Wall -Wextra -Werror main.c utils.c -o expense_tracker
```

---

## 🧪 Usage

```bash
./expense_tracker file.txt
```

To show help:

```bash
./expense_tracker --help
./expense_tracker -h
```

---

## 🧠 Program Structure

### `main()`

1. Validate arguments
2. Open the input file
3. Populate the `expenses` array
4. Start the interactive user interface
5. Free resources and exit

---

## 📂 File Structure

```
📁 project/
├── main.c
├── utils.c
├── utils.h
├── file.txt
└── README.md
```

---

## 🔧 Function Overview

### `check_argv(argc, argv)`
- Validates command-line arguments and help flags.

### `open_file(name, &status)`
- Opens the file and updates the status flag.

### `populate_expenses(fd, status, expenses[])`
- Reads entries line by line using `get_next_line()`.
- Validates and populates the `expenses` array via `add_expense()`.

### `add_expense(line, id, expenses[])`
- Converts strings to lowercase.
- Checks format validity.
- Adds to list or prints an error if the format is invalid.

### `user_search(expenses[], status)`
- Presents a menu for:
  - Search by category
  - Search by name
  - Search by date range
  - View all expenses
- Captures input and invokes appropriate handlers.

### `print_expense_infos(expenses, query, selection)`
- Calls `search_expense()` in a loop.
- Displays matched records.
- Computes:
  - Count
  - Total
  - Average

### `search_expense(expenses, query, selection)`
- Searches based on `selection`:
  - Category
  - Name
  - Date range
- Supports partial and multiple results.
- Returns the index of a match or -1.

### `free_expenses(expenses)`
- Frees dynamically allocated fields for each expense.

---

## 💾 Data Types

- `t_expense`: Struct with fields: `id`, `category`, `name`, and `date`.
- `t_selection`: Enum for current mode: `CATEGORY`, `NAME`, `DATE`, `EXIT`, etc.
- `EXPENSES_SIZE`: Maximum number of entries.

---

## 📌 Notes

- Requires a valid format per line in `file.txt`.
- Gracefully handles invalid or malformed entries.
- The date range search includes validation of dates entered by the user.
- This is a generalization of the assignment and requires further implementation to be fully functional

---

## 👨‍💻 Author

fzucconi
