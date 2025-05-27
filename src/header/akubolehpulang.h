#ifndef AKUPULANG_H
#define AKUPULANG_H

#include "stack.h"
#include "inventory.h"
#include "user.h"
#include "boolean.h"

boolean checkDiagnosis(User *pasien);
int getIdFromPenyakit(User *pasien);
int getjumlahObat(User *pasien);
int checkUrutanObat(User *pasien);
void urutanHarapan(User *pasien);
void akubolehpulang(User *pasien);
Ruangan *cariRuanganPasien(User *pasien);
Ruangan* cekAntrianPasien(User* pasien, Ruangan *ruanganPasien);

#endif