#ifndef DIAGNOSIS_H
#define DIAGNOSIS_H

#include <stdbool.h>
#include <string.h>
#include "user.h"
#include "penyakit.h"
#include "ruangan.h"

char *cekPenyakit(User pasien);
void diagnosis(User user);
void searchRuangan(User user, Ruangan *ruangan);
bool cekSuhu(User user, Penyakit penyakit);
bool cekTekananSistolik(User user, Penyakit penyakit);
bool cekTekananDiastolik(User user, Penyakit penyakit);
bool cekDetakJantung(User user, Penyakit penyakit);
bool cekSaturasiOksigen(User user, Penyakit penyakit);
bool cekKadarGulaDarah(User user, Penyakit penyakit);
bool cekBeratBadan(User user, Penyakit penyakit);
bool cekTinggiBadan(User user, Penyakit penyakit);
bool cekKadarKolesterol(User user, Penyakit penyakit);
bool cekTrombosit(User user, Penyakit penyakit);


#endif