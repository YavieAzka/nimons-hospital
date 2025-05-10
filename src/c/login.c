#include "../header/user.h"
#include "../header/boolean.h"
//Read user.csv file and store it in users[] array.
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_LENGTH 1024
#define MAX_FIELD_LENGTH 256

// Fungsi utama untuk mendapatkan field ke-n dari baris CSV
void getFieldAt(char* line, int field_number, char* output, int max_length) {
    int current_field = 0;
    int i = 0;
    int j = 0;
    
    // Cari field yang diminta
    while (line[i] != '\0' && current_field < field_number) {
        if (line[i] == ';') {
            current_field++;
        }
        i++;
    }
    
    // Ekstrak field
    while (line[i] != ';' && line[i] != '\0' && line[i] != '\n' && j < max_length - 1) {
        output[j++] = line[i++];
    }
    
    output[j] = '\0';
}

// Fungsi untuk mengambil nilai ID dari baris CSV (field index 0)
int getId(char* line) {
    char field[MAX_FIELD_LENGTH];
    getFieldAt(line, 0, field, MAX_FIELD_LENGTH);
    
    int id = 0;
    int i = 0;
    
    while (field[i] >= '0' && field[i] <= '9') {
        id = id * 10 + (field[i] - '0');
        i++;
    }
    
    return id;
}

// Fungsi untuk mengambil username dari baris CSV (field index 1)
void getUsername(char* line, char* username) {
    getFieldAt(line, 1, username, MAX_USERNAME);
}

// Fungsi untuk mengambil password dari baris CSV (field index 2)
void getPassword(char* line, char* password) {
    getFieldAt(line, 2, password, MAX_PASSWORD);
}

// Fungsi untuk mengambil role dari baris CSV (field index 3)
void getRole(char* line, char* role) {
    getFieldAt(line, 3, role, MAX_ROLE);
}

// Fungsi untuk mengambil riwayat penyakit dari baris CSV (field index 4)
void getRiwayatPenyakit(char* line, char* riwayat_penyakit) {
    getFieldAt(line, 4, riwayat_penyakit, MAX_RIWAYAT);
}

// Fungsi helper untuk mengubah string menjadi float
float stringToFloat(char* str) {
    float value = 0.0;
    int i = 0;
    int decimal_pos = -1;
    int is_negative = 0;
    
    // Periksa jika nilai negatif
    if (str[i] == '-') {
        is_negative = 1;
        i++;
    }
    
    // Cari bagian integral dan desimal
    while (str[i] != '\0') {
        if (str[i] == '.') {
            decimal_pos = 0;
        } else if (str[i] >= '0' && str[i] <= '9') {
            if (decimal_pos >= 0) {
                value = value + (str[i] - '0') / (10.0 * (++decimal_pos));
            } else {
                value = value * 10 + (str[i] - '0');
            }
        }
        i++;
    }
    
    return is_negative ? -value : value;
}

// Fungsi helper untuk mengubah string menjadi integer
int stringToInt(char* str) {
    int value = 0;
    int i = 0;
    int is_negative = 0;
    
    // Periksa jika nilai negatif
    if (str[i] == '-') {
        is_negative = 1;
        i++;
    }
    
    while (str[i] != '\0') {
        if (str[i] >= '0' && str[i] <= '9') {
            value = value * 10 + (str[i] - '0');
        }
        i++;
    }
    
    return is_negative ? -value : value;
}

// Fungsi untuk mengambil suhu tubuh dari baris CSV (field index 5)
float getSuhuTubuh(char* line) {
    char field[MAX_FIELD_LENGTH];
    getFieldAt(line, 5, field, MAX_FIELD_LENGTH);
    return stringToFloat(field);
}

// Fungsi untuk mengambil tekanan darah sistolik dari baris CSV (field index 6)
int getTekananDarahSistolik(char* line) {
    char field[MAX_FIELD_LENGTH];
    getFieldAt(line, 6, field, MAX_FIELD_LENGTH);
    return stringToInt(field);
}

