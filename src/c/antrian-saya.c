#include "../header/antrian-saya.h"
#include "../header/config.h"
#include "../header/queue.h"
#include <stdio.h>
#include <string.h>

void antrianSaya(User* userNow) {
    if (strcmp(userNow->role, "pasien") != 0) {
        printf("Hmmm... fitur ini cuma bisa dipakai sama pasien ya!\n");
        return;
    }

    int found = 0;

    for (int i = 0; i < panjang_denah_eff; i++) {
        for (int j = 0; j < lebar_denah_eff; j++) {
            Queue q = ruanganList[i][j].antrianPasien;  
            Node* current = q.front;
            int posisi = 1;

            while (current != NULL) {
                if (strcmp(current->usernamePasien, userNow->username) == 0) {
                    printf("\n==== STATUS ANTRIAN KAMU ====\n");
                    printf("Ketemu! Kamu lagi nunggu di ruangan %c%d bareng Dokter %s.\n", 
                           'A' + i, j + 1,
                           ruanganList[i][j].usernameDokter);  
                    printf("Posisimu sekarang di antrian: %d dari %d pasien.\n", posisi, q.length);

                    int kapasitas = kapasitas_ruangan;
                    if (posisi <= kapasitas) {
                        printf("Kamu udah DI DALAM ruangan. Siap-siap ya, giliranmu bentar lagi!\n\n");
                    } else {
                        int antrianLuar = posisi - kapasitas;
                        printf("Kamu masih DI LUAR ruangan. Tunggu %d pasien lagi buat masuk, ya!\n\n", antrianLuar);
                    }

                    found = 1;
                    break;
                }

                current = current->next;
                posisi++;
            }

            if (found) return;
        }
    }

    printf("\nEits, kamu belum ada di antrian mana pun nih!\n");
    printf("Yuk daftar dulu buat check-up lewat command: DAFTAR_CHECKUP\n\n");
}