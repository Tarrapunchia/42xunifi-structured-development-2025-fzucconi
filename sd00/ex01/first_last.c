#include "first_last.h"

void first_last(int arr[], int size, int target, int *first, int *last)
{
    *first = *last = -1;
    
    for (size_t i = 0; i < size; i++)
    {
        if (arr[i] == target)
        {
            if (*first == -1)
                *first = *last = i;
            else
                *last = i;
        }
    }
}

// int main()
// {
//     int arr[] = {0, 1, 2, 3, 4, 7, 5, 6, 7, 8, 9};
//     int first, last;
//     first_last(arr, 11, 4, &first, &last);
//     printf("f %d\tl %d\n", first, last);
//     first_last(arr, 11, 7, &first, &last);
//     printf("f %d\tl %d\n", first, last);
//     first_last(arr, 11, 12, &first, &last);
//     printf("f %d\tl %d\n", first, last);
//     return 0;
// }