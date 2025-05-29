#include <stdio.h>
#include <string.h>
#include "../header/exit.h"
#include "../header/save.h"

void exit_program() {
    char pilihan[10];

    do
    {
        printf("Apakah Anda ingin menyimpan data sebelum keluar? (ya/tidak): ");
        scanf("%s", pilihan);
    } while (strcmp(pilihan, "ya") != 0 && strcmp(pilihan, "tidak") != 0);    

    if (strcmp(pilihan, "ya") == 0) {
        char folder_name[100];
        printf("Masukkan nama folder untuk menyimpan data: ");
        scanf("%s", folder_name);
        save_data(folder_name);
    }

    printf("Program dihentikan. Semua dokter, pasien, dan manajer telah meninggalkan rumah sakit.\n");
}
