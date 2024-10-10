#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 100000

typedef struct snowflake_node{
    int snowflake[6]; //have to specify the array size as a field in the struct
    struct snowflake_node* next;
} snowflake_node;

int identical_right(int* snow1, int* snow2, int start){
    for (int offset = 0; offset < 6; offset++){
        if (snow1[offset] != snow2[(start + offset) % 6]){
            return 0;
        }
    }
    return 1;
}

int identical_left(int* snow1, int* snow2, int start){
    int snow2_index;
    for (int offset = 0; offset < 6; offset++){
        snow2_index = start - offset;
        if (snow2_index < 0){
            snow2_index += 6;
        }
        if (snow1[offset] != snow2[snow2_index]){
            return 0;
        }
    }
    return 1;
}

int are_identical(int* snow1, int* snow2){
    for (int start = 0; start < 6; start++){
        if (identical_right(snow1, snow2, start)) {
            return 1;
        }
        if (identical_left(snow1, snow2, start)) {
            return 1;
        }
    }
    return 0;
}

void identify_identical(snowflake_node** snowflakes){
    for (int i = 0; i < SIZE; i++){
        snowflake_node* node1 = snowflakes[i]; 
        while (node1 != NULL){
            snowflake_node* node2 = node1->next;
            while (node2 != NULL){
                if (are_identical(node1->snowflake, node2->snowflake)){
                    printf("Twin snowflakes found.\n");
                    return;
                }
                node2 = node2->next;
            }
            node1 = node1->next;
        }
    }
    printf("No two snowflakes are alike.\n");
}

int code(int* snowflake){
    int sum = 0;
    for (int i = 0; i < 6; i++){
        sum += snowflake[i];
    }
    return sum % SIZE;
}

void free_snowflakes(snowflake_node** snowflakes){
    for (int i = 0; i < SIZE; i++){
        snowflake_node* curr_node = snowflakes[i];
        while (curr_node != NULL){
            snowflake_node* tmp_node = curr_node;
            curr_node = curr_node->next;
            free(tmp_node); 
        }
    }
}

int main(void){
    static snowflake_node* snowflakes[SIZE] = {NULL};
    int n;
    scanf("%d", &n);
    for (int i = 0; i < n; i++){
        snowflake_node* snow = malloc(sizeof(snowflake_node));
        if (snow == NULL){
            fprintf(stderr, "malloc error\n");
            exit(1);
        }
        for(int j = 0; j < 6; j++){
            scanf("%d", &snow->snowflake[j]);
        }
        int snowflake_code = code(snow->snowflake);
        snow->next = snowflakes[snowflake_code];
        snowflakes[snowflake_code] = snow;
    }
    identify_identical(snowflakes);
    free_snowflakes(snowflakes);    

    return 0;
}
