#include "password_validator.h"

int is_special(char c)
{
    return ((c >= 35 && c <= 38) || (c == 42) || (c == 64) || (c == '^'));
}

PwStatus validate(const char *new_pw, const char *curr_pw)
{
    if (!curr_pw)
        return VALID;
    PwStatus pw_stat = INVALID_WEAK;
    t_valid valid = 0x00;
    int i = 0;
    for (; new_pw[i]; i++)
    {
        // uppercase
        if (!(valid & UPPER) && new_pw[i] >= 'A' && new_pw[i] <= 'Z')
            valid = valid | UPPER;

        // lowercase
        else if (!(valid & LOWER) && new_pw[i] >= 'a' && new_pw[i] <= 'z')
            valid = valid | LOWER;

        // digit
        else if (!(valid & DIGIT) && new_pw[i] >= '0' && new_pw[i] <= '9')
            valid = valid | DIGIT;

        // special
        else if (!(valid & SPECIAL) && is_special(new_pw[i]))
            valid = valid | SPECIAL;

        // differ
        if (!(curr_pw[i]) || (!(valid & DIFFER) && new_pw[i] != curr_pw[i]))
            valid = valid | DIFFER;
    }
    // len
    if (i >= 7)
        valid = valid | LENGTH;
    
    if ((valid & OK) == OK) return (VALID);
    else return (INVALID_WEAK);
}
