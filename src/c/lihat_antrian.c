#include <stdio.h>
#include <string.h>
#include "../header/lihat_antrian.h"
#include "../header/denah.h"
#include "../header/utils.h"
#include "../header/login.h"
#include "../header/user.h"
#include "../header/queue.h"
#include "../header/config.h"

void lihatSemuaAntrian() {
    gambarDenah();

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
                if (r.totalPasien == 0 || strcmp(r.usernamePasien[i], "-") == 0) {
                    printf("  Tidak ada pasien di dalam ruangan saat ini.\n");
                } else {
                    for (int k = 0; k < r.totalPasien; k++) {
                        printf("  %d. %s\n", k + 1, r.usernamePasien[k]);
                    }
                }

                printf("Pasien di antrian:\n");
                Node* cur = r.antrianPasien.front;
                int skip = 0;
                while (skip < r.totalPasien && cur != NULL) {
                    cur = cur->next;
                    skip++;
                }
                if (cur == NULL) {
                    printf("  Tidak ada pasien di antrian saat ini.\n");
                } else {
                    int antriIndex = 1;
                    while (cur != NULL) {
                        printf("  %d. %s\n", antriIndex++, cur->usernamePasien);
                        cur = cur->next;
                    }
                }
            }
        }
    }
}
