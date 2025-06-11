#include "grade_map.h"
#include <stdlib.h>

int create_node(GradeNode *node, int count, const char *name)
{
    if (count == 0)
        return 0;
    int len = strlen(name);
    node->next = malloc(sizeof(GradeNode));
    node->next->count = count;
    node->next->score = malloc(sizeof(char) * len + 1);
    strncpy(node->next->score, name, len + 1);
    node->next->next = 0;
    return 1;
}

GradeNode *compute_distribution(const char **mapped_grades, int size)
{
    GradeNode *head = 0;
    head = malloc(sizeof(GradeNode));
    if (!head || !mapped_grades)
    {
        if (mapped_grades)
        {
            for (int i = 0; i < size; i++)
            {
                if (mapped_grades[i])
                    free((void *)mapped_grades[i]);
            }
            free(mapped_grades);
        }
        if (head)
            free(head);
        return NULL;
    }
    GradeNode *buf = head;
    int map[GRADE_SIZE] = {0};
    for (int i = 0; i < size; i++)
    {
        if (strcmp(mapped_grades[i], grades[A_P]) == 0)      { map[A_P]++; }
        else if (strcmp(mapped_grades[i], grades[A]) == 0)   { map[A]++; }
        else if (strcmp(mapped_grades[i], grades[B_P]) == 0) { map[B_P]++; }
        else if (strcmp(mapped_grades[i], grades[B]) == 0)   { map[B]++; }
        else if (strcmp(mapped_grades[i], grades[B_M]) == 0) { map[B_M]++; }
        else if (strcmp(mapped_grades[i], grades[C_P]) == 0) { map[C_P]++; }
        else if (strcmp(mapped_grades[i], grades[C]) == 0)   { map[C]++; }
        else if (strcmp(mapped_grades[i], grades[C_M]) == 0) { map[C_M]++; }
        else if (strcmp(mapped_grades[i], grades[D_P]) == 0) { map[D_P]++; }
        else if (strcmp(mapped_grades[i], grades[D]) == 0)   { map[D]++; }
        else if (strcmp(mapped_grades[i], grades[D_M]) == 0) { map[D_M]++; }
        else if (strcmp(mapped_grades[i], grades[P]) == 0)   { map[P]++; }
        else { map[F]++;}
    }
    for (int i = 0; i < GRADE_SIZE; i++)
    {
        int flag = 0;
        switch (i)
        {
        case A_P: flag = create_node(buf, map[A_P], "A+"); break;
        case A: flag = create_node(buf, map[A], "A"); break;
        case A_M: flag = create_node(buf, map[A_M], "A-"); break;
        case B_P: flag = create_node(buf, map[B_P], "B+"); break;
        case B: flag = create_node(buf, map[B], "B"); break;
        case B_M: flag = create_node(buf, map[B_M], "B-"); break;
        case C_P: flag = create_node(buf, map[C_P], "C+"); break;
        case C: flag = create_node(buf, map[C], "C"); break;
        case C_M: flag = create_node(buf, map[C_M], "C-"); break;
        case D_P: flag = create_node(buf, map[D_P], "D+"); break;
        case D: flag = create_node(buf, map[D], "D"); break;
        case D_M: flag = create_node(buf, map[D_M], "D-"); break;
        case F: flag = create_node(buf, map[F], "F"); break;
        case P: flag = create_node(buf, map[P], "P"); break;

        default:
            break;
        }
        if (flag == 1)
            buf = buf->next;
    }
    buf = head->next;
    free(head);
    head = buf;
    return head;
}

void print_distribution(GradeNode *head)
{
    GradeNode *buf = head;
    while (buf)
    {
        printf("Grade: %s\tCount: %d\n", buf->score, buf->count);
        buf = buf->next;
    }
}

void free_distribution(GradeNode *head)
{
    if (!head)
        return ;
    GradeNode *buf = head;
    GradeNode *buf2 = buf->next;
    while (buf)
    {
        free(buf->score);
        free(buf);
        buf = buf2;
        if (!buf)
            return ;
        buf2 = buf->next;
    }
}

// TO TEST COMPILE WITH gcc -W -W -W -D TEST
#ifdef TEST

int main()
{
    const int scores[6] = {89, 65, 15, 100, 22, 77};
    const char **evaluations = malloc(sizeof(char *) * 6);
    
    // plusminus
    printf("[PLUSMINUS]\n");
    GradeMapper mapper = PLUSMINUS;
    map_scores(scores, 6, mapper, evaluations);
    for (int i = 0; i < 6; i++)
        printf("Score: %d\t Grade: %s\n", scores[i], evaluations[i]);
    printf("\n[PLUSMINUS BONUS]\n");
    GradeNode *head = compute_distribution(evaluations, 6);
    if (!head)
        return 0;
    print_distribution(head);
    free_distribution(head);

    // passfail
    printf("\n[PASSFAIL]\n");
    mapper = PASSFAIL;
    map_scores(scores, 6, mapper, evaluations);
    for (int i = 0; i < 6; i++)
        printf("Score: %d\t Grade: %s\n", scores[i], evaluations[i]);
    printf("\n[PASSFAIL BONUS]\n");
    head = compute_distribution(evaluations, 6);
    if (!head)
        return 0;
    print_distribution(head);
    free_distribution(head);

    // standard
    printf("\n[STANDARD]\n");
    mapper = STANDARD;
    map_scores(scores, 6, mapper, evaluations);
    for (int i = 0; i < 6; i++)
        printf("Score: %d\t Grade: %s\n", scores[i], evaluations[i]);
    printf("\n[STANDARD BONUS]\n");
    head = compute_distribution(evaluations, 6);
    if (!head)
        return 0;
    print_distribution(head);
    free_distribution(head);
    free(evaluations);
}
#endif// !TEST
