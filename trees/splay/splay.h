#ifndef SPLAY_H
#define SPLAY_H

typedef struct st_node_s st_node_t;
typedef struct st_s st_t;

struct st_node_s {
    int value;
    st_node_t *link[2]; // pointers to left child and right child
};

struct st_s {
    st_node_t *root;
};

// core functions
st_t *st_create();
void st_insert(st_t *tree, int value);
void st_delete(st_t *tree, int value);
st_node_t *st_search(st_t *tree, int value);
void st_destroy(st_t *tree);

// helper functions
void st_print(st_t *tree);

#endif // SPLAY_H
