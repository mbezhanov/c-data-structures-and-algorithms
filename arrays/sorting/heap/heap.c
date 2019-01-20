#include "heap.h"
#include "swap.h"

static void
push_down(int *arr, int len, int parent)
{
    int left_child = parent * 2 + 1;  // index, where left child is
    int right_child = parent * 2 + 2; // index, where right child is
    int greater_child;

    if (left_child >= len)
    {
        return; // parent has no children
    }

    if (right_child < len && arr[right_child] > arr[left_child])
    {
        greater_child = right_child;
    }
    else
    {
        greater_child = left_child;
    }

    if (arr[greater_child] > arr[parent])
    {
        swap(&arr[parent], &arr[greater_child]);
        push_down(arr, len, greater_child); // ensure max-heap properties were not violated after the swap
    }
}

static void
build_max_heap(int *arr, int len)
{
    for (int parent = (len - 1) / 2; parent >= 0; parent--)
    {
        push_down(arr, len, parent);
    }
}

void
heap_sort(int *arr, int len)
{
    build_max_heap(arr, len);

    for (int i = len - 1; i > 0; i--)
    {
        swap(&arr[0], &arr[i]);
        push_down(arr, i, 0);
    }
}
