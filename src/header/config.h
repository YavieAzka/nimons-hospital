#ifndef CONFIG_H
#define CONFIG_H

#include "ruangan.h"
#include "inventory.h"

#define MAX_INVENTORY 100

// Ukuran denah
extern int panjang_denah;
extern int lebar_denah;
extern int kapasitas_ruangan;
extern int kapasitas_antrian;
extern int jumlah_ruangan;
extern int panjang_denah_eff;
extern int lebar_denah_eff;

// Daftar ruangan (index ke-i = ruangan ke-i dalam bentuk linear)
extern Ruangan ruanganList[MAX_RUANGAN][MAX_RUANGAN];
extern InventoryPasien daftar_inventory[MAX_INVENTORY];
extern int jumlah_inventory;

// Fungsi
void loadConfig(const char* folder);

#endif
