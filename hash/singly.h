#ifndef SINGLY_H
#define SINGLY_H

typedef struct sll_node_s sll_node_t;
typedef struct sll_s sll_t;

struct sll_node_s {
    char *key;
    char *value;
    sll_node_t *next;
};

struct sll_s {
    sll_node_t *head;
};

// core functions
sll_t* sll_create(void);
void sll_add(sll_t *list, char *key, char *value);
void sll_remove(sll_t *list, char *key);
sll_node_t* sll_find(sll_t *list, char *key);
void sll_destroy(sll_t *list);

// helper functions
void sll_print(sll_t *list);

#endif // SINGLY_H
