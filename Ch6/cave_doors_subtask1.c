#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void exploreCave(int n){
    
    int switch_positions[n], door_for_switch[n];
    int i, result;
    
    for (i = 0; i < n; i++){
        switch_positions[i] = 0;
        door_for_switch[i] = i;
    }

    for (i = 0; i < n; i++){
        result = tryCombination(switch_positions);
        if (result == i){ // Door i is closed
           switch_positions[i] = 1; 
        }
    }

    answer(switch_positions, door_for_switch);
}

int tryCombination(int switch_positions[]){

}

void answer(int switch_positions[], int door_for_switch[]){

}

int main(void){

    return 0;
}
