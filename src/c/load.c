#include "../header/utils.h"
#include "../header/user.h"
#include "../header/penyakit.h"
#include "../header/obat.h"
#include "../header/obatPenyakit.h"
#include "../header/load.h"
#include "../header/config.h"
#include "../header/queue.h"

#define MAX_MAPPING 100


// Variabel global
User* users = NULL;
int userCount = 0;

Obat* obatList = NULL;
int obatCount = 0;

Penyakit* penyakitList = NULL;
int penyakitCount = 0;

ObatPenyakit* obatPenyakitList = NULL;
int obatPenyakitCount = 0;


int panjang_denah = 0;
int lebar_denah = 0;
int kapasitas_ruangan = 0;
int jumlah_ruangan = 0;

Ruangan ruanganList[MAX_RUANGAN][MAX_RUANGAN];
InventoryPasien daftar_inventory[MAX_INVENTORY];
int jumlah_inventory = 0;
// Membersihkan karakter newline atau carriage return
void trim_newline(char* str) {
    int len = strlen(str);
    while (len > 0 && (str[len - 1] == '\n' || str[len - 1] == '\r')) {
        str[--len] = '\0';
    }
}

// ================== OBAT ==================

Obat* getObatData(const char* filename, int* count) {
    FILE* file = fopen(filename, "r");
    if (!file) {
        printf("Error: Cannot open file %s\n", filename);
        return NULL;
    }

    Obat* list = malloc(MAX_OBAT * sizeof(Obat));
    *count = 0;

    char line[MAX_LINE_LENGTH];
    fgets(line, sizeof(line), file); // skip header

    while (fgets(line, sizeof(line), file)) {
        char field[64];
        getFieldAt(line, 0, field, sizeof(field));
        list[*count].id = stringToInt(field);

        getFieldAt(line, 1, list[*count].nama, 50);
        trim_newline(list[*count].nama);

        (*count)++;
        if (*count >= MAX_OBAT) break;
    }

    fclose(file);
    return list;
}

// ================== PENYAKIT ==================

Penyakit* getPenyakitData(const char* filename, int* count) {
    FILE* file = fopen(filename, "r");
    if (!file) {
        printf("Error: Cannot open file %s\n", filename);
        return NULL;
    }

    Penyakit* list = malloc(MAX_PENYAKIT * sizeof(Penyakit));
    *count = 0;

    char line[MAX_LINE_LENGTH];
    fgets(line, sizeof(line), file); // skip header
    int line_number = 0;
    while (fgets(line, sizeof(line), file)) {
        if (line_number++ == 0) continue;
        char field[64];
        Penyakit p;

        getFieldAt(line, 0, field, 64); p.id = stringToInt(field);
        getFieldAt(line, 1, p.name_penyakit, 50); trim_newline(p.name_penyakit);
        getFieldAt(line, 2, field, 64); p.suhu_tubuh_min = stringToFloat(field);
        getFieldAt(line, 3, field, 64); p.suhu_tubuh_max = stringToFloat(field);
        getFieldAt(line, 4, field, 64); p.tekanan_darah_sistolik_min = stringToInt(field);
        getFieldAt(line, 5, field, 64); p.tekanan_darah_sistolik_max = stringToInt(field);
        getFieldAt(line, 6, field, 64); p.tekanan_darah_diastolik_min = stringToInt(field);
        getFieldAt(line, 7, field, 64); p.tekanan_darah_diastolik_max = stringToInt(field);
        getFieldAt(line, 8, field, 64); p.detak_jantung_min = stringToInt(field);
        getFieldAt(line, 9, field, 64); p.detak_jantung_max = stringToInt(field);
        getFieldAt(line, 10, field, 64); p.saturasi_oksigen_min = stringToFloat(field);
        getFieldAt(line, 11, field, 64); p.kadar_gula_darah_min = stringToInt(field);
        getFieldAt(line, 12, field, 64); p.kadar_gula_darah_max = stringToInt(field);
        getFieldAt(line, 13, field, 64); p.berat_badan_min = stringToFloat(field);
        getFieldAt(line, 14, field, 64); p.berat_badan_max = stringToFloat(field);
        getFieldAt(line, 15, field, 64); p.tinggi_badan_min = stringToInt(field);
        getFieldAt(line, 16, field, 64); p.tinggi_badan_max = stringToInt(field);
        getFieldAt(line, 17, field, 64); p.kadar_kolesterol_min = stringToInt(field);
        getFieldAt(line, 18, field, 64); p.kadar_kolesterol_max = stringToInt(field);
        getFieldAt(line, 19, field, 64); p.trombosit_min = stringToInt(field);
        getFieldAt(line, 20, field, 64); p.trombosit_max = stringToInt(field);

        list[*count] = p;
        (*count)++;
        if (*count >= MAX_PENYAKIT) break;
    }

    fclose(file);
    return list;
}

// ================== OBAT-PENYAKIT ==================

