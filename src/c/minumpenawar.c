#include "../header/obat.h"
#include "../header/obatPenyakit.h"
#include "../header/penyakit.h"
#include "../header/user.h"
#include "../header/stack.h"
#include "../header/inventory.h"
#include "../header/akubolehpulang.h"
// Yang dicomment hapus aja kalau memang sudah fix (itu buat testing):)

// Global variabel for testing 
// Obat* obatList;
// int obatCount = 2;
// 
// ObatPenyakit* obatPenyakitList;
// int obatPenyakitCount = 2;
// 
// Penyakit* penyakitList;
// int penyakitCount = 1;
// 
// // For testing (fungsinya dari akubolehpulang.c)
// int getIdFromPenyakit(User *pasien) {
//     for (int i = 0; i < penyakitCount; i++) {
//         if (strcmp(pasien->riwayat_penyakit, penyakitList[i].name_penyakit) == 0) {
//             return penyakitList[i].id;
//         }
//     }
//     return -1;
// }
// 
// // For testing (fungsinya dari akubolehpulang.c)
// int checkUrutanObat(User *pasien) {
//     Stack tempPerut = pasien->perut;
//     int urutBenar = 1;
//     int nomorUrutan = 9999;
// 
//     while (!isStackEmpty(tempPerut)) {
//         int idObat = peek(tempPerut);
//         pop(&tempPerut);
// 
//         int urutanNow = -1;
//         for (int i = 0; i < obatPenyakitCount; i++) {
//             if (idObat == obatPenyakitList[i].obat_id &&
//                 getIdFromPenyakit(pasien) == obatPenyakitList[i].penyakit_id) {
//                 urutanNow = obatPenyakitList[i].urutan_minum;
//                 break;
//             }
//         }
// 
//         if (nomorUrutan < urutanNow) {
//             urutBenar = 0;
//             break;
//         }
// 
//         nomorUrutan = urutanNow;
//     }
// 
//     return urutBenar;
// }

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

// int main() {
//     obatList = malloc(sizeof(Obat) * 3);
//     strcpy(obatList[0].nama, "ObatA");
//     obatList[0].id = 1;
//     strcpy(obatList[1].nama, "ObatB");
//     obatList[1].id = 2;
//     strcpy(obatList[2].nama, "ObatC");
//     obatList[2].id = 3;
// 
//     obatPenyakitList = malloc(sizeof(ObatPenyakit) * 3);
//     obatPenyakitList[0].obat_id = 1;
//     obatPenyakitList[0].penyakit_id = 1;
//     obatPenyakitList[0].urutan_minum = 2;
//     obatPenyakitList[1].obat_id = 2;
//     obatPenyakitList[1].penyakit_id = 1;
//     obatPenyakitList[1].urutan_minum = 1;
//     obatPenyakitList[2].obat_id = 3;
//     obatPenyakitList[2].penyakit_id = 1;
//     obatPenyakitList[2].urutan_minum = 3;
// 
//     penyakitList = malloc(sizeof(Penyakit) * 1);
//     penyakitList[0].id = 1;
//     strcpy(penyakitList[0].name_penyakit, "Flu");
// 
//     // Inisialisasi pasien
//     User pasien;
//     pasien.id = 1;
//     strcpy(pasien.riwayat_penyakit, "Flu");
//     pasien.perut.top = -1;
// 
//     // Minum Obat
//     push(&pasien.perut, 2);
//     push(&pasien.perut, 1);
//     push(&pasien.perut, 3);
// 
//     printf("Sebelum minumPenawar:\n");
//     printf("Isi perut: ");
//     for (int i = 0; i <= pasien.perut.top; i++) {
//         printf("%d ", pasien.perut.data[i]);
//     }
//     printf("\n");
// 
//     printf("Inventory pasien (sebelum): ");
//     for (int i = 0; i < inventoryPasien.count; i++) {
//         printf("%d ", inventoryPasien.obat_id[i]);
//     }
// 
//     printf("\n");
// 
//     minumPenawar(&pasien);
// 
//     printf("Setelah minumPenawar:\n");
//     printf("Isi perut:\n ");
//     for (int i = 0; i <= pasien.perut.top + 1; i++) {
//         printf("%d ", pasien.perut.data[i]);
//     }
// 
//     printf("Inventory pasien:\n");
//     for (int i = 0; i < inventoryPasien.count; i++) {
//         printf("%d ", inventoryPasien.obat_id[i]);
//     }
// 
//     return 0;
// } 
//      gcc minumpenawar.c stack.c queue.c inventory.c -o minumpenawar