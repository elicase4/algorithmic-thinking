#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ROWS 3001
#define MAX_COLS 3001

typedef int board[MAX_ROWS][MAX_COLS];

int compare(const void* v1, const void* v2){
    
    int num1 = *(const int*) v1;
    int num2 = *(const int*) v1;

    return (num1 - num2);
}

int median(int top_row, int left_col, int bottom_row, int right_col, board q){
    
    static int cur_rectangle[MAX_ROWS*MAX_COLS];
    int i, j, num_cur_rectangle;
    num_cur_rectangle = 0;

    for (i = top_row; i < bottom_row; i++) {
        for (j = left_col; j < right_col; j++){
            cur_rectangle[num_cur_rectangle] = q[i][j];
            num_cur_rectangle++;
        }    
    }

    qsort(cur_rectangle, num_cur_rectangle, sizeof(int), compare);

    return cur_rectangle[num_cur_rectangle / 2];
}

int rectangle(int r, int c, int h, int w, board q){
    
    int top_row, left_col, bottom_row, right_col;
    int best = r*c + 1;
    int result;

    for (top_row = 0; top_row < (r - h + 1); top_row++) {
        for (left_col = 0; left_col < (c - w + 1); left_col++){
            bottom_row = top_row + h - 1;
            right_col = left_col + w - 1;
            result = median(top_row, left_col, bottom_row, right_col, q);
            if (result < best){
               best = result; 
            }
        }    
    }

    return best;
}

int main(void){

    static board q = {{48, 16, 15, 45, 40, 28, 8},
        {20, 11, 36, 19, 24, 6, 33},
        {22, 39, 30, 7, 9, 1, 18},
        {14, 35, 2, 13, 31, 12, 46},
        {32, 37, 21, 3, 41, 23, 29},
        {42, 49, 38, 10, 17, 47, 5},
        {43, 4, 34, 25, 26, 27, 44}};

    int result = rectangle(7, 7, 5, 3, q);
    printf("%d\n", result);

    return 0;
}
