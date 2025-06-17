#ifndef PASSWORD_VALIDATOR_H
# define PASSWORD_VALIDATOR_H
# include <stdlib.h>
# include <string.h>

# ifdef TEST
#  include <stdio.h>
# endif

typedef enum s_valid
{
    LENGTH  = 0x01,
    UPPER   = 0x10,
    LOWER   = 0x100,
    DIGIT   = 0x1000,
    SPECIAL = 0x10000,
    DIFFER  = 0x100000,
    OK   = 0x111111
}   t_valid;

typedef enum s_state
{
    VALID           = 0,
    INVALID_WEAK    = 1,
    INVALID_SIMILAR = 2,
    FAILURE         = 4
}   PwStatus;

typedef struct s_history
{
    char             *pw;
    struct s_history *next;
} PasswordHistory;

// typedef char *PasswordHistory;

PwStatus validate(const char *new_pw, const char *curr_pw);
PwStatus validate_password(const char *new_pw, PasswordHistory *history);

#endif // PASSWORD_VALIDATOR_H
