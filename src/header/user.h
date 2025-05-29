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
#include "stack.h"

typedef struct {
    int id;
    char username[MAX_USERNAME];
    char password[MAX_PASSWORD];
    char role[MAX_ROLE]; // "manager", "dokter", "pasien"
    char riwayat_penyakit[MAX_RIWAYAT]; 

    // Atribut kesehatan pasien
    float suhu_tubuh;
    int tekanan_darah_sistolik;
    int tekanan_darah_diastolik;
    int detak_jantung;
    float saturasi_oksigen;
    int kadar_gula_darah;
    float berat_badan;
    int tinggi_badan;                  
    int kadar_kolesterol;
    int trombosit;
    Stack perut;

    //nyawa
    int nyawa;
    int jumlah_kesalahan;
} User;

extern User users[MAX_USERS];
extern int userCount;

#endif
