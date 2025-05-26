#include <stdio.h>
#include "../header/inventory.h"
#include "../header/obat.h"

InventoryPasien inventoryPasien;

void initInventory() {
    inventoryPasien.count = 0;
}

void addInventory(int id_obat) {
    if (inventoryPasien.count < MAX_INVENTORY) {
        inventoryPasien.obat_id[inventoryPasien.count++] = id_obat;
    }
}

void removeInventory(int index) {
    for (int i = index; i < inventoryPasien.count - 1; i++) {
        inventoryPasien.obat_id[i] = inventoryPasien.obat_id[i + 1];
    }
    inventoryPasien.count--;
}

void printInventory() {
    printf("== Inventory ==\n");
    for (int i = 0; i < inventoryPasien.count; i++) {
        printf("%d. %s\n", i + 1, obatList[inventoryPasien.obat_id[i]].nama);
    }
}