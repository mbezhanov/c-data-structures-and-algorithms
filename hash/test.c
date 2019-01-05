#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "hash.h"
#include "singly.h"

static void test_insertion(hash_t *hash);
static void test_updating(hash_t *hash);
static void test_deletion(hash_t *hash);

int
main(int argc, char **argv)
{
    hash_t *hash = hash_create();

    test_insertion(hash);
    test_updating(hash);
    test_deletion(hash);
    
    hash_destroy(hash);
}

static int
bucket_size(hash_t *hash, int bucket)
{
    int count = 0;
    
    for (sll_node_t *tmp = hash->buckets[bucket]->head; tmp != NULL; tmp = tmp->next, count++);

    return count;
}

static void
test_insertion(hash_t *hash)
{
    printf("Testing insertion... ");
    
    int i, actual_size;
    int total_items = 10;
    char *keys[] = {"lorem", "ipsum", "dolor", "sit", "amet", "incididunt", "labore", "dolore", "magna", "aliqua"};
    char *values[] = {"consectetur", "adipiscing", "elit", "eiusmod", "tempor", "enim", "minim", "veniam", "quis", "nostrud"};
    int expected_bucket_sizes[] = {0, 1, 0, 2, 2, 3, 2, 0, 0, 0};

    for (i = 0; i < total_items; i++)
    {
        hash_insert(hash, keys[i], values[i]);
    }

    for (i = 0; i < total_items; i++)
    {
        actual_size = bucket_size(hash, i);

        if (expected_bucket_sizes[i] != actual_size)
        {
            printf(" FAIL!\nExpected bucket %i to have a size of %i, got %i instead.\n", i, expected_bucket_sizes[i], actual_size);
            return;
        }
    }
    puts("SUCCESS");
}

static void
test_updating(hash_t *hash)
{
    printf("Testing updating... ");

    char *keys[] = {"incididunt", "dolore", "ipsum", "labore"};
    char *old_values[] = {"enim", "veniam", "adipiscing", "minim"};
    char *new_values[] = {"minim", "quis", "veniam", "enim"};
    char *value;

    for (int i = 0; i < 4; i++)
    {
        value = hash_get(hash, keys[i]);

        if (value != old_values[i])
        {
            printf("FAIL!\nExpected old value at key \"%s\" to be \"%s\", but got \"%s\" instead.\n", keys[i], old_values[i], value);
            return;
        }
        hash_insert(hash, keys[i], new_values[i]);
        value = hash_get(hash, keys[i]);

        if (value != new_values[i])
        {
            printf("FAIL!\nExpected new value at key \"%s\" to be \"%s\", but got \"%s\" instead.\n", keys[i], new_values[i], value);
            return;
        }
    }
    puts("SUCCESS");
}

static void
test_deletion(hash_t *hash)
{
    printf("Testing deletion... ");

    int i, actual_size;
    char *keys[] = {"incididunt", "dolore", "ipsum", "labore"};
    int expected_bucket_sizes[] = {0, 0, 0, 1, 1, 2, 2, 0, 0, 0};

    for (i = 0; i < 4; i++)
    {
        if (hash_get(hash, keys[i]) == NULL)
        {
            printf("FAIL!\nKey \"%s\" does not exist in the hash table.\n", keys[i]);
            return;
        }
        hash_delete(hash, keys[i]);

        if (hash_get(hash, keys[i]) != NULL)
        {
            printf("FAIL!\nKey \"%s\" is still present in the hash table.\n", keys[i]);
            return;
        }
    }

    for (i = 0; i < 10; i++)
    {
        actual_size = bucket_size(hash, i);

        if (expected_bucket_sizes[i] != actual_size)
        {
            printf(" FAIL!\nExpected bucket %i to have a size of %i, got %i instead.\n", i, expected_bucket_sizes[i], actual_size);
            return;
        }
    }
    puts("SUCCESS");
}
