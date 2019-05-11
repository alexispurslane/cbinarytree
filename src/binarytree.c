#include <stdio.h>
#include "binarytree.h"

BinaryTree_t *new_tree(size_t len, comparator_t comp, equalizer_t equal) {
    BinaryTree_t *node = malloc(sizeof(BinaryTree_t));
    node->comparason = comp;
    node->equal = equal;
    node->data_len = len;
    node->root = NULL;
    return node;
}

BNode_t *find_node(BNode_t *root, void *data, comparator_t comp, equalizer_t equal) {
    if ((*equal)(root->data, data))
        return root;
    if ((*comp)(root->data, data)) {
        if (root->left != NULL)
            return find_node(root->left, data, comp, equal);
    } else {
        if (root->right != NULL)
            return find_node(root->right, data, comp, equal);
    }
    return NULL;
}

BNode_t *find(BinaryTree_t *tree, void *data) {
    return find_node(tree->root, data, tree->comparason, tree->equal);
}

void insert_node(BNode_t *root, BNode_t *node, comparator_t comp) {
    if ((*comp)(root->data, node->data)) {
        if (root->left == NULL) {
            root->left = node;
            node->parent = root;
        } else {
            insert_node(root->left, node, comp);
        }
    } else {
        if (root->right == NULL) {
            root->right = node;
            node->parent = root;
        } else {
            insert_node(root->right, node, comp);
        }
    }
}
void insert(BinaryTree_t *tree, void *data) {
    BNode_t *node = malloc(sizeof(BNode_t));
    node->data = malloc(tree->data_len);
    memcpy(node->data, data, tree->data_len);
    node->left = NULL;
    node->right = NULL;

    if (tree->root == NULL)
        tree->root = node;
    else
        insert_node(tree->root, node, tree->comparason);
}

void delete(BinaryTree_t *tree, BNode_t *node) {
    if (node == node->parent->left) {
        if (node->left != NULL && node->right == NULL) 
            node->parent->left = node->left;
        else if (node->left == NULL && node->right != NULL) 
            node->parent->left = node->right;
        else {
            printf("WARNING: Deleted node either has no children or 2 children. This means that neither child can be selected for reintroduction to tree.\n");
            node->parent->left = NULL;
        }
    } else {
        if (node->left != NULL && node->right == NULL) 
            node->parent->right = node->left;
        else if (node->left == NULL && node->right != NULL) 
            node->parent->right = node->right;
        else {
            printf("WARNING: Deleted node either has no children or 2 children. This means that neither child can be selected for reintroduction to tree.\n");
            node->parent->right = NULL;
        }
    }
    if (node->parent->right || node->parent->left) {
        free(node->data);
        free(node);
    } else {
        free_node(node);
    }
}

void replace(BinaryTree_t *tree, BNode_t *node1, BNode_t *node2) {
    delete(tree, node1);
    insert(tree, node2);
    free_node(node1);
}

void free_tree(BinaryTree_t *tree) {
    free_node(tree->root);
    free(tree);
}

void free_node(BNode_t *node) {
    free(node->data);
    if (node->left != NULL)
        free_node(node->left);
    if (node->right != NULL)
        free_node(node->right);
    free(node);
}
