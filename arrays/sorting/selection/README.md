# Selection Sort

Selection Sort is an iterative comparison-based sorting algorithm with an average complexity of O(n<sup>2</sup>). The algorithm works by repeatedly selecting the smallest unsorted value, and swapping it with the value of the leftmost unsorted element.

## Implementation

Starting from the very first element in the array:

1. Iterate over all remaining elements and find the minimum value.
2. If the minimum value is smaller than the value of the current element - swap them.
3. Move to the next element.
4. Repeat steps 1 to 3 until there are no more elements left in the array.

![Selection Sort](https://raw.githubusercontent.com/mbezhanov/c-data-structures-and-algorithms/master/arrays/sorting/selection/images/selectionsort.png)
