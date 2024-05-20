#include <stdio.h>
#include <stdlib.h>
#include <functions.h>

int main() {
    DoublyList* list = create();
    if (!list) {
        return 1;
    }

    insertAtHead(list, 10);
    insertAtHead(list, 50);
    insertAtTail(list, 30);
    insertAtTail(list, 40);

    printList(list);

    return 0;
}