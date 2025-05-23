#include <stdio.h>
#include "minumobat.h"

void minumObat(User* user, Inventory* inv, Stack* perut) {
    if (inv->count == 0) {
        printf("Eh, obatmu kosong loh! Gak ada yang bisa diminum sekarang :)\n");
        return;
    }

    printf("============ DAFTAR OBAT ============\n");
    for (int i = 0; i < inv->count; i++) {
        int id = inv->obat_id[i];
        printf("%d. %s\n", i + 1, obatList[id].nama);
    int pilihan;
    printf("\nPilih nomor obat yang mau kamu minum (1-%d): ", inv->count);
    scanf("%d", &pilihan);

    if (pilihan < 1 || pilihan > inv->count) {
        printf("Waduh! Nomor yang kamu pilih gak ada di daftar :(\n");
        return;
    }

    int id_obat = inv->obat_id[pilihan - 1];
    push(perut, id_obat); 
    printf("🫗 *GLEKGLEKGLEK*... %s berhasil diminum! Rasanya... unik ya!\n", obatList[id_obat].nama);

    removeInventory(inv, pilihan - 1); 
    printf("Inventory diperbarui. Obat %s udah keluar dari kantong ajaib kamu!\n", obatList[id_obat].nama);
}
