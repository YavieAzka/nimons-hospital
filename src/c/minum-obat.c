#include <stdio.h>
#include "../header/minum-obat.h"
#include "../header/inventory.h"
#include "../header/user.h"
#include "../header/obat.h"
#include "../header/config.h"

InventoryPasien* getInventoryByUser(User* user) {
    for (int i = 0; i < jumlah_inventory; i++) {
        if (daftar_inventory[i].pasien_id == user->id) {
            return &daftar_inventory[i];
        }
    }
    return NULL;
}

void removeInventoryByUser(InventoryPasien* inv, int index) {
    for (int i = index; i < inv->count - 1; i++) {
        inv->obat_id[i] = inv->obat_id[i + 1];
    }
    inv->count--;
}

void minumObat(User* user) {
    InventoryPasien* inv = getInventoryByUser(user);

    printf(">>> MINUM_OBAT\n");

    if (inv == NULL || inv->count == 0) {
        printf("Eh, obatmu kosong loh! Gak ada yang bisa diminum sekarang :)\n");
        return;
    }

    printf("============ DAFTAR OBAT ============\n");
    for (int i = 0; i < inv->count; i++) {
        int id = inv->obat_id[i];
        if (id >= 0 && id < obatCount) {
            printf("%d. %s\n", i + 1, obatList[id].nama);
        } else {
            printf("%d. [Obat tidak dikenal - ID %d]\n", i + 1, id);
        }
    }

    int pilihan;
    printf("\nPilih nomor obat yang mau kamu minum (1-%d): ", inv->count);

    if (scanf("%d", &pilihan) != 1) {
        printf("Input tidak valid! Masukkan angka ya.\n");
        while (getchar() != '\n');
        return;
    }

    if (pilihan < 1 || pilihan > inv->count) {
        printf("Waduh! Nomor yang kamu pilih gak ada di daftar!\n");
        return;
    }

    int id_obat = inv->obat_id[pilihan - 1];
    push(&user->perut, id_obat);  // akses langsung ke stack dalam user
    printf("*GLEKGLEKGLEK*... %s berhasil diminum! Rasanya... unik ya^^\n", obatList[id_obat].nama);

    removeInventoryByUser(inv, pilihan - 1);
    printf("Inventory diperbarui. Obat %s udah keluar dari kantong ajaib kamu!\n", obatList[id_obat].nama);
}