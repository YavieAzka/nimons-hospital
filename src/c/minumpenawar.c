#include "../header/load.h"
#include "../header/obatPenyakit.h"
#include "../header/obat.h"
#include "../header/penyakit.h"
#include "../header/minumpenawar.h"
#include "../header/user.h"
#include "../header/akubolehpulang.h"
#include "../header/stack.h"
#include "../header/inventory.h"

void minumPenawar(User *pasien) {
    char namaObatKeluar[MAX_NAMA_PENYAKIT] = "";
    if(pasien->perut.top == 0) {
        printf("Perut kosong!! Belum ada obat yang dimakan. :O\n");
    } else {
        if (checkUrutanObat(pasien) == 0) {
            int idObatKeluar = peek(pasien->perut);
            pop(&(pasien->perut));
            for(int i = 0; i < obatCount; i++) {
                if(idObatKeluar == obatList[i].id) {
                    strcpy(namaObatKeluar, obatList[i].nama);
                    break;
                }
            }
            //Keluarkan obat dari perut
            printf("Uwekkk :O !!! %s keluar dan kembali ke inventory\n", namaObatKeluar);
            addInventory(idObatKeluar);
        }
    }
}

