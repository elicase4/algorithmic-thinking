#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 100000

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

void identify_identical(int snowflakes[][6], int n){
    for (int i = 0; i < n; i++){
        for(int j = i+1; j < n; j++){
            if (are_identical(snowflakes[i], snowflakes[j])){
                printf("Twin snokflakes found.\n");
                return;
            }
        }
    }
    printf("No two snowflakes are alike.\n");
}

int main(void){
    static int snowflakes[SIZE][6];
    int n;
    scanf("%d", &n);
    for (int i = 0; i < n; i++){
        for(int j = 0; j < 6; j++){
            scanf("%d", &snowflakes[i][j]);
        }
    }
    identify_identical(snowflakes, n);

    return 0;
}
