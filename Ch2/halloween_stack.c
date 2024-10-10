#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 255

typedef struct stack{
    struct node* values[SIZE];
    int highest_used;
} stack;

typedef struct node {
    int candy;
    struct node* left;
    struct node* right;
} node;

// stack functions
stack* new_stack(void){
    stack* s = malloc(sizeof(stack));
    if (s == NULL){
        fprintf(stderr, "malloc failure.\n");
        exit(1);
    }
    s->highest_used = -1;

    return s;
}

void push_stack(stack* s, node* value){
    s->highest_used++;
    s->values[s->highest_used] = value;
}

node* pop_stack(stack* s){
    node* ret = s->values[s->highest_used];
    s->highest_used--;

    return ret;
}

int is_empty_stack(stack* s){
    return s->highest_used == -1;
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

// traversing the tree to get the total number of candy
int tree_candy(node* tree){
    int total = 0;
    stack* s = new_stack();
    while (tree != NULL){
        if (tree->left && tree->right){
            push_stack(s, tree->left);
            tree = tree->right;
        } else {
            total = total + tree->candy;
            if (is_empty_stack(s)){
                tree = NULL;
            } else {
                tree = pop_stack(s);
            }
        }
    }
    return total;
}

int main(void){
    // build the example tree
    node* four = new_house(4);
    node* nine = new_house(9);
    node* B = new_nonhouse(four, nine);
    node* fifteen = new_house(15);
    node* C = new_nonhouse(B, fifteen);
    node* two = new_house(2);
    node* D = new_nonhouse(C, two);
    node* seventytwo = new_house(72);
    node* three = new_house(3);
    node* six = new_house(6);
    node* E = new_nonhouse(six, D);
    node* A = new_nonhouse(seventytwo, three);
    node* F = new_nonhouse(A, E);
    node* seven = new_house(7);
    node* fortyone = new_house(41);
    node* G = new_nonhouse(seven, fortyone);
    node* H = new_nonhouse(F, G);

    return 0;
}
