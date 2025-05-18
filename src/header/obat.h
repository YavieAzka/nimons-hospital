#ifndef OBAT_H
#define OBAT_H

typedef struct {
    int id;
    char nama[50];
} Obat;

extern Obat* obatList;
extern int obatCount;
#endif