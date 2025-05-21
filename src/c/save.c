#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <dirent.h>
#include "../header/save.h"

void write_file(const char* path, const char* content) {
    FILE* file = fopen(path, "w");
    if (file != NULL) {
        fputs(content, file);
        fclose(file);
    }
}

// Fungsi cek apakah folder ada
int folder_exists(const char* folder_name) {
    DIR* dir = opendir(folder_name);
    if (dir) {
        closedir(dir);
        return 1; // ada
    }
    return 0; // tidak ada
}

// Fungsi cek apakah folder kosong
int is_folder_empty(const char* folder_name) {
    DIR* dir = opendir(folder_name);
    if (dir == NULL) return 1; // tidak ada -> kita anggap kosong

    struct dirent* entry;
    int count = 0;
    while ((entry = readdir(dir)) != NULL) {
        if (strcmp(entry->d_name, ".") != 0 &&
            strcmp(entry->d_name, "..") != 0) {
            count++;
        }
    }
    closedir(dir);
    return count == 0;
}

void save_data(const char* folder_name) {
    char path[100];
    int exists = folder_exists(folder_name);

    if (!exists) {
        mkdir(folder_name);
        printf("Folder \"%s\" belum ada. Membuat folder baru...\n", folder_name);
        printf("Berhasil menyimpan data di folder %s.\n", folder_name);
    } else if (is_folder_empty(folder_name)) {
        printf("Folder \"%s\" ditemukan dan kosong.\n", folder_name);
        printf("Berhasil menyimpan data di folder %s.\n", folder_name);
    }

    // Simulasi penyimpanan data (di dunia nyata, ini ambil dari memori)
    snprintf(path, sizeof(path), "%s/user.csv", folder_name);
    write_file(path, "id,nama,role\n1,Alice,dokter\n");

    snprintf(path, sizeof(path), "%s/obat.csv", folder_name);
    write_file(path, "id,nama,stok\n101,Paracetamol,50\n");

    snprintf(path, sizeof(path), "%s/penyakit.csv", folder_name);
    write_file(path, "id,nama\n201,Demam\n");

    snprintf(path, sizeof(path), "%s/obat_penyakit.csv", folder_name);
    write_file(path, "obat_id,penyakit_id\n101,201\n");

    snprintf(path, sizeof(path), "%s/config.txt", folder_name);
    write_file(path, "konfigurasi=default\n");
}
