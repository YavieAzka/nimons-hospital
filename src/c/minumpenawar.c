#include "../header/obat.h"
#include "../header/obatPenyakit.h"
#include "../header/penyakit.h"
#include "../header/user.h"
#include "../header/stack.h"
#include "../header/inventory.h"
#include "../header/minum-obat.h"
#include "../header/akubolehpulang.h"
#include "../header/load.h"

void addInventoryByUser(InventoryPasien* inv, int id) {
    inv->obat_id[inv->count] = id;
    inv->count++;
}
void minumPenawar(User *user) {
    InventoryPasien* inv = getInventoryByUser(user);
    int idx = getUserIndex(user->username, users, userCount);

    if (strcmp(users[idx].riwayat_penyakit, "Sehat") == 0) {
        printf("Kamu Boleh Pulang, Segera ke pulang DOK!!\n");
        return;
    }
    
    char namaObatKeluar[MAX_NAMA_PENYAKIT];

    if(inv == NULL) {
        printf("Kamu belum menerima obat dari dokter. Tidak boleh meminta obat penawar!! >:)\n");
    } else {
        if(users[idx].perut.top == -1) {
            printf("Perut kosong!! Belum ada obat yang dimakan. >:)\n");
        } else {
            int idObatKeluar = peek(users[idx].perut);
            pop(&(users[idx].perut));
            // Cari nama obat berdasarkan ID
            strcpy(namaObatKeluar, namaObat(idObatKeluar));
            //Keluarkan obat dari perut
            printf("Uwekkk :O !!!\nInventory diperbarui. Obat %s keluar dan kembali ke kantong ajaib kamu!\n", namaObatKeluar);
            addInventoryByUser(inv,idObatKeluar);
        
        }
    }
}
