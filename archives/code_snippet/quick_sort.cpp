#include <iostream>

int Partition(int unsorted[], int low, int high)
{
    int pivot = unsorted[low];
    while (low < high)
    {
        while (low < high && unsorted[high] > pivot) high--;
        unsorted[low] = unsorted[high];
        while (low < high && unsorted[low] <= pivot) low++;
        unsorted[high] = unsorted[low];
    }
    unsorted[low] = pivot;
    return low;
}

void QuickSort(int unsorted[], int low, int high)
{
    int loc = 0;
    if (low < high)
    {
        loc = Partition(unsorted, low, high);
        QuickSort(unsorted, low, loc - 1);
        QuickSort(unsorted, loc + 1, high);
    }
}

int main()
{
    int x[] = { 6, 21, 4, 13, 51, 9, 21 };
    int len = sizeof(x) / sizeof(int);
    QuickSort(x, 0, len - 1);

    for each (int i in x)
    {
        std::cout << i << " ";
    }
    
    return 0;
}