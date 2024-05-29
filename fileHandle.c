#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <signal.h>

enum {
    SUCCESS,
    FAILURE
};

int* readData(const char *filename, int *numValues) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("[-] Error opening file.\n");
        return NULL;
    }

    int count = 0;
    int temp;
    while (fscanf(file, "%d", &temp) == 1) {
        count++;
    }

    int *values = (int*)malloc(count * sizeof(int));
    if (values == NULL) {
        printf("[-] Memory allocation failed.\n");
        fclose(file);
        return NULL;
    }

    rewind(file);

    for (int i = 0; i < count; i++) {
        fscanf(file, "%d", &values[i]);
    }

    *numValues = count;

    fclose(file);

    return values;
}

int printData(int *values, int *numValues) {
    if (values == NULL || numValues == NULL || *numValues <= 0) {
        printf("[-] Invalid input.\n");
        return FAILURE;
    }

    printf("Values read from the file:\n");
    for (int i = 0; i < *numValues; i++) {
        printf("%d ", values[i]);
    }
    printf("\n");

    return SUCCESS;
}