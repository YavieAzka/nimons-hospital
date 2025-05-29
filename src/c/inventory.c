#include <stdio.h>
#include "../header/inventory.h"
#include "../header/obat.h"
#include "../header/config.h"
InventoryPasien inventoryPasien;

void removeInventoryByUser(InventoryPasien* inv, int index) {
    for (int i = index; i < inv->count - 1; i++) {
        inv->obat_id[i] = inv->obat_id[i + 1];
    }
    inv->count--;
}

InventoryPasien* getInventoryByUser(User* user) {
    for (int i = 0; i < jumlah_inventory; i++) {
        if (daftar_inventory[i].pasien_id == user->id) {
            return &daftar_inventory[i];
        }
    }
    return NULL;
}

void searchJumlahInventory(int* jumlahInventory){
    *jumlahInventory = 0;
    for (int i = 0; i < jumlah_inventory; i++) {
        if (daftar_inventory[i].count > 0) {
            (*jumlahInventory)++;
        }
    }
}
// Fungsi untuk menginisialisasi inventory pasien

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