#ifndef DIAGNOSIS_H
#define DIAGNOSIS_H

#include "boolean.h"
#include <string.h>
#include "user.h"
#include "penyakit.h"
#include "ruangan.h"

void cekPenyakit(User* pasien);
void diagnosis(User user);
void searchRuangan(User user, Ruangan *ruangan);
boolean cekSuhu(User user, Penyakit penyakit);
boolean cekTekananSistolik(User user, Penyakit penyakit);
boolean cekTekananDiastolik(User user, Penyakit penyakit);
boolean cekDetakJantung(User user, Penyakit penyakit);
boolean cekSaturasiOksigen(User user, Penyakit penyakit);
boolean cekKadarGulaDarah(User user, Penyakit penyakit);
boolean cekBeratBadan(User user, Penyakit penyakit);
boolean cekTinggiBadan(User user, Penyakit penyakit);
boolean cekKadarKolesterol(User user, Penyakit penyakit);
boolean cekTrombosit(User user, Penyakit penyakit);

#endif