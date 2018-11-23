# Heapsort

Heapsort is an iterative comparison-based sorting algorithm with an average complexity of O(n log n)

## Implementation

1. Turn the array into a max heap.
2. Swap the first value with the last value in the range of values left for sorting.
3. Decrease the range of values left for sorting.
4. Restore the max heap properties of the remaining range.
5. Repeat steps 2 to 4 until the array is sorted.

![Heapsort](https://raw.githubusercontent.com/mbezhanov/c-data-structures-and-algorithms/master/arrays/sorting/heap/images/heapsort-1.png)

## Max Heap

Arrays can be used to represent binary trees.

Given a position ***p***, the children of each element are located at the following positions:

    left = p * 2 + 1
    right = p * 2 + 2

Thus, the array from the example above can be represented as a binary tree in the following way:

![Binary Tree](https://raw.githubusercontent.com/mbezhanov/c-data-structures-and-algorithms/master/arrays/sorting/heap/images/heapsort-2.png)

To turn that array into a max heap, we ensure the max heap property is not violated, starting from the last parent (in this case: the element at position 2) all the way up to the tree root (the element at position 0)

![Max Heap](https://raw.githubusercontent.com/mbezhanov/c-data-structures-and-algorithms/master/arrays/sorting/heap/images/heapsort-3.png)
