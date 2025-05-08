#include <stdio.h>
#include <string.h>
#include "../header/login.h"


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
    printf("ID |      Nama      |      Role      |      Penyakit     |\n");
    printf("==========================================================\n");
}

void printUser_general(User U[], int idx){
    // Mengeprint user jika pengguna menggunakan perintah CARI_USER
    printHeader();
    
    if(strcmp(U[idx].role, "pasien") == 0){
        printf("%d | %s             | %s             | %s                |\n", U[idx].id, U[idx].username, U[idx].role, U[idx].riwayat_penyakit);
    }
    else{
        printf("%d | %s             | %s             | -                |\n", U[idx].id, U[idx].username, U[idx].role);
    }
    
}

void printPasien(User U[], int idx){
    printf("%d | %s             | %s                |\n", U[idx].id, U[idx].username,U[idx].riwayat_penyakit);
}



void printPilihan(){
    printf("Cari berdasarkan:\n");
    printf("1. ID\n");
    printf("2. Nama\n");
    printf(">>> ");
}

void printDokter(User U[], int idx){
    printf("%d | %s             |\n", U[idx].id, U[idx].username);
}

void cariPasien(){
    int userChoice;
    int userCount = 0;
    User* users = getUserData("../../data/user.csv", &userCount);

    printf("Cari berdasarkan:\n");
    printf("1. ID\n");
    printf("2. Nama\n");
    printf("3. Penyakit\n");
    printf(">>> ");

    scanf("%d", &userChoice);
    if(userChoice == 1){ // Search by ID
        int id;
        printf("Cari ID: ");
        scanf("%d", &id);

        if(id >= userCount || id < 0){
            printf("User dengan username '%d' tidak ditemukan.\n", id);
        }
        else{
            printf("Pengguna dengan ID %d:\n", id);
            printPasien(users, id);
        }

    }


    if(userChoice == 2){ // Search by Username
        char targetUsername[128];
        printf("Cari Username: ");
        scanf("%s", targetUsername);

        // Step 1: Urutkan array berdasarkan username
        qsort(users, userCount, sizeof(User), compareUsername);

        // Step 2: Binary search
        int id = binarySearchUsername(users, userCount, targetUsername);

        if (id != -1) {
            printf("Pengguna dengan ID %d:\n", id);
            printPasien(users, id);
        } else {
            printf("User dengan username '%s' tidak ditemukan.\n", targetUsername);
        }
    }

    if(userChoice == 3){  // Search by riwayat_penyakit
        char penyakit[32];
        printf("Cari penyakit: ");
        scanf("%s", &penyakit);
        int countPenyakit = 0;
        for(int i = 0; i < userCount; i++){
            if(strcmp(users[i].riwayat_penyakit, penyakit) == 0){
                if(countPenyakit == 0){
                    printHeader();
                    countPenyakit++;
                }
                printPasien(users, i);
            }
        }
    }
}

void cariDokter(){
    int userChoice;
    int userCount = 0;
    User* users = getUserData("../../data/user.csv", &userCount);

    printf("Cari berdasarkan:\n");
    printf("1. ID\n");
    printf("2. Nama\n");
    printf(">>> ");

    scanf("%d", &userChoice);
    if(userChoice == 1){ // Search by ID
        int id;
        printf("Cari ID: ");
        scanf("%d", &id);

        if(id >= userCount || id < 0 || strcmp(users[id].role,"Dokter") != 0){
            printf("User dengan username '%d' tidak ditemukan.\n", id);
        }
        else if(strcmp(users[id].role,"dokter") == 0){
            printf("Dokter dengan ID %d:\n", id);
            printDokter(users, id);
        }

    }


    if(userChoice == 2){ // Search by Username
        char targetUsername[128];
        printf("Cari Username: ");
        scanf("%s", targetUsername);

        // Step 1: Urutkan array berdasarkan username
        qsort(users, userCount, sizeof(User), compareUsername);

        // Step 2: Binary search
        int id = binarySearchUsername(users, userCount, targetUsername);
        
        if (id != -1 && strcmp(users[id].role,"dokter") == 0) {
            printf("Menampilkan data Dokter dengan nama %s:\n", users[id].username);
            printDokter(users, id);
        } 
        else {
            printf("Dokter dengan username '%s' tidak ditemukan.\n", targetUsername);
        }
    }
}

void cariUser(){
    
    int userChoice;
    int userCount = 0;
    User* users = getUserData("../../data/user.csv", &userCount);
    

    printPilihan();
    scanf("%d", &userChoice);

    if(userChoice == 1){ // Search by ID
        int id;
        printf("Cari ID: ");
        scanf("%d", &id);

        if(id >= userCount || id < 0){
            printf("ID user tidak ditemukan!");
        }
        else{
            printf("Pengguna dengan ID %d:\n", id);
            printUser_general(users, id);
        }

    }


    if(userChoice == 2){ // Search by Username
        char targetUsername[128];
        printf("Cari Username: ");
        scanf("%s", targetUsername);

        // Step 1: Urutkan array berdasarkan username
        qsort(users, userCount, sizeof(User), compareUsername);

        // Step 2: Binary search
        int index = binarySearchUsername(users, userCount, targetUsername);
        for(int i = 0; i < userCount; i++){
            printf("#%s\n", users[i].username);
        }
        if (index != -1) {
            printf("User ditemukan:\n");
            printf("ID       : %d\n", users[index].id);
            printf("Username : %s\n", users[index].username);
            printf("Role     : %s\n", users[index].role);
        } else {
            printf("User dengan username '%s' tidak ditemukan.\n", targetUsername);
        }
    }
}

int main(){
    cariDokter();
    // gcc cariuser.c login.c -o cariuser

    /*
    bug to yet to be fixed:
    header
    jarak pembatas
    */
}