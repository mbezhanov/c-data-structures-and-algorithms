#ifndef LCS_H
#define LCS_H

typedef struct lcs_s {
    char *str; // a string representing the longest common subsequence
    int len;   // length of the longest common subsequence
    int *arr;  // table of solutions
} lcs_t;

lcs_t* longest_common_subsequence(char *str1, char *str2);
void print_solutions_table(lcs_t *lcs, char *str1, char *str2);

#endif // LCS_H
