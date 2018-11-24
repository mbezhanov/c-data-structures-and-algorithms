# Bubble Sort

Bubble Sort is an iterative comparison-based sorting algorithm with an average complexity of O(n<sup>2</sup>), and a best-case complexity of O(n), achieved when the array passed to the algorithm is already sorted. Bubble Sort is considered to be the simplest and least performant array sorting algorithm. It gets its name from the way larger values are gradually pushed (bubble up) to the end of the array.

## Implementation

Starting from the very first element in the array:

1. Compare the values of the current element and the next element.
2. Swap the values, if the current element's value is greater.
3. Move to the next element.
4. Repeat steps 1 to 3 until the end of the array is reached.
5. Decrease the range of values left for sorting.
6. Repeat steps 1 to 5 until either no swaps have occurred or there are no values left for sorting.

![Bubble Sort](https://raw.githubusercontent.com/mbezhanov/c-data-structures-and-algorithms/master/arrays/sorting/bubble/images/bubblesort.png)
