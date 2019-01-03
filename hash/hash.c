#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "singly.h"
#include "hash.h"

#define HASH_BUCKET_SIZE (10) // total number of buckets in the hash table
#define MULTIPLIER (37) // prime number to use as a multiplier in our hash function

hash_t*
hash_create(void)
{
    hash_t *hash = malloc(sizeof(hash_t));
    assert(hash);
    hash->buckets = malloc(sizeof(sll_t) * HASH_BUCKET_SIZE);
    assert(hash->buckets);

    for (int i = 0; i < HASH_BUCKET_SIZE; i++)
    {
        hash->buckets[i] = sll_create();
    }

    return hash;
}

static int                                                                                                                                                                                                  
hash_function(const char *key)                                                                                                                                                                                    
{                                                                                                                                                                                                           
    unsigned long int h = 0;                                                                                                                                                                                            
                                                                                                                                                                                                            
    while (*key)                                                                                                                                                                                            
    {                                                                                                                                                                                                       
        h = h * MULTIPLIER + *key++;
    }                                                                                                                                                                                                       
                                                                                                                                                                                                            
    return h % HASH_BUCKET_SIZE;                                                                                                                                                                          
}  

void
hash_insert(hash_t *hash, char *key, char *value)
{
    int h = hash_function(key);
    sll_t *list = hash->buckets[h];
    sll_node_t *node = sll_find(list, key);
    
    if (node == NULL)
    {
        sll_add(list, key, value); // insert value at key
    }
    else
    {
        node->value = value; // update value at key
    }
}

void
hash_delete(hash_t *hash, char *key)
{
    int h = hash_function(key);
    sll_t *list = hash->buckets[h];
    sll_remove(list, key);
}

char*
hash_get(hash_t *hash, char *key)
{
    int h = hash_function(key);
    sll_t *list = hash->buckets[h];
    sll_node_t *node = sll_find(list, key);

    return node ? node->value : NULL;
}

void
hash_destroy(hash_t *hash)
{
    for (int i = 0; i < HASH_BUCKET_SIZE; i++)
    {
        sll_destroy(hash->buckets[i]);
    }
    free(hash->buckets);
    free(hash);
}

void
hash_print(hash_t *hash)
{
    puts("Hash table contents:");
    puts("====================");

    for (int i = 0; i < HASH_BUCKET_SIZE; i++)
    {
        printf("Bucket %02d: ", i + 1);
        sll_print(hash->buckets[i]);
        putchar('\n');
    }
}
