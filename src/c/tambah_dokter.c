#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../header/user.h"
#include "../header/ruangan.h"
#include "../header/tambah_dokter.h"

// Initialize UsernameSet
void initUsernameSet(UsernameSet *set) {
    set->count = 0;
}

// Convert a single character to lowercase
char char_toLower(char c) {
    if (c >= 'A' && c <= 'Z') {
        return c + 32; // Convert to lowercase
    }
    return c;
}

// Convert string to lowercase for case-insensitive comparison
void toLowerCase(const char *str, char *result) {
    for (int i = 0; str[i]; i++) {
        result[i] = char_toLower(str[i]);
    }
    result[strlen(str)] = '\0';
}

// Check if username exists in set (case-insensitive)
int isUsernameExists(UsernameSet *set, const char *username) {
    char lowerUsername[MAX_USERNAME];
    char lowerSetUsername[MAX_USERNAME];
    toLowerCase(username, lowerUsername);
    
    for (int i = 0; i < set->count; i++) {
        toLowerCase(set->usernames[i], lowerSetUsername);
        if (strcmp(lowerUsername, lowerSetUsername) == 0) {
            return 1; // Username exists
        }
    }
    return 0; // Username does not exist
}

// Add username to set
void addUsernameToSet(UsernameSet *set, const char *username) {
    if (set->count < MAX_SET_SIZE) {
        strcpy(set->usernames[set->count], username);
        set->count++;
    }
}

// Validate username (letters only)
int isValidUsername(const char *username) {
    for (int i = 0; username[i]; i++) {
        if (!((username[i] >= 'A' && username[i] <= 'Z') || (username[i] >= 'a' && username[i] <= 'z'))) {
            return 0; // Invalid if contains non-letter characters
        }
    }
    return 1;
}

// Find next available user ID
int getNextUserId(User *users, int userCount) {
    int maxId = 0;
    for (int i = 0; i < userCount; i++) {
        if (users[i].id > maxId) {
            maxId = users[i].id;
        }
    }
    return maxId + 1;
}

// Find available room (kept for potential future use)
int findAvailableRoom(Ruangan *ruangan, int ruanganCount) {
    for (int i = 0; i < ruanganCount; i++) {
        if (ruangan[i].idDokter == 0) {
            return i;
        }
    }
    return -1;
}

// Read config.txt to determine ruanganCount
int readHospitalSize() {
    FILE *file = fopen("../../data/config.txt", "r");
    if (!file) {
        printf("Gagal membuka config.txt\n");
        return -1;
    }

    int rows, columns;
    if (fscanf(file, "%d %d", &rows, &columns) != 2) {
        printf("Gagal membaca ukuran rumah sakit dari config.txt\n");
        fclose(file);
        return -1;
    }

    fclose(file);
    int ruanganCount = rows * columns;
    if (ruanganCount <= 0) {
        printf("Ukuran rumah sakit tidak valid (ruanganCount = %d, maksimum = %d)\n", ruanganCount, 1000);
        return -1;
    }

    return ruanganCount;
}

// Procedure to add a new doctor
void tambahDokter(User *users, int *userCount, UsernameSet *usernameSet) {
    if (*userCount >= MAX_USERS) {
        printf("Kapasitas pengguna penuh!\n");
        return;
    }

    char username[MAX_USERNAME];
    char password[MAX_PASSWORD];
    printf("Masukkan username dokter baru: ");
    scanf("%s", username);

    // Validate username format
    if (!isValidUsername(username)) {
        printf("Username hanya boleh terdiri dari huruf besar dan kecil!\n");
        return;
    }

    // Validate username uniqueness
    if (isUsernameExists(usernameSet, username)) {
        printf("Username sudah digunakan! Silakan pilih username lain.\n");
        return;
    }

    printf("Masukkan password dokter baru: ");
    scanf("%s", password);

    // Add new doctor to users
    User newDokter;
    newDokter.id = getNextUserId(users, *userCount);
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

    users[*userCount] = newDokter;
    (*userCount)++;
    addUsernameToSet(usernameSet, username);
    printf("Dokter %s berhasil ditambahkan dengan ID %d.\n", username, newDokter.id);
}

