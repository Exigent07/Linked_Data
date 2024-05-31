#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include "fileHandle.c"

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

void handle_signal(int sig) {
    if (sig == SIGINT) {
        printf("\nYou pressed Ctrl+C (SIGINT). Exiting...\n");
        exit(0);
    } else {
        printf("\nCaught signal %d. Enter 'exit' or 'quit' to exit...\n", sig);
        printf("> ");
    }
}

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
                currentNode->count++;

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
            newNode->count = 1;

            newNode->next = list->head->next;
            newNode->prev = list->head;

            list->head->next->prev = newNode;
            list->head->next = newNode;
        }
    }
}

void deleteAllNodes(DoublyList* list) {
    if (!list || !list->head) {
        return;
    }

    Node* current = list->head->next;
    Node* nextNode;

    while (current != list->head) {
        nextNode = current->next;
        free(current);
        current = nextNode;
    }

    list->head->next = list->head;
    list->head->prev = list->head;
    list->size = 0;
}

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


void printCount(DoublyList* list) {
    if (!list) return;

    Node* current = list->head->next;

    printf("The list:\n");
    while (current != list->head) {
        printf("%d: %d, ", current->data, current->count);
        current = current->next;
    }
    printf("\n");
}

void writeListToFile(const char *filename, DoublyList* list, int size) {
    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        printf("[-] Failed to open file for writing\n");
        exit(1);
    }

    if (!list) return;

    Node* current = list->head->next;

    while (current != list->head) {
        fprintf(file, "%d ", current->data);
        current = current->next;
    }

    fclose(file);
}

Node* search(DoublyList* list, int value) {
    if (!list) {
        printf("[-] Error: The list is NULL.\n");
        return NULL;
    }

    Node* currentNode = list->head->next;
    while (currentNode != list->head) {
        if (currentNode->data == value) {
            printf("[+] Value %d found in the list.\n", value);
            return currentNode;
        }
        currentNode = currentNode->next;
    }

    printf("[-] Value %d not found in the list.\n", value);
    return NULL;
}

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
        printf("  \t  - 2 To load and print count.\n");
        printf("  \t  - 3 [Filename] To load and write to a file.\n");
        printf("  -i, --interactive\t\tTo enter interactive mode\n");
    } else if (strcmp(helpType, "interactive") == 0) {
        printf("Options:\n");
        printf("  help\t\t\tDisplay this help message\n");
        printf("  read \t\t\tSpecify the input file\n");
        printf("  write \t\twrite the data into a file\n");
        printf("  search\t\tTo search a data in the list\n");
        printf("  print\t\t\tTo print the loaded file\n");
        printf("  clear\t\t\tTo clear the screen\n");
        printf("  count\t\t\tTo print the count\n");
        printf("  load\t\t\tTo load it into linked list\n");
        printf("  free\t\t\tTo free|remove all nodes\n");
        printf("  exit|quit\t\tTo exit interactive mode\n");
    }

}

void interactiveMode(DoublyList* list) {
    char input[256];
    char filename[100];
    int *values = NULL;
    int value;
    int initial = 1;
    int loaded = 0;
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
        } else if (strcmp(input, "write") == 0) {
            if (!loaded) {
                printf("Warning: Load a file first.\n");
                continue;
            }

            printf("Enter a Filename: ");
            fgets(filename, sizeof(filename), stdin);
            filename[strcspn(filename, "\n")] = '\0';
            writeListToFile(filename, list, numValues);

            printf("Data written successfully.\n");
            continue;
        } else if (strcmp(input, "search") == 0) {
            if (!loaded) {
                printf("Warning: Load a file first.\n");
                continue;
            }

            printf("Enter the value: ");
            scanf("%d", &value);
            getchar();

            Node* result = search(list, value);
            if (result) {
                printf("[+] Value %d found in the list with count %d.\n", value, result->count);
            } else {
                printf("[-] Value %d not found in the list.\n", value);
            }
            continue;
        } else if (strcmp(input, "print") == 0) {
            if (values == NULL || numValues <= 0) {
                printf("Warning: Read a file first.\n");
                continue;
            }

            printData(values, &numValues);
            continue;
        } else if (strcmp(input, "count") == 0) {
            if (values == NULL || numValues <= 0) {
                printf("Warning: Read a file first.\n");
                continue;
            }

            printCount(list);
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
            loaded = 1;
            continue;
        } else if (strcmp(input, "free") == 0) {
            if (!loaded) {
                printf("Warning: Load a file first.\n");
                continue;
            }
            deleteAllNodes(list);
            printf("Note: Removed all nodes.\n");
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
