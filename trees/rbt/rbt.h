#ifndef RBT_H
#define RBT_H

typedef struct rbt_node_s rbt_node_t;
typedef struct rbt_s rbt_t;

struct rbt_node_s {
    int value;
    unsigned char color;
    rbt_node_t *link[2]; // pointers to left child and right child
};

struct rbt_s {
    rbt_node_t *root;
};

// core functions
rbt_t *rbt_create();
void rbt_insert(rbt_t *tree, int value);
void rbt_delete(rbt_t *tree, int value);
rbt_node_t *rbt_search(rbt_t *tree, int value);
void rbt_destroy();

// helper functions
int rbt_assert_valid(rbt_t *tree);
void rbt_print(rbt_t *tree);

#endif // RBT_H
