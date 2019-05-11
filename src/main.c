#include <stdio.h>
#include "binarytree.h"

void print_tree(BNode_t *root, int spc, void (*printer)(void *data)) {
    if (root == NULL)
        return;
    print_tree(root->left, spc + 4, printer);

    printf("%*c", spc, ' ');
    printer(root->data);
    printf("\n");

    print_tree(root->right, spc + 4, printer);
}

bool int_comp(void *root, void *node) {
    return *((int*) node) < *((int*) root);
}

void int_printer(void *data) {
    printf("%d", *((int*) data));
}

bool int_equal(void *root, void *node) {
    return *((int*) node) == *((int*) root);
}

int main () {
    BinaryTree_t *tree = new_tree(sizeof(int), &int_comp, &int_equal);
    int data[] = { 1, 2, 6, 8, 12, 9, 10, 11, 5, 13, 4, 3 };
    for (size_t i = 0; i < (sizeof(data) / sizeof(int)); i++) {
        insert(tree, &data[i]);
    }
    printf("Initial tree:\n");
    print_tree(tree->root, 0, &int_printer);

    int goals[] = { 4, 10, 12 };
    for (size_t i = 0; i < (sizeof(goals) / sizeof(int)); i++) {
        BNode_t *node = find(tree, &goals[i]);
        printf("Found node: %d\n", *((int *) node->data));
        print_tree(node, 0, &int_printer);

        printf("Delete node: %d\n", *((int *) node->data));
        delete(tree, node);
        print_tree(tree->root, 0, &int_printer);
    }

    int ndata = 99;
    printf("Add node: %d\n", ndata);
    insert(tree, &ndata);
    print_tree(tree->root, 0, &int_printer);

    free_tree(tree);
    return 0;
}
