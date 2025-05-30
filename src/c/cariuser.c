#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "../header/login.h"
#include "../header/cariuser.h"

#define MAX_USERNAME_LENGTH 15
#define MAX_ROLE_LENGTH 15
#define MAX_PENYAKIT_LENGTH 20

extern User users[MAX_USERS];
extern int userCount;
void printHorizontalLine() {
    printf("+-----+---------------+---------------+--------------------+\n");
}

char toLowerChar(char c) {
    if (c >= 'A' && c <= 'Z') {
        return c + ('a' - 'A'); // atau c + 32
    }
    return c;
}

void strToLower(const char* src, char* dest) {
    int i = 0;
    while (src[i] != '\0') {
        if (src[i] >= 'A' && src[i] <= 'Z') {
            dest[i] = src[i] + ('a' - 'A');  // konversi ke huruf kecil
        } else {
            dest[i] = src[i];  // karakter lain tidak diubah
        }
        i++;
    }
    dest[i] = '\0'; // null-terminator
}

// Fungsi perbandingan username untuk qsort (ascending)
int compareUsername(const void* a, const void* b) {
    const User* userA = (const User*)a;
    const User* userB = (const User*)b;
    return strcmp(userA->username, userB->username);
}

int binarySearchUsername(User* users, int userCount, const char* target) {
    int left = 0, right = userCount - 1;

    char lower_target[128];
    strToLower(target, lower_target);

    while (left <= right) {
        int mid = (left + right) / 2;

        char lowered_mid[128];
        strToLower(users[mid].username, lowered_mid);

        int cmp = strcmp(lowered_mid, lower_target);
        if (cmp == 0) return mid;
        else if (cmp < 0) left = mid + 1;
        else right = mid - 1;
    }

    return -1; // not found
}

void printHeader(){
    printHorizontalLine();
    printf("| ID  | %-13s | %-13s | %-18s |\n", "Nama", "Role", "Penyakit");
    printHorizontalLine();
}

void printUser_general(User U){
    // Mengeprint user jika pengguna menggunakan perintah CARI_USER
    printHeader();
    
    char formatted_username[MAX_USERNAME_LENGTH + 1]; // +1 untuk null terminator
    char formatted_role[MAX_ROLE_LENGTH + 1];
    char formatted_penyakit[MAX_PENYAKIT_LENGTH + 1];
    
    // Copy dan truncate jika terlalu panjang
    strncpy(formatted_username, U.username, MAX_USERNAME_LENGTH);
    formatted_username[MAX_USERNAME_LENGTH] = '\0';
    
    strncpy(formatted_role, U.role, MAX_ROLE_LENGTH);
    formatted_role[MAX_ROLE_LENGTH] = '\0';
    
    if (strcmp(U.role, "pasien") == 0) {
        strncpy(formatted_penyakit, U.riwayat_penyakit, MAX_PENYAKIT_LENGTH);
        formatted_penyakit[MAX_PENYAKIT_LENGTH] = '\0';
        printf("| %-3d | %-13s | %-13s | %-18s |\n", 
               U.id, formatted_username, formatted_role, formatted_penyakit);
    } else {
        printf("| %-3d | %-13s | %-13s | %-18s |\n", 
               U.id, formatted_username, formatted_role, "-");
    }
    
    printHorizontalLine();
    
}

void printPasien(User U){
    char formatted_username[MAX_USERNAME_LENGTH + 1];
    char formatted_penyakit[MAX_PENYAKIT_LENGTH + 1];
    
    strncpy(formatted_username, U.username, MAX_USERNAME_LENGTH);
    formatted_username[MAX_USERNAME_LENGTH] = '\0';
    
    strncpy(formatted_penyakit, U.riwayat_penyakit, MAX_PENYAKIT_LENGTH);
    formatted_penyakit[MAX_PENYAKIT_LENGTH] = '\0';
    
    printf("| %-3d | %-18s | %-13s |\n", 
           U.id, formatted_username, formatted_penyakit);
}



void printPilihan(){
    printf("Cari berdasarkan:\n");
    printf("1. ID\n");
    printf("2. Nama\n");
    printf("Masukkan angka pilihan: \n");
    printf(">>> ");
    
}

void printDokter(User U){
    char formatted_username[MAX_USERNAME_LENGTH];
    
    strncpy(formatted_username, U.username, MAX_USERNAME_LENGTH);
    formatted_username[MAX_USERNAME_LENGTH] = '\0';
    printf("+-----+---------------+\n");
    printf("| ID  | %-13s |\n", "Nama");
    printf("+-----+---------------+\n");
    printf("| %-3d | %-13s |\n", U.id, formatted_username);
    printf("+-----+---------------+\n");
}

