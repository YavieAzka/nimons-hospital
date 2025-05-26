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
                bool adaPasienDalam = false;
                for (int k = 0; k < kapasitas_ruangan + kapasitas_antrian && k < r.totalPasien; k++) {
                    // WORKAROUND for Room B3 displaying "1. -"
                    // If totalPasien is 1 and that single patient's username is "-",
                    // treat it as if there are no actual patients for display purposes.
                    if (r.totalPasien == 1 && strcmp(r.usernamePasien[k], "-") == 0) {
                        // This will ensure adaPasienDalam is not set to true by this placeholder,
                        // leading to "Tidak ada pasien..." being printed later.
                        continue; 
                    }
                    
                    printf("  %d. %s\n", k + 1, r.usernamePasien[k]);
                    adaPasienDalam = true;
                }

                if (!adaPasienDalam) {
                    printf("  Tidak ada pasien di dalam ruangan saat ini.\n");
                }

                printf("Pasien di antrian:\n");
                bool adaPasienAntrian = false;
                for (int l = kapasitas_ruangan; l < r.totalPasien; l++) {
                    // Similar workaround could be applied here if "-" could appear in queue
                    // and should be ignored, but based on current issue, focusing on "in room".
                    // If the only "queued patient" (after filling capacity) is "-", and totalPasien reflects this.
                    if (r.totalPasien == (kapasitas_ruangan + 1) && strcmp(r.usernamePasien[l], "-") == 0) {
                        continue;
                    }

                    printf("  %d. %s\n", l - kapasitas_ruangan + 1, r.usernamePasien[l]);
                    adaPasienAntrian = true;
                }
                if (!adaPasienAntrian) {
                    printf("  Tidak ada pasien di antrian saat ini.\n");
                }
            }
        }
    }
}