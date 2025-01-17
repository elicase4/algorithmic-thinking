#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 1000000

typedef int board[SIZE*2];
typedef int positions[SIZE*2];

void add_position(int from_height, int to_height, int max_height, positions new_positions, int* num_new_positions, int* itching, board min_moves){
    if (to_height <= max_height && itching[to_height] == 0 && min_moves[to_height] == -1){
        min_moves[to_height] = 1 + min_moves[from_height];
        new_positions[*num_new_positions] = to_height;
        (*num_new_positions)++;
    }
}

void find_distances(int target_height, int jump_distance, int* itching, board min_moves){
    static positions cur_positions, new_positions;
    int num_cur_positions, num_new_positions;
    int from_height;
    for (int i = 0; i < target_height*2; i++){
        min_moves[i] = -1;
    }
    min_moves[0] = 0;
    cur_positions[0] = 0;
    num_cur_positions = 1;

    while (num_cur_positions > 0){
        num_new_positions = 0;
        for (int i = 0; i < num_cur_positions; i++){
            from_height = cur_positions[i];
            add_position(from_height, from_height + jump_distance, 2*target_height - 1, new_positions, &num_new_positions, itching, min_moves);
            for (int j = 0; j < from_height; j++){
                add_position(from_height, j, 2*target_height - 1, new_positions, &num_new_positions, itching, min_moves);
            }
        }

        num_cur_positions = num_new_positions;
        for (int i = 0; i < num_cur_positions; i++){
            cur_positions[i] = new_positions[i];
        }
    }
}

void solve(int target_height, board min_moves){
    int best = -1;
    for (int i = target_height; i < 2*target_height; i++){
        if (min_moves[i] != -1 && (best == -1 || min_moves[i] < best)){
            best = min_moves[i];
        }
    }
    printf("%d\n", best);
}

int main(void){
    int target_height, jump_distance, num_itching_sections;
    static int itching[SIZE*2] = {0};
    static board min_moves;
    int itch_start, itch_end;
    scanf("%d%d%d", &target_height, &jump_distance, &num_itching_sections);
    for (int i = 0; i < num_itching_sections; i++){
        scanf("%d%d", &itch_start, &itch_end);
        for (int j = itch_start; j < itch_end; j++){
            itching[j] = 1;
        }
    }
    find_distances(target_height, jump_distance, itching, min_moves);
    solve(target_height, min_moves);

    return 0;
}
