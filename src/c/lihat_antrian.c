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
            Ruangan r = ruanganList[i][j]; // Get the room data

            if (r.idDokter != 0) { // Only if a doctor is present
                char namaRuang[4];
                sprintf(namaRuang, "%c%d", 'A' + i, j + 1);

                printf("\n============ %s ============\n", namaRuang);
                printf("Kapasitas  : %d\n", kapasitas_ruangan);
                printf("Dokter     : Dr. %s\n", r.usernameDokter);

                // --- Display patients IN ROOM by iterating the first part of the queue ---
                printf("Pasien di dalam ruangan:\n");
                bool adaPasienDalam = false;
                Node* currentNode = r.antrianPasien.front; // Start from the front of the room's queue
                int pasienDiRuanganCount = 0;

                while (currentNode != NULL && pasienDiRuanganCount < kapasitas_ruangan) {
                    printf("  %d. %s\n", pasienDiRuanganCount + 1, currentNode->usernamePasien);
                    adaPasienDalam = true;
                    currentNode = currentNode->next; // Move to next patient in the overall list
                    pasienDiRuanganCount++;
                }
                if (!adaPasienDalam) {
                    printf("  Tidak ada pasien di dalam ruangan saat ini.\n");
                }

                // --- Display patients IN QUEUE (remaining patients) ---
                // currentNode now points to the first patient actually waiting in queue,
                // or NULL if the queue was exhausted by "Pasien di dalam ruangan".
                printf("Pasien di antrian:\n");
                // Instead of directly using your printQueue (which prints all), we continue iterating:
                bool adaPasienAntrian = false;
                int pasienDiAntrianCount = 0;
                while (currentNode != NULL) {
                    printf("  %d. %s\n", pasienDiAntrianCount + 1, currentNode->usernamePasien);
                    adaPasienAntrian = true;
                    currentNode = currentNode->next;
                    pasienDiAntrianCount++;
                }
                if (!adaPasienAntrian) {
                    printf("  Tidak ada pasien di antrian saat ini.\n");
                }
            }
        }
    }
}