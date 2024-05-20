#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    int count;
    struct Node* prev;
    struct Node* next;
} Node;

typedef struct {
    Node* head;
    int size;
} DoublyList;

DoublyList* create() {
    DoublyList* list = (DoublyList*)malloc(sizeof(DoublyList));
    if (!list) {
        printf("[-] Memory allocation failed\n");
        return NULL;
    }
    
    Node* dummyNode = (Node*)malloc(sizeof(Node));
    if (!dummyNode) {
        printf("[-] Memory allocation failed\n");
        free(list);
        return NULL;
    }

    dummyNode->data = 0;
    dummyNode->prev = dummyNode;
    dummyNode->next = dummyNode;

    list->head = dummyNode;
    list->size = 0;

    return list;
}

void insertAtHead(DoublyList* list, int data) {
    if (!list) return;

    Node* newNode = (Node*)malloc(sizeof(Node));
    if (!newNode) {
        printf("[-] Memory allocation failed\n");
        return;
    }

    newNode->data = data;

    Node* head = list->head;
    Node* firstNode = head->next;

    newNode->next = firstNode;
    newNode->prev = head;
    head->next = newNode;
    firstNode->prev = newNode;

    list->size++;
}

void insertAtTail(DoublyList* list, int data) {
    if (!list) {
        return; 
    }

    Node* newNode = (Node*)malloc(sizeof(Node));
    if (!newNode) {
        printf("[-] Memory allocation failed\n");
        return;
    }

    newNode->data = data;

    Node* head = list->head;
    Node* lastNode = head->prev;

    newNode->next = head;
    newNode->prev = lastNode;
    lastNode->next = newNode;
    head->prev = newNode;

    list->size++;
}

void printList(DoublyList* list) {
    if (!list) {
        return;
    }

    Node* current = list->head->next;
    while (current != list->head) {
        printf("%d ", current->data);
        current = current->next;
    }
    printf("\n");
}