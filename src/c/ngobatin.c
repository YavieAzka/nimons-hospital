#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "../header/boolean.h"
#include "../header/user.h"
#include "../header/penyakit.h"
#include "../header/obat.h"
#include "../header/obatPenyakit.h"
#include "../header/ngobatin.h"
#include "../header/config.h"
#include "../header/queue.h"
#include "../header/inventory.h"

void ngobatin(User currentUser) {
    
    if (strcmp(currentUser.role, "dokter") != 0) {
        printf("Maaf ya, fitur ini cuma bisa dipakai sama dokter. Coba panggil dokternya dulu deh!\n");
        return;
    }

    // Cari ruangan tempat dokter bertugas
    Ruangan* ruanganDokter = NULL;
    for (int i = 0; i < panjang_denah; i++) {
        for (int j = 0; j < lebar_denah; j++) {
            if (ruanganList[i][j].idDokter == currentUser.id) {
                ruanganDokter = &ruanganList[i][j];
                break;
            }
        }
        if (ruanganDokter != NULL) break;
    }

    if (ruanganDokter == NULL) {
        printf("Dokternya belum ditempatkan di ruangan mana pun. Tolong assign dulu ya!\n");
        return;
    }

    if (isEmptyQueue(&ruanganDokter->antrianPasien)) {
        printf("Belum ada pasien nih di antrian ruangan dokter '%s'. Santai dulu dok!\n", currentUser.username);
        return;
    }

    // Ambil pasien dari antrian paling depan
    int idPasien;
    char usernamePasien[MAX_USERNAME];
    peekFront(&ruanganDokter->antrianPasien, &idPasien, usernamePasien);

    User* target = NULL;
    for (int i = 0; i < userCount; i++) {
        if (users[i].id == idPasien) {
            target = &users[i];
            break;
        }
    }

    if (target == NULL) {
        printf("Hmm... pasien di antrian nggak ketemu di database. Ada yang janggal nih, dok.\n");
        return;
    }

    if (strcmp(target->riwayat_penyakit, "") == 0) {
        printf("Pasien ini belum ada diagnosis penyakit, dok. Kasih diagnosis dulu ya biar bisa dikasih obat yang tepat.\n");
        return;
    }

    int id_penyakit = -1;
    for (int i = 0; i < penyakitCount; i++) {
        if (strcmp(penyakitList[i].name_penyakit, target->riwayat_penyakit) == 0) {
            id_penyakit = penyakitList[i].id;
            break;
        }
    }

    if (id_penyakit == -1) {
        printf("Wah, nama penyakit '%s' nggak ada di database kita, dok. Coba dicek lagi, mungkin typo.\n", target->riwayat_penyakit);
        return;
    }

    // Ambil semua obat untuk penyakit tersebut
    typedef struct {
        int urutan;
        int id_obat;
    } ObatUntukPenyakit;

    ObatUntukPenyakit list_obat[50];
    int count_obat = 0;

    for (int i = 0; i < obatPenyakitCount; i++) {
        if (obatPenyakitList[i].penyakit_id == id_penyakit) {
            list_obat[count_obat].id_obat = obatPenyakitList[i].obat_id;
            list_obat[count_obat].urutan = obatPenyakitList[i].urutan_minum;
            count_obat++;
        }
    }

    if (count_obat == 0) {
        printf("Sepertinya belum ada data obat untuk penyakit '%s'. Coba input dulu di sistem ya, dok!\n", target->riwayat_penyakit);
        return;
    }

    // Urutkan berdasarkan urutan minum
    for (int i = 0; i < count_obat - 1; i++) {
        for (int j = 0; j < count_obat - i - 1; j++) {
            if (list_obat[j].urutan > list_obat[j + 1].urutan) {
                ObatUntukPenyakit temp = list_obat[j];
                list_obat[j] = list_obat[j + 1];
                list_obat[j + 1] = temp;
            }
        }
    }

    // Cari atau buat inventory pasien
    InventoryPasien* inv = NULL;
    for (int i = 0; i < jumlah_inventory; i++) {
        if (daftar_inventory[i].pasien_id == target->id) {
            inv = &daftar_inventory[i];
            break;
        }
    }

    if (inv == NULL) {
        inv = &daftar_inventory[jumlah_inventory];
        inv->pasien_id = target->id;
        inv->count = 0;
        jumlah_inventory++;
    }
    
    printf("\nPasien '%s' terdiagnosis menderita %s.\n", target->username, target->riwayat_penyakit);
    printf("Berikut daftar obat yang harus diberikan, urutannya jangan sampai kebalik ya!\n\n");

    for (int i = 0; i < count_obat; i++) {
        int id_obat = list_obat[i].id_obat;
        inv->obat_id[inv->count++] = id_obat;

        int foundObat = 0;
        for (int k = 0; k < obatCount; k++) {
            if (obatList[k].id == id_obat) {
                printf(">> Obat ke-%d: %s\n", i + 1, obatList[k].nama);
                foundObat = 1;
                break;
            }
        }
        if (!foundObat) {
            printf(">> Obat ke-%d: [Data obat dengan ID %d nggak ditemukan, ada yang janggal nih!]\n", i + 1, id_obat);
        }
    }

    // Hapus pasien dari antrian
    int temp_id;
    char temp_user[MAX_USERNAME];
    dequeue(&ruanganDokter->antrianPasien, &temp_id, temp_user);

    printf("\nPastikan obat diberikan satu per satu sesuai urutan di atas ya. Semangat menyembuhkan pasien!\n");
}
