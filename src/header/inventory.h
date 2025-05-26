#ifndef INVENTORY_H
#define INVENTORY_H

#define MAX_INVENTORY 100

typedef struct {
    int obat_id[MAX_INVENTORY];
    int count;
} Inventory;

void initInventory(Inventory* inv);
void addInventory(Inventory* inv, int id_obat);
void removeInventory(Inventory* inv, int index);
void printInventory(Inventory inv);

#endif
