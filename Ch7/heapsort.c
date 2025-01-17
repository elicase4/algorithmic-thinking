#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define N 10

void min_heap_insert(int* heap, int* num_heap, int value){
    
    int i;
    int temp;

    (*num_heap)++;
    heap[*num_heap] = value;
    i = *num_heap;

    while ((i > 1) && (heap[i] < heap[i / 2])){
        temp = heap[i];
        heap[i] = heap[i / 2];
        heap[i / 2] = temp;
        i = i / 2; 
    }
}

int min_heap_extract(int* heap, int* num_heap){
    
    int remove, temp;
    int i, child;

    remove = heap[1];
    heap[1] = heap[*num_heap];
    (*num_heap)--;
    i = 1;

    while ((2*i) <= *num_heap){
        
        child = (2*i);
        
        if ((child < *num_heap) && (heap[child + 1] < heap[child])){
            child++;
        }

        if (heap[child] < heap[i]){
            temp = heap[i];
            heap[i] = heap[child];
            heap[child] = temp;
            i = child; 
        } else {
            break;
        }
    }

    return remove;
}

int main(void){
    
    static int values[N] = {96, 61, 36, 74, 45, 60, 47, 6, 95, 93};
    int min_heap[N+1];
    int i, min_num_heap = 0;

    for (i = 0; i < N; i++){
        min_heap_insert(min_heap, &min_num_heap, values[i]);
    }
    
    for (i = 0; i < N; i++){
        values[i] = min_heap_extract(min_heap, &min_num_heap);
    }

    for (i = 0; i < N; i++){
        printf("%d ", values[i]);
    }
    printf("\n");

    return 0;
}
