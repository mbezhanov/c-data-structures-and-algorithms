#ifndef AVL_H
#define AVL_H

typedef struct avl_node_s avl_node_t;
typedef struct avl_s avl_t;

struct avl_node_s {
    int value;
    int height; // height of the subtree rooted at this node
    avl_node_t *link[2]; // pointers to left child and right child
};

struct avl_s {
    avl_node_t *root;
};

// core functions
avl_t* avl_create();
void avl_insert(avl_t *tree, int value);
void avl_delete(avl_t *tree, int value);
avl_node_t *avl_search(avl_t *tree, int value);
void avl_destroy(avl_t *tree);

// helper functions
int avl_assert_valid(avl_t *tree);
void avl_print(avl_t *tree);

#endif // AVL_H
