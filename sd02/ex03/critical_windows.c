#include "critical_windows.h"

float average(const int *arr, int size)
{
    int  n_size = 0;
    int  sum = 0;
    for (int i = 0; i < size; i++)
    {
        sum += arr[i];
        n_size++;
    }
    return ((float)sum / n_size);
}
int check_upper_bound(const int* readings, int *i, int step)
{
    if (readings[*(i) + step] > 150)
    {
        *i += step;
        return (0);
    }
    return (1);
}
int check_over(int value)
{
    return (value >= 70);
}
int check_window(const int* readings, int window_size, int *i)
{
    int count = 0;
    int start = *i;
    for (int j = 0; j < window_size; j++)
    {
        if (check_upper_bound(readings, i, j) == 0) return ((int)safe);
        count += check_over(readings[start + j]);
    }
    float avg = average((readings + start), window_size);
    if ( avg >= 90.f && count >= 3)
        return ((int)critical);
    return (0);
}
int count_critical_windows(const int *readings, int size)
{
    int count = 0;
    int i = 0;

    for (;(i + WINDOW_SIZE) < size; i++)
    {
        count += check_window(readings, WINDOW_SIZE, &i);
    }

    return (count);
}

// int main()
// {
//     const int arr[] = {90, 90, 120, 90, 90, 110, 155, 70, 70, 70, 70};
//     printf("count %d\n", count_critical_windows(arr, 11));
// }