ObatPenyakit* getObatPenyakitData(const char* filename, int* count) {
    FILE* file = fopen(filename, "r");
    if (!file) {
        printf("Error: Cannot open file %s\n", filename);
        return NULL;
    }

    ObatPenyakit* list = malloc(MAX_MAPPING * sizeof(ObatPenyakit));
    *count = 0;

    char line[MAX_LINE_LENGTH];
    fgets(line, sizeof(line), file); // skip header

    while (fgets(line, sizeof(line), file)) {
        ObatPenyakit op;
        char field[64];

        getFieldAt(line, 0, field, 64);
        op.id_penyakit = stringToInt(field);
        op.jumlah_obat = 0;

        for (int i = 1; i <= MAX_OBAT_PER_PENYAKIT; i++) {
            getFieldAt(line, i, field, 64);
            trim_newline(field);
            if (field[0] == '\0') break;
            op.id_obat[op.jumlah_obat++] = stringToInt(field);
        }

        list[*count] = op;
        (*count)++;
        if (*count >= MAX_MAPPING) break;
    }

    fclose(file);
    return list;
}
// ================== USER ======================
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
        char tempUsername[MAX_USERNAME];
        strcpy(tempUsername, users[i].username);
        str_toLower(tempUsername);
        //printf("#%s %s\n", *username, users[i].username);
        if(strcmp(username, tempUsername) == 0){
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

const char* getUsernameById(int id) {
    for (int i = 0; i < userCount; i++) {
        if (users[i].id == id) {
            return users[i].username;
        }
    }
    return "-"; // default jika tidak ditemukan
}

int readIntsFromLine(const char* line, int* output, int maxInts) {
    int count = 0;
    int value = 0;
    bool inNumber = false;

    for (int i = 0; line[i] != '\0' && count < maxInts; i++) {
        if (line[i] >= '0' && line[i] <= '9') {
            value = value * 10 + (line[i] - '0');
            inNumber = true;
        } else if (inNumber) {
            output[count++] = value;
            value = 0;
            inNumber = false;
        }
    }

    if (inNumber && count < maxInts) {
        output[count++] = value;
    }

    return count;
}


void loadConfig(const char* folder) {
    char path[256];
    sprintf(path, "%s/config.txt", folder);

    FILE* file = fopen(path, "r");
    if (!file) {
        printf("Error: Cannot open config file at %s\n", path);
        return;
    }

    char line[256];
    int data[20];

    // Baris 1: panjang dan lebar denah
    fgets(line, sizeof(line), file);
    int n = readIntsFromLine(line, data, 2);
    panjang_denah = data[0];
    lebar_denah = data[1];
    jumlah_ruangan = panjang_denah * lebar_denah;

    // Baris 2: kapasitas ruangan
    fgets(line, sizeof(line), file);
    readIntsFromLine(line, data, 1);
    kapasitas_ruangan = data[0];

    // Baris 3 sampai jumlah_ruangan + 2: data ruangan
    for (int i = 0; i < jumlah_ruangan; i++) {
        fgets(line, sizeof(line), file);
        int nums[20];
        int count = readIntsFromLine(line, nums, 20);

        int row = i / lebar_denah;
        int col = i % lebar_denah;
        Ruangan* r = &ruanganList[row][col];

        r->totalPasien = 0;
        r->idDokter = (count > 0) ? nums[0] : 0;
        strcpy(r->usernameDokter, getUsernameById(r->idDokter));

        for (int j = 1; j < count; j++) {
            r->idPasien[r->totalPasien] = nums[j];
            strcpy(r->usernamePasien[r->totalPasien], getUsernameById(nums[j]));
            r->totalPasien++;
        }

        initQueue(&(r->antrianPasien)); // kosong
    }

    // Baris selanjutnya: jumlah pasien yang punya inventory
    fgets(line, sizeof(line), file);
    readIntsFromLine(line, data, 1);
    jumlah_inventory = data[0];

    // Baris setelahnya: daftar inventory
    for (int i = 0; i < jumlah_inventory; i++) {
        fgets(line, sizeof(line), file);
        int nums[20];
        int count = readIntsFromLine(line, nums, 20);

        if (count >= 1) {
            InventoryPasien* inv = &daftar_inventory[i];
            inv->pasien_id = nums[0];
            inv->jumlah_obat = 0;

            for (int j = 1; j < count; j++) {
                inv->obat_ids[inv->jumlah_obat++] = nums[j];
            }
        }
    }

    fclose(file);
    printf("Konfigurasi berhasil dimuat dari %s\n", path);
}



// ================== LOAD ALL ==================

void load_all_data(const char* folder) {
    char path[256];

    sprintf(path, "%s/user.csv", folder);
    users = getUserData(path, &userCount);

    sprintf(path, "%s/obat.csv", folder);
    obatList = getObatData(path, &obatCount);

    sprintf(path, "%s/penyakit.csv", folder);
    penyakitList = getPenyakitData(path, &penyakitCount);

    sprintf(path, "%s/obat_penyakit.csv", folder);
    obatPenyakitList = getObatPenyakitData(path, &obatPenyakitCount);

    loadConfig(folder);
    
    printf("Data berhasil diload dari folder: %s\n", folder);

}