void cariPasien(){
    int userChoice;

    printf("Cari berdasarkan:\n");
    printf("1. ID\n");
    printf("2. Nama\n");
    printf("3. Penyakit\n");
    printf("Masukkan angka pilihan: \n");
    printf(">>> ");

    scanf("%d", &userChoice);

    User *usersTemp = (User *)malloc(userCount * sizeof(User));
    for(int i = 0; i < userCount; i++){
        usersTemp[i] = users[i];
    }

    if(userChoice == 1){ // Search by ID
        int idx;
        printf("Cari ID: ");
        scanf("%d", &idx);
        bool found = false;
        printf("Pengguna dengan ID %d:\n", idx);
        for(int i = 0; i < userCount; i++){
            if(users[i].id == idx){
                printUser_general(users[i]);
                found = true;
                break;
            }
        }
        if(!found) printf("Pasien dengan ID '%d' tidak ditemukan.\n", idx);   

    }
    
    else if(userChoice == 2){ // Search by Username
        char targetUsername[128];
        printf("Cari Username: ");
        scanf("%s", targetUsername);

        // Step 1: Urutkan array berdasarkan username
        qsort(usersTemp, userCount, sizeof(User), compareUsername);

        // Step 2: Binary search
        int index = binarySearchUsername(usersTemp, userCount, targetUsername);

        if (index != -1) {
            printf("Pasien dengan ID %d:\n", index);
            printPasien(usersTemp[index]);
        } else {
            printf("Pasien dengan username '%s' tidak ditemukan.\n", targetUsername);
        }
    }

    else if(userChoice == 3){  // Search by riwayat_penyakit
        char penyakit[32];
        printf("Cari penyakit: ");
        int c;
        while ((c = getchar()) != '\n' && c != EOF);

        // Ambil input penyakit
        fgets(penyakit, sizeof(penyakit), stdin);
        penyakit[strcspn(penyakit, "\n")] = '\0';  // Hapus newline dari fgets
        int countPenyakit = 0;
        for(int i = 0; i < userCount; i++){
            if(strcmp(users[i].riwayat_penyakit, penyakit) == 0){
                if(countPenyakit == 0){
                    printf("+-----+--------------------+---------------+\n");
                    printf("| ID  | %-18s | %-13s |\n", "Nama", "Penyakit");
                    printf("+-----+--------------------+---------------+\n");
                    countPenyakit++;
                }
                printPasien(users[i]);
                printf("+-----+--------------------+---------------+\n");
            }
        }
        if(countPenyakit == 0){
            printf("Pasien dengan penyakit %s tidak ditemukan\n", penyakit);
        }
    }
    else{
        printf("Pilihan tidak valid. Mohon masukkan pilihan yang benar!.\n");
    }
    free(usersTemp);
    
}

void cariDokter(){
    int userChoice;

    printf("Cari berdasarkan:\n");
    printf("1. ID\n");
    printf("2. Nama\n");
    printf("Masukkan angka pilihan: \n");
    printf(">>> ");

    scanf("%d", &userChoice);
    User *usersTemp = (User *)malloc(userCount * sizeof(User));
    for(int i = 0; i < userCount; i++){
        usersTemp[i] = users[i];
    }

    if(userChoice == 1){ // Search by ID
        int idx;
        printf("Cari ID: ");
        scanf("%d", &idx);
        bool found = false;
        for(int i = 0; i < userCount; i++){
            if(users[i].id == idx && strcmp(users[i].role, "dokter") == 0){
                printf("Dokter dengan ID %d:\n", idx);
                printUser_general(users[i]);
                found = true;
                return;
            }
        }
        if(!found) printf("Dokter dengan ID '%d' tidak ditemukan.\n", idx);   

    }

    
    else if(userChoice == 2){ // Search by Username
        char targetUsername[128];
        printf("Cari Username: ");
        scanf("%s", targetUsername);

        // Step 1: Urutkan array berdasarkan username
        qsort(usersTemp, userCount, sizeof(User), compareUsername);

        // Step 2: Binary search
        int index = binarySearchUsername(usersTemp, userCount, targetUsername);
        
        if (index!= -1 && strcmp(usersTemp[index].role,"dokter") == 0) {
            printf("Menampilkan data Dokter dengan nama %s:\n", usersTemp[index].username);
            printDokter(usersTemp[index]);
        } 
        else {
            printf("Dokter dengan username '%s' tidak ditemukan.\n", targetUsername);
        }
    }
    else{
        printf("Pilihan tidak valid. Mohon masukkan pilihan yang benar!.\n");
    }
    free(usersTemp);
}

void cariUser(){
    
    int userChoice;

    printPilihan();
    scanf("%d", &userChoice);

    
    User *usersTemp = (User *)malloc(userCount * sizeof(User));
    for(int i = 0; i < userCount; i++){
        usersTemp[i] = users[i];
    }

    if(userChoice == 1){ // Search by ID
        int idx;
        printf("Cari ID: ");
        scanf("%d", &idx);
        bool found = false;
        printf("##%d\n", userCount);
              
        for(int i = 0; i < userCount; i++){
            if(users[i].id == idx){
                printf("Pengguna dengan ID %d:\n", idx);
                printUser_general(users[i]);
                found = true;
                break;
            }
        }
        if(!found){
            printf("ID user tidak ditemukan!\n");
        }

    }

    
    else if(userChoice == 2){ // Search by Username
        char targetUsername[128];
        printf("Cari Username: ");
        scanf("%s", targetUsername); 
        // Step 1: Urutkan array berdasarkan username
        qsort(usersTemp, userCount, sizeof(User), compareUsername);

        // Step 2: Binary search
        int index = binarySearchUsername(usersTemp, userCount, targetUsername);
        if (index != -1) {
            printf("Menampilkan %s dengan nama %s:\n", usersTemp[index].role, usersTemp[index].username);
            printUser_general(usersTemp[index]);
        } else {
            printf("User dengan username '%s' tidak ditemukan.\n", targetUsername);
        }
    }
    else{
        printf("Pilihan tidak valid. Mohon masukkan pilihan yang benar!.\n");
    }
    free(usersTemp);
}

//int main(){
    //cariPasien();
    // gcc cariuser.c login.c -o cariuser

    /*
    bug to yet to be fixed:
    header
    jarak pembatas
    */
//}

/*
Applied module:
F01 - LOGIN
F02 - REGISTER
F03 - LOGOUT
F05 - Menu & Help
F18 - EXIT
*/