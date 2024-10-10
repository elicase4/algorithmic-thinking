#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 255
#define TEST_CASES 5

typedef struct node {
    int candy;
    struct node* left;
    struct node* right;
} node;

int max(int v1, int v2){
    if (v1 > v2){
        return v1;
    } else{
        return v2;
    }
}

// tree building functions
node* new_house(int candy){
    node* house = malloc(sizeof(node));
    if (house == NULL){
        fprintf(stderr, "malloc failure.\n");
        exit(1);
    }
    house->candy = candy;
    house->left = NULL;
    house->right = NULL;

    return house;
}

node* new_nonhouse(node* left, node* right){
    node* nonhouse = malloc(sizeof(node));
    if (nonhouse == NULL){
        fprintf(stderr, "malloc failure.\n");
        exit(1);
    }
    nonhouse->left = left;
    nonhouse->right = right;

    return nonhouse;
}

// read an input tree
node* read_tree_helper(char* line, int* pos){
    node* tree = malloc(sizeof(node));
    if (tree == NULL){
        fprintf(stderr, "malloc failure.\n");
        exit(1);
    }
    if (line[*pos] == '('){
        (*pos)++;
        tree->left = read_tree_helper(line, pos);
        (*pos)++;
        tree->right = read_tree_helper(line, pos);
        (*pos)++;
        return tree;
    } else{
        tree->left = NULL;
        tree->right = NULL;
        tree->candy = line[*pos] - '0';
        (*pos)++;
        if (line[*pos] != ')' && line[*pos] != ' ' && line[*pos] != '\0'){
            tree->candy = tree->candy * 10 + line[*pos] - '0';
            (*pos)++;
        }
        return tree;
    }
}

node* read_tree(char* line){
    int pos = 0;
    return read_tree_helper(line, &pos);
}

// traversing the tree to get the total number of candy
int tree_candy(node* tree){
    if (!tree->left && !tree->right){
        return tree->candy;
    }
    return tree_candy(tree->left) + tree_candy(tree->right);
}

// count the number of nodes in the tree
int tree_nodes(node* tree){
    if (!tree->left && !tree->right){
        return 1;
    }
    return 1 + tree_nodes(tree->left) + tree_nodes(tree->right);
}

// count the number of leaves in the tree
int tree_leaves(node* tree){
    if (!tree->left && !tree->right){
        return 1;
    }
    return tree_leaves(tree->left) + tree_leaves(tree->right);
}

// count the number of edges in the tree to do a complete traversal and return to the root
int tree_streets(node* tree){
    if (!tree->left && !tree->right){
        return 0;
    }
    return tree_streets(tree->left) + tree_streets(tree->right) + 4;
}

// compute the height of the tree
int tree_height(node* tree){
    if (!tree->left && !tree->right){
        return 0;
    }
    return 1 + max(tree_height(tree->left), tree_height(tree->right));
}

void tree_solve(node* tree){
    int candy = tree_candy(tree);
    int height = tree_height(tree);
    int num_streets = tree_streets(tree) - height;
    printf("%d %d\n", num_streets, candy);
}

int main(void){
    char line[SIZE + 1];
    node* tree;
    int buff_size = SIZE + 1;
    for (int i = 0; i < TEST_CASES; i++){
        fgets(line, buff_size, stdin);
        tree = read_tree(line);
        tree_solve(tree);
    }
    
    return 0;
}
