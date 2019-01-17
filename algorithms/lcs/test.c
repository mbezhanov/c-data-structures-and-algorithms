#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "lcs.h"

static void
print_usage_details(const char *command)
{
    fprintf(stderr, "Usage: %s [arguments]\n\n", command);
    fprintf(stderr, "Arguments:\n");
    fprintf(stderr, "  str1  First string.\n");
    fprintf(stderr, "  str2  Second string.\n");
}

static int
validate_arguments(int argc, char **argv)
{
    if (argc < 3)
    {
        print_usage_details(argv[0]);
        return 0; // "0" = false
    }
    return 1; // "1" = true
}

int
main(int argc, char **argv)
{
    if (!validate_arguments(argc, argv))
    {
        return 1;
    }
    char *str1 = argv[1];
    char *str2 = argv[2];

    lcs_t *lcs = longest_common_subsequence(str1, str2);

    print_solutions_table(lcs, str1, str2);
    printf("\nThe longest common subsequence of \"%s\" and \"%s\" is \"%s\" (length: %i characters)\n", str1, str2, lcs->str, lcs->len);
    free(lcs->arr);
    free(lcs->str);
    free(lcs);

    return 0;
}
