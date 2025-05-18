#include "../header/utils.h"
#include "../header/user.h"
#include "../header/penyakit.h"
#include "../header/obat.h"
#include "../header/obatPenyakit.h"

#define MAX_LINE_LENGTH 256
#define MAX_OBAT 20
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

    printf("Data berhasil diload dari folder: %s\n", folder);
}
