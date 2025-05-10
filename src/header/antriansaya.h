#ifndef ANTRIANSAYA_H
#define ANTRIANSAYA_H

#define MAX_PASIEN 200

// Untuk mendefinisikan data pasien
typedef struct {
    char nama[50];          // Nama pasien
    char dokter[50];        // Nama dokter yang menangani
    char ruangan[16];       // Ruangan tempat pasien berada
    int posisiAntrian;      // Posisi antrian pasien
    int terdaftar;          // 1 jika terdaftar, 0 jika belum terdaftar
} Pasien;

// Untuk menyimpan daftar pasien
extern Pasien antrian[MAX_PASIEN];

// Untuk menghitung jumlah pasien yang terdaftar
extern int jumlahPasien;

// Untuk mendaftar pasien dalam antrian
void daftarPasien(const char* nama, const char* dokter, const char* ruangan);

// Untuk mengecek status antrian pasien
void cekAntrian(const char* nama);

#endif 
