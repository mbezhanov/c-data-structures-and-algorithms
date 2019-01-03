#ifndef TREAP_H
#define TREAP_H

typedef struct treap_node_s treap_node_t;
typedef struct treap_s treap_t;

struct treap_node_s {
    int value;
    int priority;
    treap_node_t *link[2]; // pointers to left child and right child
};

struct treap_s {
    treap_node_t *root;
};

// core functions
treap_t *treap_create(void);
void treap_insert(treap_t *tree, int value);
void treap_delete(treap_t *tree, int value);
treap_node_t *treap_search(treap_t *tree, int value);
void treap_destroy(treap_t *tree);

// helper functions
int treap_assert_valid(treap_t *tree);
void treap_print(treap_t *tree);

#endif // TREAP_H
