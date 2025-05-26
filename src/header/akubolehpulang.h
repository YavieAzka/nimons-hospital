#ifndef AKUPULANG_H
#define AKUPULANG_H

#include "stack.h"
#include "inventory.h"
#include "user.h"
#include "boolean.h"

boolean checkDiagnosis(User *pasien);
int getIdFromPenyakit(User *pasien);
int getjumlahObat(User *pasien);
int checkUrutanObat(User *pasien, Stack *perut);
void urutanHarapan(User *pasien, Stack *perut, Inventory *inv);
void akubolehpulang(User *pasien, Stack *perut, Inventory *inv);

#endif