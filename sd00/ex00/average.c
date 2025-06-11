#include "average.h"

float average(const int *arr, int size)
{
    size_t  n_size = 0;
    size_t  sum = 0;
    for (size_t i = 0; i < size; i++)
    {
        if (arr[i] < 0 || arr[i] > 100)
            continue;
        sum += arr[i];
        n_size++;
    }
    // if (n_size == 0)
    //     return (-1.f); // error value
    return ((float)sum / n_size);
}

// int main()
// {
//     int arr[] = {};
//     printf("%f\n", average(arr, 0));
// }