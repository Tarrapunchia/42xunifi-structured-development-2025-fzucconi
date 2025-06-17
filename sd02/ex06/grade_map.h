#ifndef GRADE_MAP_H
#define GRADE_MAP_H

# ifdef DEBUG
#  include <stdio.h>
#  include <stdlib.h>  
# endif // DEBUG

typedef enum e_mapper
{
    PLUSMINUS,
    PASSFAIL,
    STANDARD
}   GradeMapper;

typedef enum e_grade
{
    A_P,
    A,
    A_M,
    B_P,
    B,
    B_M,
    C_P,
    C,
    C_M,
    D_P,
    D,
    D_M,
    F,
    P
}   t_grade;

static const char grades[14][3] = {"A+", "A", "A-", "B+", "B", "B-", "C+", "C", "C-", "D+", "D", "D-", "F", "P"};

void map_scores(const int *scores, int size, GradeMapper mapper, const char **mapped_grades);

#endif // GRADE_MAPPING_H
