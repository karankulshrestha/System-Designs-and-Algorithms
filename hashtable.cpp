#include <bits/stdc++.h>
#include <cstring>
using namespace std;

struct node {
    const char* key;
    const char* value;
    struct node* next;
};


void setNode(struct node* node, char* key, char* value) {
    node->key = key;
    node->value = value;
    node->next = NULL;
};


struct hashMap {
    int numOfElements, capacity;
    struct node** arr;
};


void initializeHashmap(struct hashMap* mp) {
    mp->capacity = 100;
    mp->numOfElements = 0;
    mp->arr = (struct node**)malloc(sizeof(struct node*) * mp->capacity);
    return;
};


int hashFunction(struct hashMap* mp, const char* key) {
    int bucketIndex;
    int sum = 0, factor = 31;
    for (int i = 0; i < strlen(key); i++) {

        sum = ((sum % mp->capacity) + (((int)key[i]) * factor) % mp->capacity) % mp->capacity;

        factor = ((factor % INT_MAX) * (31 % INT_MAX)) % INT_MAX;
    }
    bucketIndex = sum;
    return bucketIndex;
}


void insert(struct hashMap* mp, const char* key, const char* value) {
    int bucketIndex = hashFunction(mp, key);
    struct node* newNode = (struct node*) malloc(sizeof(struct node));
    newNode->key = key;
    newNode->value = value;
    newNode->next = NULL;

    if(mp->arr[bucketIndex] == NULL) {
        mp->arr[bucketIndex] = newNode;
    } else {
        struct node* temp = mp->arr[bucketIndex];
        newNode->next = temp;
        mp->arr[bucketIndex] = newNode;
    }
    return;
}



void deleteKey(struct hashMap* mp, const char* key) {
    int bucketIndex = hashFunction(mp, key);
    struct node* prevNode = NULL;

    struct node* currentNode = mp->arr[bucketIndex];

    while(currentNode != NULL) {
        if(strcmp(key, currentNode->key) == 0) {
            if(currentNode == mp->arr[bucketIndex]) {
                mp->arr[bucketIndex] = currentNode->next;
            } else {
                prevNode->next = currentNode->next;
            }
            
            free(currentNode);
            break;
        };
        prevNode = currentNode;
        currentNode = currentNode->next;

    }
    return;
}


const char* search(struct hashMap* mp, const char* key) {
    int bucketIndex = hashFunction(mp, key);
    struct node* currentNode = mp->arr[bucketIndex];
    while(currentNode!= NULL) {
        if(strcmp(key, currentNode->key) == 0) {
            return currentNode->value;
        }
        currentNode = currentNode->next;
    }

    return "Key not found";
}


int main() {
    struct hashMap* mp = (struct hashMap*)malloc(sizeof(struct hashMap));
    initializeHashmap(mp);

    // Insert some key-value pairs
    insert(mp, "karan", "shreya");
    insert(mp, "aman", "Vartika");
    insert(mp, "jimmy", "lanes");
    insert(mp, "pattern", "net");
    insert(mp, "badboy", "kx");

    // Print the values for the keys
    printf("%s\n", search(mp, "karan"));   // Expected: "shreya"
    printf("%s\n", search(mp, "aman"));    // Expected: "Vartika"
    printf("%s\n", search(mp, "jimmy"));   // Expected: "lanes"
    printf("%s\n", search(mp, "badboy"));  // Expected: "kx"

    // Deleting a key
    deleteKey(mp, "badboy");

    // After deletion, try to search again
    printf("%s\n", search(mp, "badboy"));  // Expected: "Key not found"

    return 0;
}
