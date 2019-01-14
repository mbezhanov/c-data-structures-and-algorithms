#ifndef LIS_H
#define LIS_H

typedef struct lis_s {
    int *arr;
    int len;
} lis_t;

lis_t* longest_increasing_subsequence(int *arr, int len);

#endif // LIS_H
