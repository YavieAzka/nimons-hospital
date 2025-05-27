#include <stdio.h>
#include "../header/minumobat.h"

void minumObat(User* user, Stack* perut) {
    if (inventoryPasien.count == 0) {
        printf(">>> MINUM_OBAT\n");
        printf("Eh, obatmu kosong loh! Gak ada yang bisa diminum sekarang.\n");
        return;
    }

    printf(">>> MINUM_OBAT\n");
    printf("============ DAFTAR OBAT ============\n");
    for (int i = 0; i < inventoryPasien.count; i++) {
        int id = inventoryPasien.obat_id[i];
        printf("%d. %s\n", i + 1, obatList[id].nama);
    }

    int pilihan;
    printf("\nPilih nomor obat yang mau kamu minum (1-%d): ", inventoryPasien.count);

    if (scanf("%d", &pilihan) != 1) {
        printf("Input tidak valid! Masukkan angka ya.\n");
        while (getchar() != '\n'); 
        return;
    }

    if (pilihan < 1 || pilihan > inventoryPasien.count) {
        printf("Waduh! Nomor yang kamu pilih gak ada di daftar!\n");
        return;
    }

    int id_obat = inventoryPasien.obat_id[pilihan - 1];
    push(perut, id_obat);
    printf("*GLEKGLEKGLEK*... %s berhasil diminum! Rasanya... unik ya^^\n", obatList[id_obat].nama);

    removeInventory(pilihan - 1);
    printf("Inventory diperbarui. Obat %s udah keluar dari kantong ajaib kamu!\n", obatList[id_obat].nama);
}