#include <stdio.h>
#include "inventory.h"
#include "obat.h"

void initInventory(Inventory* inv) {
    inv->count = 0;
}

void addInventory(Inventory* inv, int id_obat) {
    if (inv->count < MAX_INVENTORY) {
        inv->obat_id[inv->count++] = id_obat;
    }
}

void removeInventory(Inventory* inv, int index) {
    if (index >= 0 && index < inv->count) {
        for (int i = index; i < inv->count - 1; i++) {
            inv->obat_id[i] = inv->obat_id[i + 1];
        }
        inv->count--;
    }
}

void printInventory(Inventory inv) {
    printf("== INVENTORY ==\n");
    for (int i = 0; i < inv.count; i++) {
        printf("%d. %s\n", i + 1, obatList[inv.obat_id[i]].nama);
    }
}
