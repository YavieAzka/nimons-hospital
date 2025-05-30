#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../header/exit.h"
#include "../header/save.h"

void exit_program() {
    char pilihan[10];
    do
    {
        printf("Apakah Anda ingin menyimpan data sebelum keluar? (ya/tidak): ");
        scanf("%9s", pilihan);
    } while (strcmp(pilihan, "ya") != 0 && strcmp(pilihan, "tidak") != 0);
     // Gunakan %9s agar tidak melebihi buffer

    if (strcmp(pilihan, "ya") == 0) {
        char folder_name[100];
        printf("Masukkan nama folder untuk menyimpan data: ");
        getchar(); // Membaca newline tersisa dari scanf sebelumnya
        fgets(folder_name, sizeof(folder_name), stdin);

        // Hapus newline '\n' dari akhir input jika ada
        size_t len = strlen(folder_name);
        if (len > 0 && folder_name[len - 1] == '\n') {
            folder_name[len - 1] = '\0';
        }

        save_data(folder_name);
    }

    printf("Program dihentikan. Semua dokter, pasien, dan manajer telah meninggalkan rumah sakit.\n");
}



// #include <stdio.h>
// #include <stdlib.h>
// #include <string.h>
// #include "../header/exit.h"
// #include "../header/save.h"

// void exit_program() {
//     char pilihan[10];
//     printf("Apakah Anda ingin menyimpan data sebelum keluar? (ya/tidak): ");
//     scanf("%s", pilihan);

//     if (strcmp(pilihan, "ya") == 0) {
//         char folder_name[100];
//         printf("Masukkan nama folder untuk menyimpan data: ");
//         scanf("%s", folder_name);
//         save_data(folder_name);
//     }

//     printf("Program dihentikan. Semua dokter, pasien, dan manajer telah meninggalkan rumah sakit.\n");
// }
