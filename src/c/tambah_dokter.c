#include <stdio.h>
#include <string.h>
#include "../header/user.h"
#include "../header/ruangan.h"
#include "../header/tambah_dokter.h"
#include "../header/utils.h"
#include "../header/set.h"
#include "../header/config.h"

extern User users[MAX_USERS];
extern int userCount;
extern Ruangan ruanganList[MAX_RUANGAN][MAX_RUANGAN];
extern int panjang_denah, lebar_denah;

Set usernameSet;

void toLowerCase(const char *str, char *result) {
    int i = 0;
    while (str[i]) {
        result[i] = char_toLower(str[i]);
        i++;
    }
    result[i] = '\0';
}

int isValidUsername(const char* username) {
    for (int i = 0; username[i]; i++) {
        if (!((username[i] >= 'A' && username[i] <= 'Z') || (username[i] >= 'a' && username[i] <= 'z'))) {
            return 0;
        }
    }
    return 1;
}

int getNextUserId() {
    int maxId = 0;
    for (int i = 0; i < userCount; i++) {
        if (users[i].id > maxId) maxId = users[i].id;
    }
    return maxId + 1;
}

void tambahDokter() {
    // Initialize usernameSet from existing users
    createEmptySet(&usernameSet);
    for (int i = 0; i < userCount; i++) {
        insert(&usernameSet, users[i].username);
    }

    if (userCount >= MAX_USERS) {
        printf("Kapasitas pengguna penuh!\n");
        return;
    }

    char username[MAX_USERNAME], password[MAX_PASSWORD];

    printf("Masukkan username dokter baru: ");
    scanf("%s", username);

    if (!isValidUsername(username)) {
        printf("Username hanya boleh terdiri dari huruf!\n");
        return;
    }

    if (contains(usernameSet, username)) {
        printf("Username sudah digunakan. Silakan pilih username lain.\n");
        return;
    }

    printf("Masukkan password dokter baru: ");
    scanf("%s", password);

    User newDokter;
    newDokter.id = getNextUserId();
    strcpy(newDokter.username, username);
    strcpy(newDokter.password, password);
    strcpy(newDokter.role, "dokter");
    strcpy(newDokter.riwayat_penyakit, "");
    newDokter.suhu_tubuh = 0.0;
    newDokter.tekanan_darah_sistolik = 0;
    newDokter.tekanan_darah_diastolik = 0;
    newDokter.detak_jantung = 0;
    newDokter.saturasi_oksigen = 0;
    newDokter.kadar_gula_darah = 0;
    newDokter.berat_badan = 0.0;
    newDokter.tinggi_badan = 0.0;
    newDokter.kadar_kolesterol = 0;
    newDokter.kadar_kolesterol_ldl = 0;
    newDokter.trombosit = 0;

    users[userCount++] = newDokter;
    insert(&usernameSet, username);

    printf("Dokter %s berhasil ditambahkan dengan ID %d.\n", username, newDokter.id);
}

void assignDokter() {
    char username[MAX_USERNAME];
    printf("Masukkan username dokter yang akan diassign: ");
    scanf("%s", username);

    int dokterId = -1;
    for (int i = 0; i < userCount; i++) {
        if (strcmp(users[i].username, username) == 0 && strcmp(users[i].role, "dokter") == 0) {
            dokterId = users[i].id;
            break;
        }
    }

    if (dokterId == -1) {
        printf("Dokter dengan username %s tidak ditemukan.\n", username);
        return;
    }

    // Cek apakah sudah diassign ke suatu ruangan
    for (int i = 0; i < panjang_denah; i++) {
        for (int j = 0; j < lebar_denah; j++) {
            if (ruanganList[i][j].idDokter == dokterId) {
                printf("Dokter sudah diassign ke ruangan %c%d.\n", 'A' + i, j + 1);
                return;
            }
        }
    }

    char input[10];
    printf("Masukkan kode ruangan (misal A1, B3, dst): ");
    scanf("%s", input);

    // Validasi panjang input minimal 2 (1 huruf + 1 digit)
    if (strlen(input) < 2) {
        printf("Format ruangan tidak valid.\n");
        return;
    }

    char rowChar = input[0];
    if (rowChar < 'A' || rowChar >= 'A' + panjang_denah) {
        printf("Baris tidak valid. Maksimum baris adalah %c.\n", 'A' + panjang_denah - 1);
        return;
    }

    int row = rowChar - 'A';
    int col = atoi(input + 1) - 1;

    if (col < 0 || col >= lebar_denah) {
        printf("Kolom tidak valid. Harus antara 1 hingga %d.\n", lebar_denah);
        return;
    }

    // Cek apakah ruangan sudah diisi
    if (ruanganList[row][col].idDokter != 0) {
        printf("Ruangan %c%d sudah diisi oleh dokter %s.\n", 'A' + row, col + 1, ruanganList[row][col].usernameDokter);
        return;
    }

    // Assign dokter
    ruanganList[row][col].idDokter = dokterId;
    strcpy(ruanganList[row][col].usernameDokter, username);
    ruanganList[row][col].totalPasien = 0;
    initQueue(&ruanganList[row][col].antrianPasien);

    printf("Dokter %s berhasil diassign ke ruangan %c%d.\n", username, 'A' + row, col + 1);
}

void tampilkanDokterDanRuangan() {
    printf("ID\tUsername\tRuangan\n");
    printf("------------------------------------\n");

    int found = 0;
    for (int i = 0; i < userCount; i++) {
        if (strcmp(users[i].role, "dokter") == 0) {
            found = 1;
            printf("%d\t%s\t\t", users[i].id, users[i].username);

            int assigned = 0;
            for (int x = 0; x < panjang_denah; x++) {
                for (int y = 0; y < lebar_denah; y++) {
                    if (ruanganList[x][y].idDokter == users[i].id) {
                        printf("(%d,%d)\n", x + 1, y + 1);
                        assigned = 1;
                        break;
                    }
                }
                if (assigned) break;
            }

            if (!assigned) printf("Belum diassign\n");
        }
    }

    if (!found) {
        printf("Tidak ada dokter yang terdaftar.\n");
    }

    printf("------------------------------------\n");
}
