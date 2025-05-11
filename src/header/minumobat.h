#ifndef MINUMOBAT_H
#define MINUMOBAT_H

#define MAX_OBAT 3

// Untuk mendefinisikan obat
typedef struct {
    char nama[50];        // Nama obat
    int tersedia;         // 1 jika tersedia, 0 jika tidak tersedia
} Obat;

// Untuk menampilkan daftar obat yang tersedia
void daftarObat(Obat list[], int jumlah);

// Untuk minum obat
void minumObat(Obat list[], int nomorObat);

#endif 
