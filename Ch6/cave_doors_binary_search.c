#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void set_a_switch(int door, int switch_positions[], int door_for_switch[], int n){
    
    int i, result;
    int low = 0, high = (n-1), mid;

    // Set all non-associated switch positions to 0
    for (i = 0; i < n; i++){
        if (door_for_switch[i] == -1){
            switch_positions[i] = 0;
        }
    }

    // Want to close the current door if it is left open (works because the result test sees if the previously set switch position resulted in the door being closed)
    result = tryCombination(switch_positions);
    if (result != door){
        for (i = 0; i < n; i++){
            if (door_for_switch[i] == -1){
                switch_positions[i] = 1;
            }
        } 
    }

    // Binary search for the switch that opens the door of interest
    while (low != high){
        
        // Toogle the door from low to mid 
        mid = (low + high) / 2;
        for (i = low; i <= mid; i++){
            if (door_for_switch[i] == -1){
                switch_positions[i] = 1 - switch_positions[i];
            }
        } 
        
        // Check if the door of interest is opened or closed 
        result = tryCombination(switch_positions);

        // If the door is open, reduce the search range from low to mid and close all the doors again
        if (result != door){
            high = mid;
            for (i = low; i <= mid; i++){
                if (door_for_switch[i] == -1){
                    switch_positions[i] = 1 - switch_positions[i];
                }
            }
        // If the door is close, reduce the search range from mid to high 
        } else{
            low = mid + 1;
        }

    }
    
    // Open the door that was found and toogle its switch to the open position 
    door_for_switch[low] = door;
    switch_positions[low] = 1 - switch_positions[low];
}

void exploreCave(int n){
    
    int switch_positions[n], door_for_switch[n];
    int i;
    
    for (i = 0; i < n; i++){
        door_for_switch[i] = -1;
    }   

    for (i = 0; i < n; i++){
        set_a_switch(i, switch_positions, door_for_switch, n);
    } 

    answer(switch_positions, door_for_switch);
}


// returns the number of the first closed door or -1 if all doors are open
int tryCombination(int switch_positions[]){

}

void answer(int switch_positions[], int door_for_switch[]){

}

int main(void){

    return 0;
}
