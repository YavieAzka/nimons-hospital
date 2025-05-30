#include <stdio.h>
#include "../header/minum-obat.h"
#include "../header/inventory.h"
#include "../header/user.h"
#include "../header/obat.h"
#include "../header/config.h"
#include "../header/load.h"

char* namaObat(int id){
    for (int i = 0; i < obatCount; i++)
    {
        if (obatList[i].id == id)
        {
            return obatList[i].nama;
        }
    }
    return "";
}

void minumObat(User* user) {
    InventoryPasien* inv = getInventoryByUser(user);
    int idx = getUserIndex(user->username, users, userCount);

    if (inv == NULL || inv->count == 0) {
        printf("Eh, obatmu kosong loh! Gak ada yang bisa diminum sekarang :)\n");
        return;
    }

    printf("============ DAFTAR OBAT ============\n");
    for (int i = 0; i < inv->count; i++) {
        int id = inv->obat_id[i];
        if (strcmp(namaObat(id), "") != 0) {
            printf("%d. %s\n", i + 1, namaObat(id));
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
    push(&users[idx].perut, id_obat);  // akses langsung ke stack dalam user
    printf("*GLEKGLEKGLEK*... %s berhasil diminum! Rasanya... unik ya^^\n", namaObat(id_obat));
    
    removeInventoryByUser(inv, pilihan - 1);
    printf("Inventory diperbarui. Obat %s udah keluar dari kantong ajaib kamu!\n", namaObat(id_obat));
}