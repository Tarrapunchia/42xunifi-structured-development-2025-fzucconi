#ifndef CRITICAL_WINDOWS_H
# define CRITICAL_WINDOWS_H
# define WINDOW_SIZE 5
# include <stdio.h>

typedef enum e_count
{
    safe,
    critical
}   t_count;

int count_critical_windows(const int *readings, int size);

#endif