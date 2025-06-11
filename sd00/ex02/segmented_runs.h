#ifndef SEGMENTED_RUNS_H
# define SEGMENTED_RUNS_H
# include <stddef.h>

typedef enum e_bool {
    FALSE,
    TRUE
}   t_bool;

int count_segments(const int *arr, int size);

#endif