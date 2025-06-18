#ifndef UTILS_H
# define UTILS_H
# define CONTACTS_SIZE 1000

typedef struct s_contact
{
    int     id;
    char    *name;
    char    *phone;
    char    *email;
    char    *city;
    char    *address;
}   t_contact;

typedef enum e_selection : int
{
    LIST_ALL,
    SEARCH_NAME,
    SEARCH_CITY,
    ADD_CONTACT,
    EDIT_CONTACT,
    DELETE_CONTACT,
    SAVE,
    EXIT = 9
}   t_selection;

typedef enum e_flags
{
    ID      = 0x01,
    PERSON  = 0x10,
    CITY    = 0x100,
    EMAIL   = 0x1000,
    PHONE   = 0x10000,
    ADDRESS = 0x100000,
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
t_bit_flag  check_id(int id, t_contact *contacts);

/******************************************************************
 * Checks if a given name or city is non empty after trimming     *
 * and returns ERROR if it is else PERSON or ADDRESS (t_bit_flag) *
 ******************************************************************/
t_bit_flag  check_str(const char* str);

/****************************************************************************************
 * Checks that phone use only digits and typical symbols and include at least one digit *
 * and returns ERROR if not or PHONE (t_bit_flag)                                       *
 ****************************************************************************************/
t_bit_flag  check_phone(const char* phone);

/****************************************************************************************
 * Checks that email has one '@' with non-empty local and domain parts and at least one *
 * dot in the domain and returns ERROR if not or EMAIL (t_bit_flag)                     *
 ****************************************************************************************/
t_bit_flag  check_mail(const char* mail);

/***************************************************************************************************
 * Checks the correctness of the entry passed using the t_bit_flag bitflag, invoking sequentially: *
 *     - check_id(...);                                                                            *
 *     - check_str(...); twice, once for the contact name and once for the city name               *
 *     - check_phone(...);                                                                         *
 *     - check_mail(...);                                                                          *
 * and putting the results in & with a t_bit_flag flag initialized to 0x00                         *
 * the return is flag == CORRECT (KO if not equal, OK if equal)                                    *
 ***************************************************************************************************/
int  check_correctness(const char* line);

/**********************************************************************************
* // 1. convert the string line to its corresponding lowcase string                 *
* // 2. checks if the line format is OK using check correctness(...)                *
* //  2.OK add the contact to the contacts in the first unused spot                 *
* //  2.KO print an error msg on the stderr to warn the user that the given contact *
* //       entry wasn't correctly formatted                                         *
**********************************************************************************/
void add_contact(const char *line, t_contact contacts[CONTACTS_SIZE]);

/**********************************************************
 * Ask for contact details and passes to add contact(...) *
 **********************************************************/
void set_contact(t_contact *contacts);

/************************************************************************************
 * // Cycle since there are entries and the number of entries isn't >= CONTACTS_SIZE *
 ************************************************************************************/
int populate_contacts(int fd, int status, t_contact contacts[CONTACTS_SIZE]);

/******************************************************************************
* // logic for a contact search in the contactS, returns its index (or -1 if not *
* // found) so in the next search i can start searching from that index on,      *
* // to scout for multiple possible solutions                                    *
******************************************************************************/
int search_contact(t_contact *contacts, const char* query, t_selection selection);

/***********************************************************************************************
 * Prints all the contacts info iterating on the contacts array using print_contact_infos(...) *
 ***********************************************************************************************/
void list_all(t_contact *contacts);

/***********************************************************************************
* // 1. Prints query string                                                             *
* // 2. in a cycle, invokes search contact and prints the found contacts (or not found) *
* //    keeping score of the average contact, the total number of records considered and*
* //    the total amount spent in them                                                  *
* // 3. At the end of the cicle prints the 3 parameters listed in point 2               *
***********************************************************************************/
void    print_contact_infos(t_contact *contacts, const char* name,  t_selection selection);

/*******************************************************************************************
 * 1. Copies the "master" contact list in a temp contact list to use
 * 2. prints "menu" and asks the user for a choice between:                                *
 *  - list all contacts (by calling list_all(...))                                         *
 *  - search by name (multiple contacts possibly shown)  (using search_contatc(...))       *
 *  - search by city (multiple contacts possibly shown)  (using search_contatc(...))       *
 *  - add contact (using set_contact(...))                                                 *
 *  - edit contact (using search_contact and then using that id to edit the first found)   *
 *  - delete contact (same as edit contact)                                                *
 *  - save (copy the temporary contact list in the original contact list, overwrtiting it) *
 *  - exit                                                                                 *
 *******************************************************************************************/
void    user_ui(t_contact contacts[CONTACTS_SIZE], int status);

/**********************************************
 * Frees the memory allocated for the contactS *
 **********************************************/
void    free_contacts(t_contact *contacts);
#endif