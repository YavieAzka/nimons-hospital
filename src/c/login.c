#include "../header/user.h"
#include "../header/boolean.h"
//Read user.csv file and store it in users[] array.
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_COMMAND 50

void print_helpMessage_pasien(User usernow){
    printf("HELP ==========================================================================\n");
    printf("Halo %s %s, berikut adalah seluruh fungsi yang dapat kamu akses:\n", usernow.role, usernow.username);
    printf("    1. LOGOUT\n");
    printf("    2. DAFTAR_CHECKUP\n");
    printf("    3. ANTRIAN_SAYA\n");
    printf("    4. MINUM_OBAT\n");
    printf("    5. MINUM_PENAWAR\n");
    printf("    6. DOK_AKU_MAU_PULANG\n");
    printf("    7. LIHAT_DENAH\n");
    printf("    8. LIHAT_RUANGAN\n");
    printf("    9. EXIT\n");
    printf("Footnote: =====================================================================\n");
    printf("    1. Untuk menggunakan aplikasi, silahkan masukkan perintah yang terdaftar.\n");
    printf("    2. Jangan lupa untuk memasukkan input yang valid.\n");

}

void print_helpMessage_dokter(User usernow){
    printf("HELP ==========================================================================\n");
    printf("Halo %s %s, berikut adalah seluruh fungsi yang dapat kamu akses:\n", usernow.role, usernow.username);
    printf("    1. LOGOUT\n");
    printf("    2. LIHAT_ANTRIAN\n");
    printf("    3. DIAGNOSIS\n");
    printf("    4. NGOBATIN\n");
    printf("    5. LIHAT_DENAH\n");
    printf("    6. LIHAT_RUANGAN\n");
    printf("    7. EXIT\n");
    printf("Footnote: =====================================================================\n");
    printf("    1. Untuk menggunakan aplikasi, silahkan masukkan perintah yang terdaftar.\n");
    printf("    2. Jangan lupa untuk memasukkan input yang valid.\n");
}

void print_helpMessage_manager(User usernow){
    printf("HELP ==========================================================================\n");
    printf("Halo %s %s, berikut adalah seluruh fungsi yang dapat kamu akses:\n", usernow.role, usernow.username);
    printf("    1. LOGOUT\n");
    printf("    2. TAMBAH_DOKTER\n");
    printf("    3. ASSIGN_DOKTER\n");
    printf("    4. LIHAT_USER\n");
    printf("    5. CARI_USER\n");
    printf("    6. LIHAT_DENAH\n");
    printf("    7. LIHAT_RUANGAN\n");
    printf("    8. HELP\n");
    printf("    9. EXIT\n");
    printf("Footnote: =====================================================================\n");
    printf("    1. Untuk menggunakan aplikasi, silahkan masukkan perintah yang terdaftar.\n");
    printf("    2. Jangan lupa untuk memasukkan input yang valid.\n");
}

char* help(User userNow){

    if(strcmp(userNow.role, "manager") == 0){
        print_helpMessage_manager(userNow);
    }

    else if(strcmp(userNow.role, "dokter") == 0){
        print_helpMessage_dokter(userNow);
    }

    else if(strcmp(userNow.role, "pasien") == 0){
        print_helpMessage_pasien(userNow);
    }

    else{
        printf("Role tidak valid.\n");
    }

    // get user input
    char* input = (char*)malloc(MAX_COMMAND * sizeof(char));
    scanf("%s", input);
    return input;
}
