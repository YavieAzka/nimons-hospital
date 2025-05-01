#ifndef USER_H
#define USER_H

#define MAX_USERNAME 50
#define MAX_PASSWORD 50
#define MAX_ROLE 10
#define MAX_RIWAYAT 100
#define MAX_USERS 100



#include <stdio.h>
#include <string.h>
#include <stdlib.h>


typedef struct {
    int id;
    char username[MAX_USERNAME];
    char password[MAX_PASSWORD];
    char role[MAX_ROLE]; // "manager", "dokter", "pasien"
    char riwayat_penyakit[MAX_RIWAYAT]; // Riwayat penyakit (string deskripsi)
    // Atribut kesehatan pasien
    float suhu_tubuh;
    int tekanan_darah_sistolik;
    int tekanan_darah_diastolik;
    int detak_jantung;
    int saturasi_oksigen;
    int kadar_gula_darah;
    float berat_badan;
    float tinggi_badan;
    int kadar_kolesterol;
    int kadar_kolesterol_ldl;
    int trombosit;

} User;


#endif



