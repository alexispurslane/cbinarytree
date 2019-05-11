#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

// return true if node is less than root
typedef bool (*comparator_t)(void *root, void *node);
typedef bool (*equalizer_t)(void *root, void *node);

typedef struct BNode {
    void *data;
    struct BNode *left, *right, *parent;
} BNode_t;

typedef struct BinaryTree {
    BNode_t *root;
    comparator_t comparason;
    equalizer_t equal;
    size_t data_len;
} BinaryTree_t;

BinaryTree_t *new_tree(size_t len, comparator_t comp, equalizer_t equal);

BNode_t *find(BinaryTree_t *tree, void *data);

void insert(BinaryTree_t *tree, void *data);
void delete(BinaryTree_t *tree, BNode_t *node);
void replace(BinaryTree_t *tree, BNode_t *node1, BNode_t *node2);

void free_tree(BinaryTree_t *tree);
void free_node(BNode_t *node);
