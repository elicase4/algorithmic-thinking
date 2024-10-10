#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define hashsize(n) ((unsigned long)1 << (n))
#define hashmask(n) (hashsize(n) - 1)

unsigned long oaat(char* key, unsigned long len, unsigned long bits){
    unsigned long hash, i;
    for (hash = 0, i = 0; i < len; i++){
        hash += key[i]; // add current key to the hash
        hash += (hash << 10); //implement avalanche effect
        /*
         avalanche effect: a small change in the keys bites results in a large change to the key's hashcode (reduces the likelihood of collisions)
        */
        hash ^= (hash >> 6);
    }
    hash += (hash << 3);
    hash ^= (hash >> 11);
    hash += (hash << 15);
    return hash & hashmask(bits);
}


int main(void){
    long snowflake[] = {1, 2, 3, 4, 5, 6};
    unsigned long code = oaat((char*)snowflake, sizeof(snowflake), 17);
    printf("%lu\n", code);

    return 0;
}
