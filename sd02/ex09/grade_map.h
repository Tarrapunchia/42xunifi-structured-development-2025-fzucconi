#ifndef GRADE_MAP_H
#define GRADE_MAP_H
# include <string.h>
#  include <stdio.h>
#  include <stdlib.h>  

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
    P,
    GRADE_SIZE
}   t_grade;

static const char grades[14][3] = {"A+", "A", "A-", "B+", "B", "B-", "C+", "C", "C-", "D+", "D", "D-", "F", "P"};

typedef struct s_grade_node
{
    char                  *score;
    int                   count;
    struct s_grade_node   *next;
}   GradeNode;

void map_scores(const int *scores, int size, GradeMapper mapper, const char **mapped_grades);
GradeNode *compute_distribution(const char **mapped_grades, int size);
void print_distribution(GradeNode *head);
void free_distribution(GradeNode *head);
#endif // GRADE_MAPPING_H
