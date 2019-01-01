#ifndef BST_H
#define BST_H

typedef struct bst_node_s bst_node_t;
typedef struct bst_s bst_t;

struct bst_node_s {
    int value;
    bst_node_t *link[2];
};

struct bst_s {
    bst_node_t *root;
};

// core functions
bst_t* bst_create();
void bst_insert(bst_t *tree, int value);
void bst_delete(bst_t *tree, int value);
bst_node_t* bst_search(bst_t *tree, int value);
void bst_destroy();

// helper functions
int bst_assert_valid(bst_t *tree);
void bst_print(bst_t *tree);

#endif // BST_H
