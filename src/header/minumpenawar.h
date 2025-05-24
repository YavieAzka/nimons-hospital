#ifndef MINUMPENAWAR_H
#define MINUMPENAWAR_H

#include "obatPenyakit.h"
#include "user.h"
extern int idxUrutanMinum;
extern int urutanMinumObat[MAX_OBAT_PER_PENYAKIT];

typedef struct {
    int IdObat;
    int urutanMinum;
    char namaObat[50];
} Perut;

extern Perut P[MAX_OBAT_PER_PENYAKIT];

const char* getNamaObatById(int idObat);
int getIdByNamaObat(char *namaObat);
int getUrutanByIdObat(int idObat);
int getIdPenyakitByRiwayat(const char* riwayat);
void getUrutanMinum(Obat list[], int nomorObat, int *idxUrutanMinum);
int checkUrutanMinum(Obat list[], int IdPenyakit, Perut *P, int urutanMinumObat[], int idxUrutanMinum);
void minumpenawar(User *pasien);

#endif
