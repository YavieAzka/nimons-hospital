#ifndef INVENTORY_H
#define INVENTORY_H

#define MAX_INVENTORY 100
#include "user.h"

typedef struct {
    int pasien_id;
    int obat_id[MAX_INVENTORY];
    int count;
} InventoryPasien;

extern InventoryPasien inventoryPasien; 

void initInventory();
void addInventory(int id_obat);
void removeInventory(int index);
void printInventory();
InventoryPasien* getInventoryByUser(User* user);
void removeInventoryByUser(InventoryPasien* inv, int index);
void searchJumlahInventory(int* jumlahInventory);

#endif