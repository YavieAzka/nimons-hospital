#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <dirent.h>
#include "../header/save.h"
#include "../header/load.h"
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
        mkdir(folder_name, 0777);
        printf("Folder \"%s\" belum ada. Membuat folder baru...\n", folder_name);
        printf("Berhasil menyimpan data di folder %s.\n", folder_name);
    } else if (is_folder_empty(folder_name)) {
        printf("Folder \"%s\" ditemukan dan kosong.\n", folder_name);
        printf("Berhasil menyimpan data di folder %s.\n", folder_name);
    }

    // Simulasi penyimpanan data (di dunia nyata, ini ambil dari memori)
    snprintf(path, sizeof(path), "%s/user.csv", folder_name);
    write_file(path,
    "id;username;password;role;riwayat_penyakit;suhu_tubuh;"
    "tekanan_darah_sistolik;tekanan_darah_diastolik;detak_jantung;"
    "saturasi_oksigen;kadar_gula_darah;berat_badan;tinggi_badan;"
    "kadar_kolesterol;kadar_kolesterol_ldl;trombosit\n"
    )
    
   
    
    snprintf(path, sizeof(path), "%s/obat.csv", folder_name);
    write_file(path,
        "obat_id;nama_obat\n"
        "1;Oseltamivir\n"
        "2;Vitamin C\n"
        "3;Remdesivir\n"
        "4;Lisinopril\n"
        "5;Metformin\n"
    );

    snprintf(path, sizeof(path), "%s/penyakit.csv", folder_name);
    write_file(path,
        "id;nama_penyakit;suhu_tubuh_min;suhu_tubuh_max;"
        "tekanan_darah_sistolik_min;tekanan_darah_sistolik_max;"
        "tekanan_darah_diastolik_min;tekanan_darah_diastolik_max;"
        "detak_jantung_min;detak_jantung_max;saturasi_oksigen_min;"
        "saturasi_oksigen_max;kadar_gula_darah_min;kadar_gula_darah_max;"
        "berat_badan_min;berat_badan_max;tinggi_badan_min;tinggi_badan_max;"
        "kadar_kolesterol_min;kadar_kolesterol_max;trombosit_min;trombosit_max\n"
    
        "1;Influenza;36.0;38.5;90;120;60;80;60;100;95.0;100.0;70.0;140.0;45.0;90.0;150;185;150;240;150;450\n"
        "2;COVID-19;36.0;39.0;90;130;60;85;60;120;90.0;100.0;70.0;180.0;45.0;90.0;150;185;150;240;150;450\n"
        "3;Hipertensi;36.0;37.5;140;180;90;120;60;100;90.0;100.0;70.0;140.0;45.0;90.0;150;185;150;240;150;450\n"
        "4;Diabetes Mellitus;36.0;37.5;90;140;60;90;60;100;90.0;100.0;126.0;200.0;45.0;90.0;150;185;150;240;150;450\n"
        "5;Anemia;36.0;37.0;90;120;60;80;60;100;95.0;100.0;70.0;140.0;45.0;90.0;150;185;150;240;150;450\n"
    );

    snprintf(path, sizeof(path), "%s/obat_penyakit.csv", folder_name);
    write_file(path,
        "obat_id;penyakit_id;urutan_minum\n"
        "1;1;1\n"
        "2;1;2\n"
        "3;2;1\n"
        "4;3;1\n"
        "5;4;1\n"
        "3;5;1\n"
        "4;5;3\n"
        "5;5;2\n"
    );

    snprintf(path, sizeof(path), "%s/config.txt", folder_name);
    write_file(path,
        "2 3\n"
        "3\n"
        "2 3 4 5\n"
        "0\n"
        "0\n"
        "0\n"
        "0\n"
        "0\n"
        "2\n"
        "3 1 2 3 4\n"
        "5 2 3 42 3\n"
    );

}
