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

// Fungsi pembanding untuk qsort berdasarkan ID
int compareID(const void *a, const void *b) {
    User *userA = (User *)a;
    User *userB = (User *)b;
    if (userA->id < userB->id) return -1;
    if (userA->id > userB->id) return 1;
    return 0;
}

// Fungsi binary search berdasarkan ID
// Mengembalikan indeks di array yang disortir, atau -1 jika tidak ditemukan
int binarySearchID(User arr[], int n, int targetID) {
    int low = 0, high = n - 1;
    while (low <= high) {
        int mid = low + (high - low) / 2;
        if (arr[mid].id == targetID) {
            return mid; // Ditemukan
        }
        if (arr[mid].id < targetID) {
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }
    return -1; // Tidak ditemukan
}
// Fungsi perbandingan username untuk qsort (ascending)
int compareUsername(const void* a, const void* b) {
    const User* userA = (const User*)a;
    const User* userB = (const User*)b;
    return strcmp(userA->username, userB->username);
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
    
    printf("| %-3d | %-18s | %-18s |\n", 
           U.id, formatted_username, formatted_penyakit);
}



void printPilihan(){
    printf("Cari berdasarkan:\n");
    printf("1. ID\n");
    printf("2. Nama\n");
    printf("Masukkan angka pilihan: \n");
    printf("\033[93m>>> \033[0m");
    
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

void cariPasien() {
    int userChoice;

    printf("Cari pasien berdasarkan:\n");
    printf("1. ID\n");
    printf("2. Nama\n");
    printf("3. Penyakit\n");
    printf("Masukkan angka pilihan: \n");
    printf("\033[93m>>> \033[0m");
    scanf("%d", &userChoice);
    int c; // Untuk membersihkan buffer input
    while ((c = getchar()) != '\n' && c != EOF);


    User *usersTemp = NULL; // Hanya alokasi jika diperlukan untuk binary search ID
    if (userChoice == 1) { // Alokasi untuk sorting
        usersTemp = (User *)malloc(userCount * sizeof(User));
        if (usersTemp == NULL && userCount > 0) {
            perror("Gagal mengalokasikan memori untuk usersTemp");
            return;
        }
        for (int i = 0; i < userCount; i++) {
            usersTemp[i] = users[i];
        }
    }


    if (userChoice == 1) { // Search by ID (Binary Search)
        int targetID;
        printf("Cari ID: ");
        scanf("%d", &targetID);
        while ((c = getchar()) != '\n' && c != EOF); // Bersihkan buffer

        qsort(usersTemp, userCount, sizeof(User), compareID);
        int index = binarySearchID(usersTemp, userCount, targetID);

        if (index != -1 && strcmp(usersTemp[index].role, "pasien") == 0) {
            printf("Pasien dengan ID %d ditemukan:\n", targetID);
            // Menggunakan printUser_general atau printPasien sesuai kebutuhan
            // Jika ingin format tabel seperti pencarian penyakit, Anda perlu menyesuaikannya
            printUser_general(usersTemp[index]);
        } else {
            printf("Pasien dengan ID '%d' tidak ditemukan atau bukan pasien.\n", targetID);
        }
    } else if (userChoice == 2) { // Search by Username (Sequential Search)
        char targetUsername[128];
        printf("Cari Username: ");
        // scanf("%s", targetUsername); // Rawan buffer overflow dan tidak membaca spasi
        fgets(targetUsername, sizeof(targetUsername), stdin);
        targetUsername[strcspn(targetUsername, "\n")] = '\0'; // Hapus newline

        bool found = false;
        printf("Mencari pasien dengan username '%s':\n", targetUsername);
        for (int i = 0; i < userCount; i++) {
            if (strcmp(users[i].username, targetUsername) == 0 && strcmp(users[i].role, "pasien") == 0) {
                // Menggunakan printUser_general atau printPasien
                // Jika ingin format tabel, Anda perlu penyesuaian
                printUser_general(users[i]);
                found = true;
                // break; // Hapus jika ingin menampilkan semua pasien dengan nama yang sama
            }
        }
        if (!found) {
            printf("Pasien dengan username '%s' tidak ditemukan.\n", targetUsername);
        }
    } else if (userChoice == 3) { // Search by riwayat_penyakit (Sequential Search - Tidak Berubah)
        char penyakit[32];
        printf("Cari penyakit: ");
        // while ((c = getchar()) != '\n' && c != EOF); // Sudah ada di awal fungsi
        fgets(penyakit, sizeof(penyakit), stdin);
        penyakit[strcspn(penyakit, "\n")] = '\0'; // Hapus newline dari fgets

        int countPenyakit = 0;
        for (int i = 0; i < userCount; i++) {
            if (strcmp(users[i].riwayat_penyakit, penyakit) == 0 && strcmp(users[i].role, "pasien") == 0) {
                if (countPenyakit == 0) {
                    printf("+-----+--------------------+--------------------+\n");
                    printf("| ID  | %-18s | %-18s |\n", "Nama", "Penyakit");
                    printf("+-----+--------------------+--------------------+\n");
                }
                printPasien(users[i]); // Menggunakan printPasien untuk format tabel
                printf("+-----+--------------------+--------------------+\n");
                countPenyakit++;
            }
        }
        if (countPenyakit == 0) {
            printf("Pasien dengan penyakit '%s' tidak ditemukan.\n", penyakit);
        }
    } else {
        printf("Pilihan tidak valid. Mohon masukkan pilihan yang benar!.\n");
    }

    if (usersTemp != NULL) { // Hanya free jika dialokasikan
        free(usersTemp);
    }
}

void cariDokter() {
    int userChoice;

    printf("Cari dokter berdasarkan:\n");
    printf("1. ID\n");
    printf("2. Nama\n");
    printf("Masukkan angka pilihan: \n");
    printf("\033[93m>>> \033[0m");
    scanf("%d", &userChoice);
    int c; // Untuk membersihkan buffer input
    while ((c = getchar()) != '\n' && c != EOF);

    User *usersTemp = NULL;
    if (userChoice == 1) {
        usersTemp = (User *)malloc(userCount * sizeof(User));
        if (usersTemp == NULL && userCount > 0) {
            perror("Gagal mengalokasikan memori untuk usersTemp");
            return;
        }
        for (int i = 0; i < userCount; i++) {
            usersTemp[i] = users[i];
        }
    }

    if (userChoice == 1) { // Search by ID (Binary Search)
        int targetID;
        printf("Cari ID: ");
        scanf("%d", &targetID);
        while ((c = getchar()) != '\n' && c != EOF);

        qsort(usersTemp, userCount, sizeof(User), compareID);
        int index = binarySearchID(usersTemp, userCount, targetID);

        if (index != -1 && strcmp(usersTemp[index].role, "dokter") == 0) {
            printf("Dokter dengan ID %d ditemukan:\n", targetID);
            printDokter(usersTemp[index]); // atau printUser_general
        } else {
            printf("Dokter dengan ID '%d' tidak ditemukan atau bukan dokter.\n", targetID);
        }
    } else if (userChoice == 2) { // Search by Username (Sequential Search)
        char targetUsername[128];
        printf("Cari Username: ");
        fgets(targetUsername, sizeof(targetUsername), stdin);
        targetUsername[strcspn(targetUsername, "\n")] = '\0';

        bool found = false;
        printf("Mencari dokter dengan username '%s':\n", targetUsername);
        for (int i = 0; i < userCount; i++) {
            if (strcmp(users[i].username, targetUsername) == 0 && strcmp(users[i].role, "dokter") == 0) {
                printDokter(users[i]); // atau printUser_general
                found = true;
                // break; // Hapus jika ingin menampilkan semua dokter dengan nama yang sama
            }
        }
        if (!found) {
            printf("Dokter dengan username '%s' tidak ditemukan.\n", targetUsername);
        }
    } else {
        printf("Pilihan tidak valid. Mohon masukkan pilihan yang benar!.\n");
    }

    if (usersTemp != NULL) {
        free(usersTemp);
    }
}

void cariUser() {
    int userChoice;

    printPilihan(); // Mencetak opsi: 1. ID, 2. Nama
    scanf("%d", &userChoice);
    int c; // Untuk membersihkan buffer input
    while ((c = getchar()) != '\n' && c != EOF);


    User *usersTemp = NULL;
    if (userChoice == 1) {
        usersTemp = (User *)malloc(userCount * sizeof(User));
        if (usersTemp == NULL && userCount > 0) {
            perror("Gagal mengalokasikan memori untuk usersTemp");
            return;
        }
        for (int i = 0; i < userCount; i++) {
            usersTemp[i] = users[i];
        }
    }


    if (userChoice == 1) { // Search by ID (Binary Search)
        int targetID;
        printf("Cari ID: ");
        scanf("%d", &targetID);
        while ((c = getchar()) != '\n' && c != EOF);

        qsort(usersTemp, userCount, sizeof(User), compareID);
        int index = binarySearchID(usersTemp, userCount, targetID);

        if (index != -1) {
            printf("Pengguna dengan ID %d ditemukan:\n", targetID);
            printUser_general(usersTemp[index]);
        } else {
            printf("User dengan ID '%d' tidak ditemukan.\n", targetID);
        }
    } else if (userChoice == 2) { // Search by Username (Sequential Search)
        char targetUsername[128];
        printf("Cari Username: ");
        fgets(targetUsername, sizeof(targetUsername), stdin);
        targetUsername[strcspn(targetUsername, "\n")] = '\0';

        bool found = false;
        printf("Mencari user dengan username '%s':\n", targetUsername);
        for (int i = 0; i < userCount; i++) {
            if (strcmp(users[i].username, targetUsername) == 0) {
                printf("Menampilkan %s dengan nama %s:\n", users[i].role, users[i].username);
                printUser_general(users[i]);
                found = true;
                // break; // Hapus jika ingin menampilkan semua user dengan nama yang sama
            }
        }
        if (!found) {
            printf("User dengan username '%s' tidak ditemukan.\n", targetUsername);
        }
    } else {
        printf("Pilihan tidak valid. Mohon masukkan pilihan yang benar!.\n");
    }
    
    if (usersTemp != NULL) {
        free(usersTemp);
    }
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