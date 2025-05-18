#ifndef OBAT_PENYAKIT_H
#define OBAT_PENYAKIT_H

#define MAX_OBAT_PER_PENYAKIT 20  // <-- ini penting

typedef struct {
    int id_penyakit;
    int id_obat[MAX_OBAT_PER_PENYAKIT];
    int jumlah_obat;
} ObatPenyakit;

// Array dan count global (harus extern di header ini jika dideklarasi di load.c)
extern ObatPenyakit* obatPenyakitList;
extern int obatPenyakitCount;

#endif
