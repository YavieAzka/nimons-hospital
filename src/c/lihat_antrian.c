#include <stdio.h>
#include <string.h>
#include "../header/lihat_antrian.h"
#include "../header/denah.h"
#include "../header/utils.h"
#include "../header/login.h"
#include "../header/user.h"
#include "../header/queue.h"
#include "../header/config.h"
#include "../header/ruangan.h"

void lihatSemuaAntrian() {
    gambarDenah(); // Menampilkan grid denah ruangan

    for (int i = 0; i < panjang_denah; i++) {
        for (int j = 0; j < lebar_denah; j++) {
            Ruangan r = ruanganList[i][j];

            if (r.idDokter != 0) {
                char namaRuang[4];
                sprintf(namaRuang, "%c%d", 'A' + i, j + 1);

                printf("\n============ %s ============\n", namaRuang);
                printf("Kapasitas  : %d\n", kapasitas_ruangan);
                printf("Dokter     : Dr. %s\n", r.usernameDokter);

                printf("Pasien di dalam ruangan:\n");

                Node* cur = r.antrianPasien.front;
                int index = 0;
                bool adaPasienDalam = false;

                // Pasien dalam ruangan: index < kapasitas_ruangan
                while (cur != NULL && index < kapasitas_ruangan) {
                    printf("  %d. %s\n", index + 1, cur->usernamePasien);
                    adaPasienDalam = true;
                    cur = cur->next;
                    index++;
                }

                if (!adaPasienDalam) {
                    printf("  Tidak ada pasien di dalam ruangan saat ini.\n");
                }

                printf("Pasien di antrian:\n");
                bool adaPasienAntrian = false;
                int antriIndex = 1;

                // Sisanya dianggap sebagai pasien di antrian
                while (cur != NULL) {
                    printf("  %d. %s\n", antriIndex++, cur->usernamePasien);
                    adaPasienAntrian = true;
                    cur = cur->next;
                }

                if (!adaPasienAntrian) {
                    printf("  Tidak ada pasien di antrian saat ini.\n");
                }
            }
        }
    }
}