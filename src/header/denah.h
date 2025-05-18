#ifndef DENAH_H
#define DENAH_H

#include "ruangan.h"
#define MAX_BARIS 100
#define MAX_KOLOM 100

typedef struct 
{
    Ruangan daftarRuang[MAX_BARIS][MAX_KOLOM];
    int MaxPasien;
    int barisMax;
    int barisEff;
    int kolomMax;
    int kolomEff;
} Denah;

void lihatRuang(Denah denah, char * str);
void gambarDenah(Denah denah);
void denah();
void gambarDenah(Denah denah);
void getUsernameFromArray(int id, char* str);

#endif