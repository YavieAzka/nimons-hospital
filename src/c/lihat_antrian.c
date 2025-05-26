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
            int k;
            if (r.idDokter != 0) {
                char namaRuang[4];
                sprintf(namaRuang, "%c%d", 'A' + i, j + 1);

                printf("\n============ %s ============\n", namaRuang);
                printf("Kapasitas  : %d\n", kapasitas_ruangan);
                printf("Dokter     : Dr. %s\n", r.usernameDokter);

                printf("Pasien di dalam ruangan:\n");
                bool adaPasienDalam = false;
                for (k = 0; k < kapasitas_ruangan && k < r.totalPasien; k++) {
                    if (r.totalPasien == 1 && strcmp(r.usernamePasien[k], "-") == 0) {
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
                for (int l = k; l < r.totalPasien; l++) {
                    
                    // This check is for the B3-like scenario where a single "-" might be the first in queue
                    // For A1, if totalPasien is 5, this 'if' won't prevent valid queue display
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