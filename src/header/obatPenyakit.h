#ifndef OBAT_PENYAKIT_H
#define OBAT_PENYAKIT_H

#define MAX_OBAT_PER_PENYAKIT 20  // <-- ini penting

typedef struct {
    int obat_id;
    int penyakit_id;
    int urutan_minum;
} ObatPenyakit;

// Array dan count global (harus extern di header ini jika dideklarasi di load.c)
extern ObatPenyakit* obatPenyakitList;
extern int obatPenyakitCount;

#endif
