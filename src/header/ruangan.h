#ifndef RUANGAN_H
#define RUANGAN_H
#include "user.h"
#include "queue.h"

#define MAX_PASIEN 5
#define MAX_RUANGAN 5

typedef struct 
{
    int idDokter;
    char usernameDokter[MAX_USERNAME];
    int idPasien[MAX_PASIEN];
    char usernamePasien[MAX_PASIEN][MAX_USERNAME];
    int totalPasien;
    Queue antrianPasien;
} Ruangan;

#endif