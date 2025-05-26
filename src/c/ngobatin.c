#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "../header/user.h"
#include "../header/penyakit.h"
#include "../header/obat.h"
#include "../header/obatPenyakit.h"
#include "../header/ngobatin.h"
#include "../header/config.h"
#include "../header/stack.h"
#include "../header/queue.h"

Ruangan* cariRuanganDokter(const char* usernameDokter) {
    for (int i = 0; i < panjang_denah_eff; i++) {
        for (int j = 0; j < lebar_denah_eff; j++) {
            if (strcmp(ruanganList[i][j].usernameDokter, usernameDokter) == 0) {
                return &ruanganList[i][j];
            }
        }
    }
    return NULL;
}

User* cariUserByUsername(const char* username) {
    for (int i = 0; i < userCount; i++) {
        if (strcmp(users[i].username, username) == 0) {
            return &users[i];
        }
    }
    return NULL;
}

void ngobatin() {
    extern User currentUser;
    if (strcmp(currentUser.role, "dokter") != 0) {
        printf("Maaf ya, fitur ini cuma bisa dipakai sama dokter. Coba panggil dokternya dulu deh!\n");
        return;
    }

    Ruangan* ruanganSaya = cariRuanganDokter(currentUser.username);
    if (ruanganSaya == NULL) {
        printf("Dok, Anda belum ditugaskan di ruangan manapun. Coba minta manager assign dulu ya!\n");
        return;
    }

    if (isEmptyQueue(&ruanganSaya->antrianPasien)) {
        printf("Tidak ada pasien di ruangan saat ini. Silakan tunggu pasien berikutnya.\n");
        return;
    }

    int idPasien;
    char usernamePasien[MAX_USERNAME];
    peekFront(&ruanganSaya->antrianPasien, &idPasien, usernamePasien);

    User* pasien = cariUserByUsername(usernamePasien);
    if (pasien == NULL) {
        printf("Data pasien dengan username %s tidak ditemukan. Ada yang aneh nih!\n", usernamePasien);
        return;
    }

    if (strcmp(pasien->riwayat_penyakit, "") == 0) {
        printf("Pasien %s belum didiagnosis, dok. Tolong lakukan diagnosis dulu sebelum ngobatin!\n", pasien->username);
        return;
    }

    if (!isStackEmpty(pasien->perut)) {
        printf("Pasien %s masih dalam proses pengobatan sebelumnya. Harap tunggu hingga selesai dan pulang dulu ya.\n", pasien->username);
        return;
    }

    int id_penyakit = -1;
    for (int i = 0; i < penyakitCount; i++) {
        if (strcmp(penyakitList[i].name_penyakit, pasien->riwayat_penyakit) == 0) {
            id_penyakit = penyakitList[i].id;
            break;
        }
    }

    if (id_penyakit == -1) {
        printf("Wah, penyakit '%s' tidak dikenali dalam database penyakit. Coba dicek lagi ya.\n", pasien->riwayat_penyakit);
        return;
    }

    int found = 0;
    for (int i = 0; i < obatPenyakitCount; i++) {
        if (obatPenyakitList[i].id_penyakit == id_penyakit) {
            printf("\nDokter sedang mengobati pasien %s.\n", pasien->username);
            printf("Pasien terdiagnosis penyakit %s\n", pasien->riwayat_penyakit);
            printf("Obat yang harus diberikan:\n");

            initStack(&pasien->perut); 

            for (int j = 0; j < obatPenyakitList[i].jumlah_obat; j++) {
                int id_obat = obatPenyakitList[i].id_obat[j];

                push(&pasien->perut, id_obat);

                int foundObat = 0;
                for (int k = 0; k < obatCount; k++) {
                    if (obatList[k].id == id_obat) {
                        printf(">> Obat ke-%d: %s\n", j + 1, obatList[k].nama);
                        foundObat = 1;
                        break;
                    }
                }
                if (!foundObat) {
                    printf(">> Obat ke-%d: [ID %d tidak ditemukan!]\n", j + 1, id_obat);
                }
            }

            printf("\nPastikan pasien meminum obat sesuai urutan ya, dok!\n");
            found = 1;
            break;
        }
    }

    if (!found) {
        printf("Belum ada data obat untuk penyakit '%s'. Silakan tambahkan dulu di database, dok!\n", pasien->riwayat_penyakit);
    }
}