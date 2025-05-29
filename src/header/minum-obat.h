#ifndef MINUMOBAT_H
#define MINUMOBAT_H

#include "user.h"
#include "obat.h"
#include "inventory.h"

extern InventoryPasien daftar_inventory[];
extern int jumlah_inventory;


// Pasien meminum obat dari inventory miliknya sendiri, masuk ke perut (stack)
void minumObat(User* user);

#endif