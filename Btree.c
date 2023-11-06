#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define t 2

struct BTreeNode {
    int n;
    char keys[2 * t - 1];
    struct BTreeNode* children[2 * t];
    int leaf;
};

struct BTreeNode* createNode() {
    struct BTreeNode* newNode = (struct BTreeNode*)malloc(sizeof(struct BTreeNode));
    newNode->n = 0;
    newNode->leaf = 1;
    return newNode;
}

void splitChild(struct BTreeNode* x, int i) {
    struct BTreeNode* y = x->children[i];
    struct BTreeNode* z = createNode();
    x->children[i] = y;
    x->n = x->n + 1;
    for (int j = x->n - 1; j >= i + 1; j--) {
        x->children[j + 1] = x->children[j];
        x->keys[j] = x->keys[j - 1];
    }
    x->children[i + 1] = z;
    for (int j = y->n - 1; j >= 0; j--) {
        z->keys[j] = y->keys[j + t];
        z->n = z->n + 1;
        y->n = y->n - 1;
    }
}

void insertNonFull(struct BTreeNode* x, char k) {
    int i = x->n - 1;
    if (x->leaf) {
        while (i >= 0 && k < x->keys[i]) {
            x->keys[i + 1] = x->keys[i];
            i--;
        }
        x->keys[i + 1] = k;
        x->n = x->n + 1;
    } else {
        while (i >= 0 && k < x->keys[i]) {
            i--;
        }
        i++;
        if (x->children[i]->n == 2 * t - 1) {
            splitChild(x, i);
            if (k > x->keys[i])
                i++;
        }
        insertNonFull(x->children[i], k);
    }
}

struct BTreeNode* insert(struct BTreeNode* root, char k) {
    if (root->n == 2 * t - 1) {
        struct BTreeNode* s = createNode();
        s->children[0] = root;
        splitChild(s, 0);
        insertNonFull(s, k);
        return s;
    } else {
        insertNonFull(root, k);
        return root;
    }
}

void inOrder(struct BTreeNode* root) {
    if (root != NULL) {
        int i;
        for (i = 0; i < root->n; i++) {
            inOrder(root->children[i]);
            printf("%c ", root->keys[i]);
        }
        inOrder(root->children[i]);
    }
}

int main() {
    struct BTreeNode* root = createNode();
    char keys[] = {'F', 'S', 'Q', 'K', 'C', 'L', 'H', 'T', 'V', 'W', 'M', 'R', 'N', 'P', 'A', 'B', 'X', 'Y', 'D', 'Z', 'E'};
    int numKeys = sizeof(keys) / sizeof(keys[0]);

    for (int i = 0; i < numKeys; i++) {
        root = insert(root, keys[i]);
    }

    printf("In-order traversal of the B-tree: ");
    inOrder(root);
    printf("\n");
    
    return 0;
}
