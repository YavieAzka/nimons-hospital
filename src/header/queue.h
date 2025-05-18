#ifndef QUEUE_H
#define QUEUE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_USERNAME 50

typedef struct Node {
    int idPasien;
    char usernamePasien[MAX_USERNAME];
    struct Node* next;
} Node;

typedef struct {
    Node* front;
    Node* rear;
    int length;
} Queue;

// Inisialisasi queue
void initQueue(Queue* q);

// Enqueue pasien ke antrian
void enqueue(Queue* q, int idPasien, const char* usernamePasien);

// Dequeue pasien dari antrian
bool dequeue(Queue* q, int* idOut, char* usernameOut);

// Melihat pasien di front tanpa menghapus
bool peekFront(Queue* q, int* idOut, char* usernameOut);

// Mengecek apakah queue kosong
bool isEmptyQueue(Queue* q);

// Menampilkan isi antrian (untuk keperluan debug / tampil)
void printQueue(Queue* q);

#endif
