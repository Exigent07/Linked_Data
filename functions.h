#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <stdio.h>
#include <stdlib.h>

/*
The Node struct represents a single node in the doubly linked list. 
It contains:
- data: The integer data stored in the node.
- count: An additional integer that can be used for counting purposes.
- prev: A pointer to the previous node in the list.
- next: A pointer to the next node in the list.
*/
typedef struct Node {
    int data;
    int count;
    struct Node* prev;
    struct Node* next;
} Node;

/*
The DoublyList struct represents the entire doubly linked list. 
It contains:
- head: A pointer to the dummy node which simplifies insertion and deletion operations.
- size: An integer representing the number of elements in the list (excluding the dummy node).
*/
typedef struct {
    Node* head;
    int size;
} DoublyList;

/*
Creates a new doubly linked list and initializes it with a dummy node.
Returns a pointer to the newly created DoublyList. If memory allocation fails, returns NULL.
The dummy node's prev and next pointers point to itself, creating a circular structure.
*/
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

/*
Inserts a new node with the given data at the head (beginning) of the doubly linked list.
Updates the pointers of the existing nodes to maintain the doubly linked structure.
Increments the size of the list.
*/
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

/*
Inserts a new node with the given data at the tail (end) of the doubly linked list.
Updates the pointers of the existing nodes to maintain the doubly linked structure.
Increments the size of the list.
*/
void insertAtTail(DoublyList* list, int data) {
    if (!list) return;

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

/*
Prints the data of each node in the doubly linked list from the head to the tail.
Starts from the node after the dummy node and traverses the list until it reaches the dummy node again.
*/
void printList(DoublyList* list) {
    if (!list) return;

    Node* current = list->head->next;
    while (current != list->head) {
        printf("%d ", current->data);
        current = current->next;
    }
    printf("\n");
}

/*
Prints the usage and options of the program.

Arguments:
    programName: The name of the program executable.

Options:
    -h, --help    Display this help message
    -f, --file FILE    Specify the input file

This function prints the usage and options of the program. It provides information on how to use the program's command-line options and what each option does.
*/

void printHelp(const char* programName, const char* helpType) {
    if (strcmp(helpType, "args") == 0) {
        printf("Usage: %s [OPTIONS]\n", programName);
        printf("Options:\n");
        printf("  -h, --help\t\t\tDisplay this help message\n");
        printf("  -f, --file FILE\t\tSpecify the input file\n");
        printf("  -a, --action operation\tSpecify the operation to perform on the data\n");
        printf("  \t[Operations]\n");
        printf("  \t  - 0 To print the data.\n");
        printf("  \t  - 1 To load it into linked list.\n");
        printf("  -i, --interactive\t\tTo enter interactive mode\n");
    } else if (strcmp(helpType, "interactive") == 0) {
        printf("Options:\n");
        printf("  help\t\t\tDisplay this help message\n");
        printf("  read FILENAME\t\tSpecify the input file\n");
        printf("  print\t\t\tTo print the loaded file\n");
        printf("  load\t\t\tTo load it into linked list\n");
        printf("  exit|quit\t\tTo exit interactive mode\n");
    }
    

}

void interactiveMode() {
    char input[256];
    int initial = 1;
    while (1) {
        if (initial) {
            printf("\nEnter a command (type 'help' for usage) > ");
            initial = 0;
        } else {
            printf("\n> ");
        }
        
        fgets(input, sizeof(input), stdin);

        input[strcspn(input, "\n")] = '\0';

        if (strcmp(input, "help") == 0) {
            printHelp("", "interactive");
        } else if (strcmp(input, "quit") == 0 || strcmp(input, "exit") == 0) {
            printf("Exiting interactive mode.\n");
            break;
        } else {
            printf("Unknown command. Type 'help' for usage.\n");
        }
    }
}

#endif