#include "grade_mapping.h"

void PlusMinus(const int *scores, const char **mapped_grades, unsigned int size)
{

    for (unsigned int i = 0; i < size; i++)
    {
        if (scores[i] > 96) { *(mapped_grades + i) = grades[A_P];}
        else if (scores[i] < 97 && scores[i] > 92) { *(mapped_grades + i) = grades[A];   }
        else if (scores[i] > 89 && scores[i] < 93) { *(mapped_grades + i) = grades[A_M]; }
        else if (scores[i] > 86 && scores[i] < 90) { *(mapped_grades + i) = grades[B_P]; }
        else if (scores[i] < 87 && scores[i] > 82) { *(mapped_grades + i) = grades[B];   }
        else if (scores[i] > 79 && scores[i] < 83) { *(mapped_grades + i) = grades[B_M]; }
        else if (scores[i] > 76 && scores[i] < 80) { *(mapped_grades + i) = grades[C_P]; }
        else if (scores[i] < 77 && scores[i] > 72) { *(mapped_grades + i) = grades[C];   }
        else if (scores[i] > 69 && scores[i] < 73) { *(mapped_grades + i) = grades[C_M]; }
        else if (scores[i] > 66 && scores[i] < 70) { *(mapped_grades + i) = grades[D_P]; }
        else if (scores[i] < 67 && scores[i] > 62) { *(mapped_grades + i) = grades[D];   }
        else if (scores[i] > 59 && scores[i] < 63) { *(mapped_grades + i) = grades[D_M]; }
        else { *(mapped_grades + i) = grades[F];}
    }
}
void PassFail(const int *scores, const char **mapped_grades, unsigned int size)
{
    for (unsigned int i = 0; i < size; i++)
    {
        if (scores[i] > 59) { mapped_grades[i] = grades[P]; }
        else { mapped_grades[i] = grades[F]; }
    }
    
}
void Standard(const int *scores, const char **mapped_grades, unsigned int size)
{
    for (unsigned int i = 0; i < size && mapped_grades[i]; i++)
    {
        if (scores[i] > 89)                         { mapped_grades[i] = grades[A];  }
        else if (scores[i] > 79 && scores[i] < 90)  { mapped_grades[i] = grades[B];  }
        else if (scores[i] < 80 && scores[i] > 69)  { mapped_grades[i] = grades[C];  }
        else if (scores[i] < 70 && scores[i] > 59)  { mapped_grades[i] = grades[D];  }
        else { mapped_grades[i] = grades[F];}
    }
}

void map_scores(const int *scores, int size, GradeMapper mapper, const char **mapped_grades)
{
    if (!scores || !mapped_grades)
        return ;
    switch (mapper)
    {
    case PLUSMINUS: PlusMinus(scores, mapped_grades, size); break;
    case PASSFAIL: PassFail(scores, mapped_grades, size); break;
    case STANDARD: Standard(scores, mapped_grades, size); break;
    default:
        break;
    }
}

// TO TEST COMPILE WITH gcc -W -W -W -D DEBUG
#ifdef DEBUG

int main()
{
    const int scores[6] = {89, 65, 15, 100, 22, 77};
    const char **grades = malloc(sizeof(char *) * 6);
    
    // plusminus
    printf("[PLUSMINUS]\n");
    GradeMapper mapper = PLUSMINUS;
    map_scores(scores, 6, mapper, grades);
    for (int i = 0; i < 6; i++)
        printf("Score: %d\t Grade: %s\n", scores[i], grades[i]);

    // passfail
    printf("\n[PASSFAIL]\n");
    mapper = PASSFAIL;
    map_scores(scores, 6, mapper, grades);
    for (int i = 0; i < 6; i++)
        printf("Score: %d\t Grade: %s\n", scores[i], grades[i]);

    // standard
    printf("\n[STANDARD]\n");
    mapper = STANDARD;
    map_scores(scores, 6, mapper, grades);
    for (int i = 0; i < 6; i++)
        printf("Score: %d\t Grade: %s\n", scores[i], grades[i]);
}
#endif // DEBUG