#include "../header/queue.h"

void initQueue(Queue* q) {
    q->front = NULL;
    q->rear = NULL;
    q->length = 0;
}

void enqueue(Queue* q, int idPasien, const char* usernamePasien) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->idPasien = idPasien;
    strcpy(newNode->usernamePasien, usernamePasien);
    newNode->next = NULL;

    if (isEmptyQueue(q)) {
        q->front = newNode;
    } else {
        q->rear->next = newNode;
    }
    q->rear = newNode;
    q->length++;
}

bool dequeue(Queue* q, int* idOut, char* usernameOut) {
    if (isEmptyQueue(q)) return false;

    Node* temp = q->front;
    *idOut = temp->idPasien;
    strcpy(usernameOut, temp->usernamePasien);

    q->front = q->front->next;
    if (q->front == NULL) q->rear = NULL;

    free(temp);
    q->length--;
    return true;
}

bool peekFront(Queue* q, int* idOut, char* usernameOut) {
    if (isEmptyQueue(q)) return false;
    *idOut = q->front->idPasien;
    strcpy(usernameOut, q->front->usernamePasien);
    return true;
}

bool isEmptyQueue(Queue* q) {
    return q->front == NULL;
}

void printQueue(Queue* q) {
    Node* current = q->front;
    int i = 1;
    if (isEmptyQueue(q)) {
        printf("  Tidak ada pasien di antrian saat ini.\n");
        return;
    }
    while (current != NULL) {
        printf("  %d. %s\n", i++, current->usernamePasien);
        current = current->next;
    }
}
