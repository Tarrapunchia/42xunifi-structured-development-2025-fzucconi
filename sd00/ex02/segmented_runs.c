#include "segmented_runs.h"

void check_sequential(const int *arr, t_bool *flag, int *len, int *count, int delim, int seq_len, size_t *i)
{
    seq_len--;
    if (arr[*i] == delim)
    {
        *flag = FALSE;
        *len = 0;
        (*i)++;
        return;
    }

    // se ho gia' trovato il sottosegmento come incrementale
    if (*flag == TRUE)
        return;

    if (arr[*i - 1] == (arr[*i] - 1))
        (*len)++;
    else
        *len = 0;

    if (*len >= seq_len)
    {
        (*count)++;
        *flag = TRUE;
    }
}

int count_segments(const int *arr, int size)
{
    int count, len = 0;
    t_bool flag = FALSE;
    
    size_t i = 0;
    // elimino tutti i delimitatori iniziali
    while (arr[i] == -1)
        i++;
    // faccio partire il ciclo dal secondo valore utile,
    // controllando al contempo se esso esiste
    if ((i + 1) >= size)
        return (count);
    i++;
    for (; i < size; i++)
    {
        check_sequential(
            arr,
            &flag,
            &len,
            &count,
            -1,
            3,
            &i
        );
    }
    return (count);
}

// int main()
// {
//     const int arr[] = {-1, -1, -1,2,3,4,-1,5,6,-1,1,2,3,4};
//     printf("count %d\n", count_segments(arr, 14));
// }