#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include "fileHandle.c"

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
    This function inserts unique values from an array into a doubly linked list.
    It checks each value in the array against the existing nodes in the list.
    If a value already exists in the list, it is moved to the front of the list.
    If a value does not exist in the list, it is inserted at the front of the list.

    Parameters:
        - list: Pointer to a DoublyList representing the linked list.
        - values: Pointer to an array of integers containing the values to be inserted.
        - numValues: Number of values in the array.

    Algorithm:
        1. For each value in the array:
            a. Check if the value already exists in the list.
            b. If the value exists, move it to the front of the list.
            c. If the value does not exist, insert it at the front of the list.

    Note:
        - This function assumes that the linked list is initialized and has a valid head node.
        - Memory allocation for new nodes is handled within the function.
        - Duplicates are moved to the front to ensure uniqueness in the list.
*/

void insertUniqueValues(DoublyList* list, int* values, int numValues) {
    if (!list || !values || numValues <= 0) {
        printf("[-] Error: Invalid input parameters.\n");
        return;
    }

    for (int i = 0; i < numValues; i++) {
        int valueToInsert = values[i];

        Node* currentNode = list->head->next;
        while (currentNode != list->head) {
            if (currentNode->data == valueToInsert) {
                currentNode->prev->next = currentNode->next;
                currentNode->next->prev = currentNode->prev;

                currentNode->next = list->head->next;
                currentNode->prev = list->head;

                list->head->next->prev = currentNode;
                list->head->next = currentNode;

                break;
            }
            currentNode = currentNode->next;
        }

        if (currentNode == list->head) {
            Node* newNode = (Node*)malloc(sizeof(Node));
            if (!newNode) {
                printf("[-] Error: Memory allocation failed.\n");
                return;
            }
            newNode->data = valueToInsert;

            newNode->next = list->head->next;
            newNode->prev = list->head;

            list->head->next->prev = newNode;
            list->head->next = newNode;
        }
    }
}

/*
Prints the data of each node in the doubly linked list from the head to the tail.
Starts from the node after the dummy node and traverses the list until it reaches the dummy node again.
*/

void printList(DoublyList* list) {
    if (!list) return;

    Node* current = list->head->next;

    printf("The list:\n");
    while (current != list->head) {
        printf("%d, ", current->data);
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
        printf("  read \t\t\tSpecify the input file\n");
        printf("  print\t\t\tTo print the loaded file\n");
        printf("  clear\t\t\tTo clear the screen\n");
        printf("  load\t\t\tTo load it into linked list\n");
        printf("  exit|quit\t\tTo exit interactive mode\n");
    }

}

/*
    This function implements an interactive mode for command-line interaction.
    It continuously prompts the user for input commands until the user chooses to exit.
    Supported commands include 'help' for usage information, 'quit' or 'exit' to exit interactive mode,
    and handling of unknown commands with appropriate feedback.

    Algorithm:
        1. Initialize an input buffer and set initial flag for prompting the user.
        2. Continuously loop to prompt the user for input.
        3. Parse user input and handle supported commands:
            - 'help': Print usage information using printHelp function.
            - 'quit' or 'exit': Exit the interactive mode loop.
            - Unknown commands: Provide feedback about unknown commands.

    Note:
        - Input commands are case-sensitive.
        - The 'help' command displays usage information for interactive mode.
        - Exiting interactive mode terminates the loop and returns to the main program.
*/

void interactiveMode(DoublyList* list) {
    char input[256];
    char filename[100];
    int *values = NULL;
    int initial = 1;
    int numValues = 0;
    
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
        } else if (strcmp(input, "read") == 0) {
            printf("Enter the Filename: ");
            fgets(filename, sizeof(filename), stdin);
            filename[strcspn(filename, "\n")] = '\0';
            values = readData(filename, &numValues);
            if (values == NULL) {
                printf("Error reading file.\n");
                numValues = 0;
            } else {
                printf("File read successfully.\n");
            }
            continue;
        } else if (strcmp(input, "print") == 0) {
            if (values == NULL || numValues <= 0) {
                printf("Warning: Read a file first.\n");
                continue;
            }

            printData(values, &numValues);
            continue;
        } else if (strcmp(input, "load") == 0) {
            if (values == NULL || numValues <= 0) {
                printf("Warning: Read a file first.\n");
                continue;
            }

            insertUniqueValues(list, values, numValues);
            printList(list);
            free(values);
            values = NULL;
            numValues = 0;
            continue;
        } else if (strcmp(input, "clear") == 0) {
                #ifdef _WIN32
                    system("cls");
                #else
                    system("clear");
                #endif

                continue;
        } else if (strcmp(input, "quit") == 0 || strcmp(input, "exit") == 0) {
            printf("Exiting interactive mode.\n");
            break;
        } else {
            printf("Unknown command. Type 'help' for usage.\n");
        }
    }
}

#endif