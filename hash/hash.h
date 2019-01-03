#ifndef HASH_H
#define HASH_H

#include "singly.h"

typedef struct hash_s hash_t;

struct hash_s {
   sll_t **buckets;
};

// core functions
hash_t* hash_create(void);
void hash_insert(hash_t *hash, char *key, char *value);
void hash_delete(hash_t *hash, char *key);
char* hash_get(hash_t *hash, char *key);
void hash_destroy(hash_t *hash);

// helper functons
void hash_print(hash_t *hash);

#endif // HASH_H
