#ifndef USER_H
#define USER_H

#define MAX_PENYAKIT 50

#include <stdio.h>
#include <string.h>
#include <stdlib.h>


typedef struct {
    int id;
    char name_penyakit[MAX_PENYAKIT];
    float suhu_tubuh_min;
    float suhu_tubuh_max;
    int tekanan_darah_sistolik_min;
    int tekanan_darah_sistolik_max;
    int tekanan_darah_diastolik_min;
    int tekanan_darah_diastolik_max;
    int detak_jantung_min;
    int detak_jantung_max;
    float saturasi_oksigen_min;
    float saturasi_oksigen_max;
    int kadar_gula_darah_min;
    int kadar_gula_darah_max;
    float berat_badan_min;
    float berat_badan_max;
    int tinggi_badan_min;
    int tinggi_badan_max;
    int kadar_kolesterol_min;
    int kadar_kolesterol_max;
    int trombosit_min;
    int trombosit_max;
} Penyakit;


#endif



