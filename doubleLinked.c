#include "functions.h"

int main(int argc, char* argv[]) {
    int *values;
    int numValues;

    signal(SIGINT, handle_signal);
    signal(SIGTERM, handle_signal);

    if (argc < 2) {
        printf("[-] Error: Insufficient arguments.\n");
        printHelp(argv[0], "args");
        return 1;
    }

    DoublyList* list = create();
    if (!list) {
        printf("[-] Error: Linked list initialization failed.\n");
        return 1;
    }

    if (strcmp(argv[1], "--interactive") == 0 || strcmp(argv[1], "-i") == 0) {
        interactiveMode(list);
    } else if (strcmp(argv[1], "--file") == 0 || strcmp(argv[1], "-f") == 0) {
        if (argc < 5) {
            printf("[-] Error: Insufficient arguments for file operation.\n");
            printHelp(argv[0], "args");
            return 1;
        }

        if (strcmp(argv[3], "-a") == 0 || strcmp(argv[3], "--action") == 0) {
            if (strcmp(argv[4], "0") == 0) {
                values = readData(argv[2], &numValues);
                if (values == NULL) {
                    printf("[-] Error: Failed to read data from file.\n");
                    return 1;
                }
                printData(values, &numValues);
                free(values);
            } else if (strcmp(argv[4], "1") == 0) {
                values = readData(argv[2], &numValues);
                if (values == NULL) {
                    printf("[-] Error: Failed to read data from file.\n");
                    return 1;
                }
                insertUniqueValues(list, values, numValues);
                printList(list);
                deleteAllNodes(list);
                free(values);
            } else if (strcmp(argv[4], "2") == 0) {
                values = readData(argv[2], &numValues);
                if (values == NULL) {
                    printf("[-] Error: Failed to read data from file.\n");
                    return 1;
                }
                insertUniqueValues(list, values, numValues);
                printCount(list);
                deleteAllNodes(list);
                free(values);
            } else if (strcmp(argv[4], "3") == 0 && argv[5]) {
                values = readData(argv[2], &numValues);
                insertUniqueValues(list, values, numValues);
                writeListToFile(argv[5], list, numValues);
                printf("Data written successfully.\n");
                deleteAllNodes(list);
                free(values);
            } else {
                printf("[-] Error: Invalid action.\n");
                printHelp(argv[0], "args");
                return 1;
            }
        } else {
            printf("[-] Error: Invalid action argument.\n");
            printHelp(argv[0], "args");
            return 1;
        }
    } else {
        printf("[-] Error: Invalid arguments.\n");
        printHelp(argv[0], "args");
        return 1;
    }

    return 0;
}
