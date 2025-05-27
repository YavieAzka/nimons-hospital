#include "../header/utils.h"
#include "../header/user.h"
#include "../header/penyakit.h"
#include "../header/obat.h"
#include "../header/obatPenyakit.h"
#include "../header/load.h"
#include "../header/config.h"
#include "../header/queue.h"
#include "../header/stack.h"

#define MAX_MAPPING 100


// Variabel global
User users[MAX_USERS];
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
int kapasitas_antrian = 0;
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
        *count = 0; // Ensure count is 0 on error
        return NULL;
    }

    // Allocate memory for the list of mappings
    // Using a sufficiently large MAX_MAPPING or dynamic resizing would be robust.
    ObatPenyakit* list = malloc(MAX_MAPPING * sizeof(ObatPenyakit));
    if (!list) {
        printf("Error: Memory allocation failed for ObatPenyakit list.\n");
        fclose(file);
        *count = 0;
        return NULL;
    }

    *count = 0; // Initialize the number of records found

    char line[MAX_LINE_LENGTH];
    char field_buffer[64]; // Buffer to temporarily hold string fields from CSV

    // Skip the header line
    if (fgets(line, sizeof(line), file) == NULL) {
        // File is empty or only has a header (or header read failed)
        fclose(file);
        // list is allocated but count is 0, which is acceptable.
        return list; 
    }

    // Read each data line
    while (fgets(line, sizeof(line), file) && *count < MAX_MAPPING) {
        ObatPenyakit current_op;

        // Field 0: obat_id
        getFieldAt(line, 0, field_buffer, sizeof(field_buffer));
        trim_newline(field_buffer); // Important if getFieldAt doesn't handle it
        if (strlen(field_buffer) == 0) continue; // Skip if field is empty after trim
        current_op.obat_id = stringToInt(field_buffer);

        // Field 1: penyakit_id
        getFieldAt(line, 1, field_buffer, sizeof(field_buffer));
        trim_newline(field_buffer);
        if (strlen(field_buffer) == 0) continue; 
        current_op.penyakit_id = stringToInt(field_buffer);

        // Field 2: urutan_minum
        getFieldAt(line, 2, field_buffer, sizeof(field_buffer));
        trim_newline(field_buffer);
        if (strlen(field_buffer) == 0) continue; 
        current_op.urutan_minum = stringToInt(field_buffer);

        // Add the parsed struct to list
        list[*count] = current_op;
        (*count)++;
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

void str_toLower(char *str) {
    for (int i = 0; str[i]; i++) {
        str[i] = char_toLower(str[i]);
    }
}

void getUserData(const char* filename) {
    FILE* file = fopen(filename, "r");
    if (!file) {
        printf("Error: Cannot open file %s\n", filename);
        return;
    }

    char line[MAX_LINE_LENGTH];
    int line_count = 0;
    userCount = 0;

    while (fgets(line, MAX_LINE_LENGTH, file)) {
        if (++line_count == 1) continue;

        User current_user = {0};

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

        users[userCount++] = current_user;
        if (userCount >= MAX_USERS) break;
    }

    fclose(file);
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


User* getUserById(int id) {
    for (int i = 0; i < userCount; i++) {
        if (users[i].id == id) {
            return &users[i];
        }
    }
    return NULL;
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
    int data[40]; // General purpose array for reading ints from a line

    // Baris 1: ukuran denah
    if (!fgets(line, sizeof(line), file)) { /* Handle error or EOF */ fclose(file); return; }
    readIntsFromLine(line, data, 2);
    panjang_denah = data[0];
    lebar_denah = data[1];
    jumlah_ruangan = panjang_denah * lebar_denah;

    // Baris 2: kapasitas ruangan
    if (!fgets(line, sizeof(line), file)) { /* Handle error or EOF */ fclose(file); return; }
    // Assuming config.txt line 2 strictly has only one value for kapasitas_ruangan as per spec
    readIntsFromLine(line, data, 1); // Read only 1 integer for capacity
    kapasitas_ruangan = data[0];
    // If your config.txt genuinely has a second number for 'kapasitas_antrian' and you use it:
    // int count_kapasitas = readIntsFromLine(line, data, 2);
    // kapasitas_ruangan = data[0];
    // if (count_kapasitas > 1) kapasitas_antrian = data[1];


    // Baris 3–(3 + jumlah_ruangan - 1): ruangan data
    for (int i = 0; i < jumlah_ruangan; i++) {
        if (!fgets(line, sizeof(line), file)) { /* Handle error or EOF */ fclose(file); return; }
        
        int room_config_nums[40]; // Holds numbers from one room line: docID, patientID1, ...
        int num_count_on_line = readIntsFromLine(line, room_config_nums, 40);

        int row = i / lebar_denah;
        int col = i % lebar_denah;
        Ruangan* r = &ruanganList[row][col];

        // Initialize room
        r->idDokter = 0;
        strcpy(r->usernameDokter, ""); // Default to empty
        initQueue(&(r->antrianPasien)); // CRITICAL: Initialize the queue for the room

        if (num_count_on_line > 0) { // If there's at least a doctor ID
            r->idDokter = room_config_nums[0];
            if (r->idDokter != 0) {
                const char* doc_username = getUsernameById(r->idDokter);
                if (doc_username) {
                    strcpy(r->usernameDokter, doc_username);
                }
            }
        }

        if (r->idDokter == 0) { // If no doctor or invalid doctor ID, skip patient processing for this room
            continue; 
        }

        // Enqueue all valid patient IDs listed for this doctor into r->antrianPasien
        // Patient IDs start from room_config_nums[1] up to room_config_nums[num_count_on_line-1]
        for (int j = 1; j < num_count_on_line; j++) {
            int id_pasien = room_config_nums[j];

            if (id_pasien == 0) {
                // Patient ID 0 signifies end of actual patient list OR no patients if it's the first.
                // If this is encountered, no more valid patients on this line.
                break; 
            }

            const char* patient_username = getUsernameById(id_pasien);
                                    
            if (patient_username) { // Ensure a valid username string was returned
                // The B3 issue (showing "1.-") should be resolved because if id_pasien is 0,
                // we break above, and the queue for B3 will be empty.
                // If getUsernameById returns "-" for a *non-zero* unknown ID, that patient "-" will be enqueued.
                enqueue(&(r->antrianPasien), id_pasien, patient_username);
            } else {
                // Optional: Handle case where getUsernameById might return NULL (though yours returns "-")
                // enqueue(&(r->antrianPasien), id_pasien, "UNKNOWN_PATIENT");
            }
        }
        // After this loop, r->antrianPasien.length correctly reflects the total actual patients.
        // The Ruangan struct members like r->totalPasien, r->idPasien[], r->usernamePasien[][]
        // are not the primary source for lihatSemuaAntrian if it reads from the queue.
        // You could set r->totalPasien = r->antrianPasien.length; if it's used elsewhere.
    }

    // ... (Rest of your loadConfig for Inventory and Perut (Stack)) ...
    // Ensure fgets checks and error handling for subsequent file reads too.

    fclose(file);
    printf("Konfigurasi berhasil dimuat dari %s\n", path);


    // Inventory
    fgets(line, sizeof(line), file);
    readIntsFromLine(line, data, 1);
    jumlah_inventory = data[0];

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

    // Perut (stack)
    fgets(line, sizeof(line), file);
    readIntsFromLine(line, data, 1);
    int jumlah_stack_perut = data[0];

    for (int i = 0; i < jumlah_stack_perut; i++) {
        fgets(line, sizeof(line), file);
        int nums[20];
        int count = readIntsFromLine(line, nums, 20);
        if (count == 0) continue;

        int pasien_id = nums[0];
        User* u = getUserById(pasien_id);
        if (u == NULL) continue;

        initStack(&(u->perut));

        // Push dari kiri ke kanan untuk urutan: bawah → atas
        for (int j = 1; j < count; j++) {
            push(&(u->perut), nums[j]);
        }
    }

    fclose(file);
    printf("Konfigurasi berhasil dimuat dari %s\n", path);
}




// ================== LOAD ALL ==================

void load_all_data(const char* folder) {
    char path[256];

    sprintf(path, "%s/user.csv", folder);
    getUserData(path);

    sprintf(path, "%s/obat.csv", folder);
    obatList = getObatData(path, &obatCount);

    sprintf(path, "%s/penyakit.csv", folder);
    penyakitList = getPenyakitData(path, &penyakitCount);

    sprintf(path, "%s/obat_penyakit.csv", folder);
    obatPenyakitList = getObatPenyakitData(path, &obatPenyakitCount);

    loadConfig(folder);
    
    printf("Data berhasil diload dari folder: %s\n", folder);

}
