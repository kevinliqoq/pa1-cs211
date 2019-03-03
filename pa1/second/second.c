#include "second.h"

int numOfNodes = 0;

int main(int argc, char** argv) {

    head = NULL;

    FILE *input;
    input = fopen(argv[1], "r");

    if (input == NULL) {
        printf("error");
        return 0;
    }

    char llMethod;
    int val;

    while (!feof(input)) {

        fscanf(input, "%c\t%d\n", &llMethod, &val);

        if (llMethod == 'i') {
            head = llInsertInOrder(head, val);
        } else if (llMethod == 'd') {
            head = llDelete(head, val);
        }

    }

    fclose(input);
    printLL(head);

    return 0;

}

LList* llInsertInOrder(LList *head, int val) {
    ++numOfNodes;
    // case: node needs to go in beginning
    if (head == NULL) {
        head = (LList *) malloc(sizeof(LList));
        head->val = val;
    }
    // case: node needs to go somewhere in middl 
    else {
        // pointer of node with val to insert 
        LList *temp = (LList *) malloc(sizeof(LList));
        temp->val = val;
        LList *currentNode = head;
        LList *previousNode = NULL;

        while (currentNode != NULL) {
            if (currentNode->val >= val) {
                
                // if previous is null, then currentNode is at the head, and if currentNode is head, then previousNode is null
                if (currentNode == head) {
                    temp->next = head;
                    head = temp; // move the val in front of the head
                    break;
                } else if (previousNode->val <= val) { // previous is guarenteed to have a value 
                    temp->next = currentNode;
                    previousNode->next = temp;  // move val in front of currentNode
                    break;
                }
            }
            previousNode = currentNode;
            currentNode = currentNode->next; // move currentNode forward
        }
        // case: node needs to go at the end
        if (!currentNode && previousNode->val <= val) {
            previousNode->next = temp; // add val to the end
        }

    }
    return head;
}

LList* llDelete(LList *head, int val) {

    if (head != NULL) {
        LList *currentNode = head; // currentNode contains address for original head
        LList *previousNode = NULL;
        while (currentNode != NULL) {
            if (currentNode->val == val) {
                if (!currentNode->next && !previousNode) { // LL has 1 item and current = head
                    free(currentNode); // will free head
                    head = NULL;
                } else if (!currentNode->next && previousNode) { // LL is at the end of the list
                    previousNode->next = NULL;
                    free(currentNode);
                } else if (currentNode->next && !previousNode) { // ll is at the head and num of nudes > 1
                    head = currentNode->next; // move head oto the next node
                    free(currentNode);
                } else if (currentNode->next && previousNode) { // item is somewhere in the middle
                    previousNode->next = currentNode->next;
                    free(currentNode);
                }
                --numOfNodes;
                break;
            }
            previousNode = currentNode; // move prevnode forward
            currentNode = currentNode->next; // move currentNode forward
        }
    }
    return head;
}

void printLL(LList *head) {
    printf("%d\n", numOfNodes);
    if (head != NULL) {
        LList *currentNode = head;
        LList *previousNode = NULL;
        while (currentNode != NULL) {
            if (!previousNode || (previousNode->val != currentNode->val)) { // prev node exists implies that not at head which means there is possibility for last node & cur node vals to match
                printf("%d", currentNode->val); // skip printing for this one
                if (currentNode->next) { // following output guidelines, the very last node shouldnt have 
                    printf("\t");
                } 
            }
            previousNode = currentNode;
            currentNode = currentNode->next; // move forward
        }
    }
}