// Fungsi untuk mengambil tekanan darah diastolik dari baris CSV (field index 7)
int getTekananDarahDiastolik(char* line) {
    char field[MAX_FIELD_LENGTH];
    getFieldAt(line, 7, field, MAX_FIELD_LENGTH);
    return stringToInt(field);
}

// Fungsi untuk mengambil detak jantung dari baris CSV (field index 8)
int getDetakJantung(char* line) {
    char field[MAX_FIELD_LENGTH];
    getFieldAt(line, 8, field, MAX_FIELD_LENGTH);
    return stringToInt(field);
}

// Fungsi untuk mengambil saturasi oksigen dari baris CSV (field index 9)
int getSaturasiOksigen(char* line) {
    char field[MAX_FIELD_LENGTH];
    getFieldAt(line, 9, field, MAX_FIELD_LENGTH);
    return stringToInt(field);
}

// Fungsi untuk mengambil kadar gula darah dari baris CSV (field index 10)
int getKadarGulaDarah(char* line) {
    char field[MAX_FIELD_LENGTH];
    getFieldAt(line, 10, field, MAX_FIELD_LENGTH);
    return stringToInt(field);
}

// Fungsi untuk mengambil berat badan dari baris CSV (field index 11)
float getBeratBadan(char* line) {
    char field[MAX_FIELD_LENGTH];
    getFieldAt(line, 11, field, MAX_FIELD_LENGTH);
    return stringToFloat(field);
}

// Fungsi untuk mengambil tinggi badan dari baris CSV (field index 12)
float getTinggiBadan(char* line) {
    char field[MAX_FIELD_LENGTH];
    getFieldAt(line, 12, field, MAX_FIELD_LENGTH);
    return stringToFloat(field);
}

// Fungsi untuk mengambil kadar kolesterol dari baris CSV (field index 13)
int getKadarKolesterol(char* line) {
    char field[MAX_FIELD_LENGTH];
    getFieldAt(line, 13, field, MAX_FIELD_LENGTH);
    return stringToInt(field);
}

// Fungsi untuk mengambil kadar kolesterol LDL dari baris CSV (field index 14)
int getKadarKolesterolLDL(char* line) {
    char field[MAX_FIELD_LENGTH];
    getFieldAt(line, 14, field, MAX_FIELD_LENGTH);
    return stringToInt(field);
}

// Fungsi untuk mengambil trombosit dari baris CSV (field index 15)
int getTrombosit(char* line) {
    char field[MAX_FIELD_LENGTH];
    getFieldAt(line, 15, field, MAX_FIELD_LENGTH);
    return stringToInt(field);
}

// Fungsi utama untuk memproses file CSV dan mengisi data user
User* getUserData(const char* filename, int* user_count) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error: Could not open file %s\n", filename);
        return NULL;
    }
    
    User* users = (User*)malloc(MAX_USERS * sizeof(User));
    if (users == NULL) {
        printf("Error: Memory allocation failed\n");
        fclose(file);
        return NULL;
    }
    
    char line[MAX_LINE_LENGTH];
    int line_count = 0;
    *user_count = 0;
    
    // Baca file baris per baris
    while (fgets(line, MAX_LINE_LENGTH, file) != NULL) {
        line_count++;
        
        // Lewati baris header atau baris yang dimulai dengan //
        if (line_count == 1 || (line[0] == '/' && line[1] == '/')) {
            continue;
        }
        
        User current_user = {0}; // Inisialisasi semua nilai dengan nol
        
        // Proses setiap atribut menggunakan fungsi spesifik
        current_user.id = getId(line);
        getUsername(line, current_user.username);
        getPassword(line, current_user.password);
        getRole(line, current_user.role);
        getRiwayatPenyakit(line, current_user.riwayat_penyakit);
        current_user.suhu_tubuh = getSuhuTubuh(line);
        current_user.tekanan_darah_sistolik = getTekananDarahSistolik(line);
        current_user.tekanan_darah_diastolik = getTekananDarahDiastolik(line);
        current_user.detak_jantung = getDetakJantung(line);
        current_user.saturasi_oksigen = getSaturasiOksigen(line);
        current_user.kadar_gula_darah = getKadarGulaDarah(line);
        current_user.berat_badan = getBeratBadan(line);
        current_user.tinggi_badan = getTinggiBadan(line);
        current_user.kadar_kolesterol = getKadarKolesterol(line);
        current_user.kadar_kolesterol_ldl = getKadarKolesterolLDL(line);
        current_user.trombosit = getTrombosit(line);
        
        // Tambahkan user ke array users
        users[*user_count] = current_user;
        (*user_count)++;
        
        // Periksa jika melebihi batas maksimum user
        if (*user_count >= MAX_USERS) {
            printf("Warning: Maximum number of users reached (%d)\n", MAX_USERS);
            break;
        }
    }
    
    fclose(file);
    return users;
}

