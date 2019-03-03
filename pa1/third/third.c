#include "third.h"

int collisionCount = 0; // collisions count
int successfulSearchCount = 0; // successful search count
LLnode* nodesToBeFreed[BUCKET_SIZE + 1];
int insertCount = 0;

int main(int argc, char** argv) {

    FILE *input;
    input = fopen(argv[1], "r");

    if (input == NULL) {
        printf("error");
        return 0;
    }

    char hashMethod;
    int key;
    LLnode* buckets[BUCKET_SIZE + 1]; // add one because we can still accomodate hashed values upto and including 10000

    int i;
    for (i = 0; i < BUCKET_SIZE; i++) { // clear out array
    	buckets[i] = NULL;
    }

    while (!feof(input)) {

        fscanf(input, "%c\t%d\n", &hashMethod, &key);

        if (hashMethod == 'i') {
            hashInsert(key, buckets);
            ++insertCount;
        } else if (hashMethod == 's') {
            hashSearch(key, buckets);
        }
    }

    fclose(input);

    printf("%d\n", collisionCount);
    printf("%d", successfulSearchCount);
    freeBuckets(insertCount, nodesToBeFreed);

    return 0;
}

void hashInsert(int key, LLnode* buckets[]) {
    int hashValue = key % BUCKET_SIZE;
    if (hashValue < 0) { // bucket lower limit is 0
        hashValue += 10000;
    }
    if (hashValue > BUCKET_SIZE) { // bucket upper limit is 10,000., seperate statement because the negative case could still go above upper limit when made positive
        return;
    }

    LLnode* hashedNode = (LLnode *) malloc(sizeof(LLnode));
    hashedNode->val = key;

    if (buckets[hashValue] != NULL) { // a collision has occured
        ++collisionCount; 
        LLnode* head = buckets[hashValue]; // set the 'head' node to the node at the hashValue, this will be a pointer to the first node in the collision list

        while (head) {
            if (head->val == key) { // already in list
                free(hashedNode); //dont need because already in list, free node
                return;
            } 
            if (!(head->next)) { // reached the end of the ll and there is no dupes
                head->next = hashedNode; // add this node to the end of the list
                nodesToBeFreed[insertCount] = hashedNode;
                return;
            }
            head = head->next;
        }
    } else { // no collision
        hashedNode->next = NULL;
        buckets[hashValue] = hashedNode;
        nodesToBeFreed[insertCount] = hashedNode;
    }
}

void hashSearch(int key, LLnode* buckets[]) {
    int hashValue = key % BUCKET_SIZE;

    if (hashValue < 0) { // bucket lower limit is 0
        hashValue += 10000;
    }
    if (hashValue > BUCKET_SIZE) { // bucket upper limit is 10,000., seperate statement because the negative case could still go above upper limit when made positive
        return;
    }
    
    if (buckets[hashValue]) {
        LLnode* head = buckets[hashValue];
        while (head != NULL) {
            if (head->val == key) {
                ++successfulSearchCount;
            }
            head = head->next;
        }
    }

}

void freeBuckets(int insertCount, LLnode * nodesToBeFreed[]) {
    int i;

    for (i = 0; i < insertCount; i++) {
        if (nodesToBeFreed[i] != NULL) {
            free(nodesToBeFreed[i]);
        }
    } 
}