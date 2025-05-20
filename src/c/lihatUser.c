#include "stdio.h"
#include "string.h"
#include "../header/user.h"
#include "../header/lihatUser.h"
#include "../header/help.h"
#include "../header/login.h"
#include "../header/lihatUser.h"
#include "../header/load.h"

void sortAscID(User* users, int userCount) {
    User temp;

    for(int i = 0; i < userCount; i++) {
        for(int j = 0; j < userCount - i - 1; j++) {
            if(users[j].id > users[j+1].id) {
                temp = users[j];
                users[j] = users[j+1];
                users[j+1] = temp;
            }
        }
    }
} 

//Prosedur untuk mengurutkan berdasarkan ID dan Descending
void sortDescID(User* users, int userCount) {
    User temp;

    for(int i = 0; i < userCount; i++) {
        for(int j = 0; j < userCount - i - 1; j++) {
            if(users[j].id < users[j+1].id) {
                temp = users[j];
                users[j] = users[j+1];
                users[j+1] = temp;
            }
        }
    }
}

//Prosedur untuk mengurutkan berdasarkan Nama dan Ascending
void sortAscNama(User* users, int userCount) {
    User temp;

    for(int i = 0; i < userCount; i++) {
        for(int j = 0; j < userCount - i - 1; j++) {
            if(strcasecmp(users[j].username, users[j+1].username) > 0) {
                temp = users[j];
                users[j] = users[j+1];
                users[j+1] = temp;
            }
        }
    }
}

//Prosedur untuk mengurutkan berdasarkan Nama dan Descending
void sortDescNama(User* users, int userCount) {
    User temp;

    for(int i = 0; i < userCount; i++) {
        for(int j = 0; j < userCount - i - 1; j++) {
            if(strcasecmp(users[j].username, users[j+1].username) < 0) {
                temp = users[j];
                users[j] = users[j+1];
                users[j+1] = temp;
            }
        }
    }
}

//Prosedur untuk menerima input pilihan sort dan melakukan sort
void urutanSort(User* users, int userCount) {
    int pilihanSort;
    int pilihanPengurutan;

    //Pilih sort berdasarkan ID / Nama
    printf("Urutkan berdasarkan? (ID / Nama)\n");
    printf("    1. ID\n");
    printf("    2. Nama\n");

    for(;;) {
        printf(">>> ");
        scanf("%d", &pilihanSort);
        if(pilihanSort == 1) {
            break;

        } else if (pilihanSort == 2){
            break;

        } else {
            printf("Input tidak Valid. Silahkan ketik ulang\n");
        }
    }

    //Pilih sort urut ASC atau DESC 
    printf("Urutkan Sort? (ASC / DESC)\n");
    printf("    1. ASC (A-Z)\n");
    printf("    2. DESC (Z-A)\n");

    for(;;) {
        printf(">>> ");
        scanf("%d", &pilihanPengurutan);
        if(pilihanPengurutan == 1) {
            break;

        } else if (pilihanPengurutan == 2){
            break;

        } else {
            printf("Input tidak Valid. Silahkan ketik ulang\n");
        }
    }

    //Sort berdasarkan input yang dimasukkan
    if (pilihanSort == 1 && pilihanPengurutan == 1) {
        sortAscID(users, userCount); 
    } else if (pilihanSort == 2 && pilihanPengurutan == 1) {
        sortAscNama(users, userCount);
    } else if (pilihanSort == 1 && pilihanPengurutan == 2) {
        sortDescID(users, userCount);
    } else {
        sortDescNama(users, userCount);
    }
}

//Prosedur untuk menampilkan data User / Pasien / Dokter
void interfaceUser(User* users, char *command, int userCount){
    if (strcmp(command, "LIHAT_USER") == 0 ) {
        printf("========================== DATA USER ==========================\n");
        printf("+-----+---------------------+----------------+----------------+\n");
        printf("| ID  | %-18s  | %-13s  | %-13s  |\n", "Nama", "Role", "Penyakit");
        printf("+-----+---------------------+----------------+----------------+\n");
        for (int i = 0; i < userCount; i++) {
            printf("| %-3d | %-18s  | %-13s  | %-13s  |\n", users[i].id, users[i].username, users[i].role, users[i].riwayat_penyakit);
            printf("+-----+---------------------+----------------+----------------+\n");
        }
    } else if (strcmp(command, "LIHAT_PASIEN") == 0 ) {
        printf("=============== DATA PASIEN ================\n");
        printf("+-----+--------------------+---------------+\n");
        printf("| ID  | %-18s | %-13s |\n", "Nama", "Penyakit");
        printf("+-----+--------------------+---------------+\n");
        for (int i = 0; i < userCount; i++) {
            if (strcmp(users[i].role, "pasien") == 0) {
                printf("| %-3d | %-18s | %-13s |\n", users[i].id, users[i].username, users[i].riwayat_penyakit);
                printf("+-----+--------------------+---------------+\n");
            }
        }
    } else if (strcmp(command, "LIHAT_DOKTER") == 0 ) {
        printf("======== DATA DOKTER =======\n");
        printf("+-----+--------------------+\n");
        printf("| ID  | %-18s |\n", "Nama");
        printf("+-----+--------------------+\n");
        for (int i = 0; i < userCount; i++) {
            if (strcmp(users[i].role, "dokter") == 0) {
                printf("| %-3d | %-18s |\n", users[i].id, users[i].username);
                printf("+-----+--------------------+\n");
            }
        }
    }
}

//Prosedur untuk menampilkan data user yang sudah di sort
void lihatUser(char *command) {
    urutanSort(users, userCount);
    interfaceUser(users, command, userCount);
}

//Prosedur untuk menampilkan data pasien yang sudah di sort
void lihatPasien(char *command) {
    lihatUser(command); 
}

//Prosedur untuk menampilkan data dokter yang sudah di sort
void lihatDokter(char *command) {
    lihatUser(command); 
}
