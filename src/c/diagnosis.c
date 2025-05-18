#include "../header/diagnosis.h"
#include "../header/penyakit.h"
#include "../header/utils.h"
#include <stdbool.h>

#define MAX_LINE_LENGTH 1024
#define MAX_FIELD_LENGTH 256

int getPenyakitId(char* line){
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

void getNamaPenyakit(char* line, char* nama_penyakit){
    getFieldAt(line, 1, nama_penyakit, MAX_NAMA_PENYAKIT);
}

float getSuhuTubuhMin(char* line){
    char field[MAX_FIELD_LENGTH];
    getFieldAt(line, 2, field, MAX_FIELD_LENGTH);
    return stringToFloat(field);
}

float getSuhuTubuhMax(char* line){
    char field[MAX_FIELD_LENGTH];
    getFieldAt(line, 3, field, MAX_FIELD_LENGTH);
    return stringToFloat(field);
}

int getTekananDarahSistolikMin(char* line){
    char field[MAX_FIELD_LENGTH];
    getFieldAt(line, 4, field, MAX_FIELD_LENGTH);
    return stringToInt(field);
}

int getTekananDarahSistolikMax(char* line){
    char field[MAX_FIELD_LENGTH];
    getFieldAt(line, 5, field, MAX_FIELD_LENGTH);
    return stringToInt(field);
}

int getTekananDarahDiastolikMin(char* line){
    char field[MAX_FIELD_LENGTH];
    getFieldAt(line, 6, field, MAX_FIELD_LENGTH);
    return stringToInt(field);
}

int getTekananDarahDiastolikMax(char* line){
    char field[MAX_FIELD_LENGTH];
    getFieldAt(line, 7, field, MAX_FIELD_LENGTH);
    return stringToInt(field);
}
int getDetakJantungMin(char* line){
    char field[MAX_FIELD_LENGTH];
    getFieldAt(line, 8, field, MAX_FIELD_LENGTH);
    return stringToInt(field);
}

int getDetakJantungMax(char* line){
    char field[MAX_FIELD_LENGTH];
    getFieldAt(line, 9, field, MAX_FIELD_LENGTH);
    return stringToInt(field);
}

int getSaturasiOksigenMin(char* line){
    char field[MAX_FIELD_LENGTH];
    getFieldAt(line, 10, field, MAX_FIELD_LENGTH);
    return stringToInt(field);
}

int getSaturasiOksigenMax(char* line){
    char field[MAX_FIELD_LENGTH];
    getFieldAt(line, 11, field, MAX_FIELD_LENGTH);
    return stringToInt(field);
}

int getKadarGulaDarahMin(char* line){
    char field[MAX_FIELD_LENGTH];
    getFieldAt(line, 12, field, MAX_FIELD_LENGTH);
    return stringToInt(field);
}

int getKadarGulaDarahMax(char* line){
    char field[MAX_FIELD_LENGTH];
    getFieldAt(line, 13, field, MAX_FIELD_LENGTH);
    return stringToInt(field);
}

float getBeratBadanMin(char* line){
    char field[MAX_FIELD_LENGTH];
    getFieldAt(line, 14, field, MAX_FIELD_LENGTH);
    return stringToFloat(field);
}

float getBeratBadanMax(char* line){
    char field[MAX_FIELD_LENGTH];
    getFieldAt(line, 15, field, MAX_FIELD_LENGTH);
    return stringToFloat(field);
}

int getTinggiBadanMin(char* line){
    char field[MAX_FIELD_LENGTH];
    getFieldAt(line, 16, field, MAX_FIELD_LENGTH);
    return stringToInt(field);
}

int getTinggiBadanMax(char* line){
    char field[MAX_FIELD_LENGTH];
    getFieldAt(line, 17, field, MAX_FIELD_LENGTH);
    return stringToInt(field);
}

int getKadarKolesterolMin(char* line){
    char field[MAX_FIELD_LENGTH];
    getFieldAt(line, 18, field, MAX_FIELD_LENGTH);
    return stringToInt(field);
}

int getKadarKolesterolMax(char* line){
    char field[MAX_FIELD_LENGTH];
    getFieldAt(line, 19, field, MAX_FIELD_LENGTH);
    return stringToInt(field);
}

int getTrombositMin(char* line){
    char field[MAX_FIELD_LENGTH];
    getFieldAt(line, 20, field, MAX_FIELD_LENGTH);
    return stringToInt(field);
}

int getTrombositMax(char* line){
    char field[MAX_FIELD_LENGTH];
    getFieldAt(line, 21, field, MAX_FIELD_LENGTH);
    return stringToInt(field);
}

Penyakit* getPenyakitData(const char* filename, int* penyakit_count) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error: Could not open file %s\n", filename);
        return NULL;
    }
    
    Penyakit* penyakit = (Penyakit*)malloc(MAX_PENYAKIT * sizeof(Penyakit));
    if (penyakit == NULL) {
        printf("Error: Memory allocation failed\n");
        fclose(file);
        return NULL;
    }
    
    char line[MAX_LINE_LENGTH];
    int line_count = 0;
    *penyakit_count = 0;
    
    // Baca file baris per baris
    while (fgets(line, MAX_LINE_LENGTH, file) != NULL) {
        line_count++;
        
        // Lewati baris header atau baris yang dimulai dengan //
        if (line_count == 1 || (line[0] == '/' && line[1] == '/')) {
            continue;
        }
        
        Penyakit current_penyakit = {0}; // Inisialisasi semua nilai dengan nol
        
        // Proses setiap atribut menggunakan fungsi spesifik
        current_penyakit.id = getPenyakitId(line);
        getNamaPenyakit(line, current_penyakit.name_penyakit);
        current_penyakit.suhu_tubuh_min = getSuhuTubuhMin(line);
        current_penyakit.suhu_tubuh_max = getSuhuTubuhMax(line);
        current_penyakit.tekanan_darah_sistolik_min = getTekananDarahSistolikMin(line);
        current_penyakit.tekanan_darah_sistolik_max = getTekananDarahSistolikMax(line);
        current_penyakit.tekanan_darah_diastolik_min = getTekananDarahDiastolikMin(line);
        current_penyakit.tekanan_darah_diastolik_max = getTekananDarahDiastolikMax(line);
        current_penyakit.detak_jantung_min = getDetakJantungMin(line);
        current_penyakit.saturasi_oksigen_max = getSaturasiOksigenMax(line);
        current_penyakit.kadar_gula_darah_min = getKadarGulaDarahMin(line);
        current_penyakit.kadar_gula_darah_max = getKadarGulaDarahMax(line);
        current_penyakit.berat_badan_min = getBeratBadanMin(line);
        current_penyakit.berat_badan_max = getBeratBadanMax(line);
        current_penyakit.tinggi_badan_min = getTinggiBadanMin(line);
        current_penyakit.tinggi_badan_max = getTinggiBadanMax(line);
        current_penyakit.kadar_kolesterol_min = getKadarKolesterolMin(line);
        current_penyakit.kadar_kolesterol_max = getKadarKolesterolMax(line);
        current_penyakit.trombosit_min = getTrombositMin(line);
        current_penyakit.trombosit_max = getTrombositMax(line);
        
        // Tambahkan user ke array users
        penyakit[*penyakit_count] = current_penyakit;
        (*penyakit_count)++;
        
        // Periksa jika melebihi batas maksimum user
        if (*penyakit_count >= MAX_PENYAKIT) {
            printf("Warning: Maximum number of penyakit reached (%d)\n", MAX_USERS);
            break;
        }
    }
    
    fclose(file);
    return penyakit;
}

/*char *cekPenyakit(User user, Penyakit* penyakit, int penyakit_count){
    bool Found = false;
    int i = 0;
    while (Found == false && i < penyakit_count)
    {
        return "false";
    }
}

void diagnosis(const char* filename, User user){
    int penyakit_count = 0;
    Penyakit* penyakit = getPenyakitData("data/user.csv", &penyakit_count);
    return;
}*/