// Procedure to assign a doctor to a room
void assignDokter(User *users, int userCount, Ruangan *ruangan, int ruanganCount) {
    char username[MAX_USERNAME];
    printf("Masukkan username dokter yang akan diassign: ");
    scanf("%s", username);

    // Find the doctor
    int doctorIndex = -1;
    for (int i = 0; i < userCount; i++) {
        if (strcmp(users[i].username, username) == 0 && strcmp(users[i].role, "dokter") == 0) {
            doctorIndex = i;
            break;
        }
    }

    if (doctorIndex == -1) {
        printf("Dokter dengan username %s tidak ditemukan.\n", username);
        return;
    }

    // Check if doctor is already assigned to a room
    for (int i = 0; i < ruanganCount; i++) {
        if (ruangan[i].idDokter == users[doctorIndex].id) {
            printf("Dokter %s sudah diassign ke ruangan %d.\n", username, i + 1);
            return;
        }
    }

    // Prompt for room number (1-based)
    int roomNumber;
    printf("Masukkan nomor ruangan (1-%d): ", ruanganCount);
    scanf("%d", &roomNumber);

    // Validate room number
    if (roomNumber < 1 || roomNumber > ruanganCount) {
        printf("Nomor ruangan tidak valid. Harus antara 1 dan %d.\n", ruanganCount);
        return;
    }

    // Convert to 0-based index
    int roomIndex = roomNumber - 1;

    // Check if room is already occupied
    if (ruangan[roomIndex].idDokter != 0) {
        printf("Ruangan %d sudah diisi oleh dokter %s.\n", roomNumber, ruangan[roomIndex].usernameDokter);
        return;
    }

    // Assign doctor to room
    ruangan[roomIndex].idDokter = users[doctorIndex].id;
    strcpy(ruangan[roomIndex].usernameDokter, username);
    ruangan[roomIndex].totalPasien = 0;
    initQueue(&ruangan[roomIndex].antrianPasien);
    printf("Dokter %s diassign ke ruangan %d.\n", username, roomNumber);
}

// Procedure to display doctors and their assigned rooms
void tampilkanDokterDanRuangan(User *users, int userCount, Ruangan *ruangan, int ruanganCount) {
    printf("\nDaftar Dokter dan Ruangan:\n");
    printf("ID\tUsername\tRuangan\n");
    printf("--------------------------------\n");

    int found = 0;
    for (int i = 0; i < userCount; i++) {
        if (strcmp(users[i].role, "dokter") == 0) {
            found = 1;
            printf("%d\t%s\t\t", users[i].id, users[i].username);
            
            // Check if the doctor is assigned to a room
            int roomAssigned = -1;
            for (int j = 0; j < ruanganCount; j++) {
                if (ruangan[j].idDokter == users[i].id) {
                    roomAssigned = j;
                    break;
                }
            }
            if (roomAssigned != -1) {
                printf("Ruangan %d\n", roomAssigned + 1);
            } else {
                printf("Belum diassign\n");
            }
        }
    }

    if (!found) {
        printf("Tidak ada dokter yang terdaftar.\n");
    }
    printf("--------------------------------\n");
}

// Simple login check (stub for F01)
int isManagerLoggedIn = 0; // Simulate manager login status
void login() {
    char username[MAX_USERNAME], password[MAX_PASSWORD];
    printf("Username: ");
    scanf("%s", username);
    printf("Password: ");
    scanf("%s", password);
    // For demo, assume "nimonsslatte" is the manager from user.csv
    if (strcmp(username, "nimonsslatte") == 0 && strcmp(password, "nimonatutgajah23") == 0) {
        isManagerLoggedIn = 1;
        printf("Login berhasil sebagai manager.\n");
    } else {
        printf("Login gagal.\n");
    }
}

// Load users from user.csv (stub for D03)
void loadUsers(User *users, int *userCount, UsernameSet *usernameSet) {
    FILE *file = fopen("../../data/user.csv", "r");
    if (!file) {
        printf("Gagal membuka user.csv\n");
        return;
    }

    char line[512];
    // Skip header
    fgets(line, sizeof(line), file);

    *userCount = 0;
    while (fgets(line, sizeof(line), file) && *userCount < MAX_USERS) {
        User *u = &users[*userCount];
        char *token = strtok(line, ";");
        u->id = atoi(token);
        token = strtok(NULL, ";");
        strcpy(u->username, token);
        token = strtok(NULL, ";");
        strcpy(u->password, token);
        token = strtok(NULL, ";");
        strcpy(u->role, token);
        token = strtok(NULL, ";");
        strcpy(u->riwayat_penyakit, token ? token : "");
        u->suhu_tubuh = (token = strtok(NULL, ";")) ? atof(token) : 0.0;
        u->tekanan_darah_sistolik = (token = strtok(NULL, ";")) ? atoi(token) : 0;
        u->tekanan_darah_diastolik = (token = strtok(NULL, ";")) ? atoi(token) : 0;
        u->detak_jantung = (token = strtok(NULL, ";")) ? atoi(token) : 0;
        u->saturasi_oksigen = (token = strtok(NULL, ";")) ? atoi(token) : 0;
        u->kadar_gula_darah = (token = strtok(NULL, ";")) ? atoi(token) : 0;
        u->berat_badan = (token = strtok(NULL, ";")) ? atof(token) : 0.0;
        u->tinggi_badan = (token = strtok(NULL, ";")) ? atof(token) : 0.0;
        u->kadar_kolesterol = (token = strtok(NULL, ";")) ? atoi(token) : 0;
        u->kadar_kolesterol_ldl = (token = strtok(NULL, ";")) ? atoi(token) : 0;
        u->trombosit = (token = strtok(NULL, ";")) ? atoi(token) : 0;

        addUsernameToSet(usernameSet, u->username);
        (*userCount)++;
    }
    fclose(file);
}