//Fungsi untuk mencetak data user (untuk debugging)
// void printUserData(User users, int user_count) {
    
//     printf("  ID: %d\n", users.id);
//     printf("  Username: %s\n", users.username);
//     printf("  Password: %s\n", users.password);
//     printf("  Role: %s\n", users.role);
//     printf("  Riwayat Penyakit: %s\n", users.riwayat_penyakit);
//     printf("  Suhu Tubuh: %.1f\n", users.suhu_tubuh);
//     printf("  Tekanan Darah: %d/%d\n", users.tekanan_darah_sistolik, users.tekanan_darah_diastolik);
//     printf("  Detak Jantung: %d\n", users.detak_jantung);
//     printf("  Saturasi Oksigen: %d\n", users.saturasi_oksigen);
//     printf("  Kadar Gula Darah: %d\n", users.kadar_gula_darah);
//     printf("  Berat Badan: %.1f\n", users.berat_badan);
//     printf("  Tinggi Badan: %.1f\n", users.tinggi_badan);
//     printf("  Kadar Kolesterol: %d\n", users.kadar_kolesterol);
//     printf("  Kadar Kolesterol LDL: %d\n", users.kadar_kolesterol_ldl);
//     printf("  Trombosit: %d\n", users.trombosit);
//     printf("\n");
    
// }
int getUserIndex(const char* username, User* users, int user_count){
    
    for(int i = 0; i < user_count; i++){
        //printf("#%s %s\n", *username, users[i].username);
        if(strcmp(username, users[i].username) == 0){
            return i;
        }
    }
    return -1;
}

char char_toLower(char c) {
    if (c >= 'A' && c <= 'Z') {
        return c + 32;
    } else {
        return c;
    }
}

void str_toLower(char *str) {
    for (int i = 0; str[i]; i++) {
        str[i] = char_toLower(str[i]);
    }
}

User login(User *user_now){

    // users adalah array yang menampung data User
    int user_count = 0;
    User* users = getUserData("../../data/user.csv", &user_count);
    char username[512]; char password[512];


    // input username
    printf("Username: ");
    scanf("%s", &username);
    str_toLower(username);
    
    // input password
    printf("Password: ");
    scanf("%s", &password);
    
    // cek apakah username sudah terdaftar
    if(getUserIndex(username, users, user_count) != -1){
        *user_now = users[getUserIndex(username, users, user_count)];
        // Password correct
        if(strcmp(password, user_now->password) == 0){
            printf("Login Berhasil!. Welcome %s %s\n", user_now->role, user_now->username);
        }
        
        // Password incorrect
        else{
            printf("Password untuk user %s salah. Mohon login kembali.\n", user_now->username);
        }
        
    }
    else{
        printf("Pengguna belum terdaftar. Mohon untuk melakukan pendaftaran terlebih dahulu.\n");
    }
    
    free(users);
    return *user_now;
}
//Contoh cara menggunakan fungsi-fungsi ini
int main() {
    // users adalah array yang menampung data User.
    int user_count = 0;
    User u;
    
    u = login(&u);
    printf("#%s", u.username);
    return 0;
}

// gcc src/c/main.c src/c/login.c -I src/header -o src/c/main