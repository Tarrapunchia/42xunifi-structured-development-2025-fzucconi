# 📇 Contact Manager Program

## 🧩 Overview

This program manages a list of contacts stored in a file. It allows the user to search, add, edit, delete, and list contacts through a terminal-based menu. Input is validated for correctness using bitflag checks. Temporary modifications can be saved explicitly.

---

## 🚀 Features

- Load contacts from a file
- Search by:
  - **Name**
  - **City**
- Add new contacts
- Edit or delete existing contacts
- List all contacts
- Save changes
- Input validation for:
  - ID uniqueness
  - Valid phone numbers and emails
  - Non-empty name and city
- Interactive user interface

---

## 🛠️ Compilation

Compile with a C compiler such as `gcc`:

```bash
gcc -Wall -Wextra -Werror main.c utils.c -o contact_manager
```

---

## 🧪 Usage

```bash
./contact_manager file.txt
```

To show help:

```bash
./contact_manager --help
./contact_manager -h
```

---

## 🧠 Program Structure

### `main()`

1. Validate arguments
2. Open the contact file
3. Populate the `contacts` array
4. Run the interactive user interface
5. Free memory and exit

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
- Validates command-line arguments and handles help flags.

### `open_file(name, &status)`
- Opens the input file and updates the status flag.

### `populate_contacts(fd, status, contacts[])`
- Reads entries line-by-line.
- Validates and stores contacts using `add_contact()`.

### `check_correctness(line)`
- Validates fields:
  - ID: uniqueness
  - Name and city: non-empty
  - Phone: valid format
  - Email: proper structure
- Uses bitflags to determine overall validity.

### `add_contact(line, contacts[])`
- Converts the line to lowercase.
- Validates it with `check_correctness()`.
- Adds the contact or prints an error if invalid.

### `set_contact(contacts[])`
- Prompts user to input contact details.
- Adds the contact using `add_contact()`.

### `list_all(contacts[])`
- Lists all contacts using `print_contact_infos()`.

### `print_contact_infos(contacts, query, selection)`
- Displays all matches for a given search.
- Can be used for name or city searches.

### `search_contact(contacts, query, selection)`
- Searches contacts by name or city.
- Returns the index of a matching contact.

### `user_ui(contacts[], status)`
- Creates a temporary working list.
- Shows a menu to:
  - List all contacts
  - Search by name/city
  - Add, edit, or delete contacts
  - Save changes to main contact list
  - Exit program

### `free_contacts(contacts)`
- Frees any dynamically allocated fields of each contact.

---

## 💾 Data Types

- `t_contact`: Struct with fields `id`, `name`, `phone`, `email`, `city`, `address`.
- `t_selection`: Enum for user menu options.
- `t_bit_flag`: Bitmask-based validation flags.
- `CONTACTS_SIZE`: Maximum number of entries.

---

## 📌 Notes

- Changes are only saved after choosing the "Save" option.
- Contacts are validated before being accepted.
- Input parsing and validation are modular and reusable.
- This is a generalization of the assignment and requires further implementation to be fully functional

---

## 👨‍💻 Author

fzucconi
