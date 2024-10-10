#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void set_a_switch(int door, int switch_positions[], int door_for_switch[], int n){
    
    int i, result;
    int found = 0;

    // Set all mon-associated switch positions to 0
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

    // Linear Search for the switch that opens the door of interest
    i = 0;
    while (!found){
       
        // Toogle a switch not associated with a door 
        if (door_for_switch[i] == -1){
            switch_positions[i] = 1 - switch_positions[i]; 
        } 
        
        // Check the new status of the door. If the door is open, we have found the assocaited switch. 
        result = tryCombination(switch_positions);
        if (result != door){
            found = 1; 
        } else{
            i++
        }

    }
    
    door_for_switch[i] = door;
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
