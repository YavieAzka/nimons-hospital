#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <dirent.h>

#include "../header/obat.h"
#include "../header/penyakit.h"
#include "../header/obatPenyakit.h"
#include "../header/user.h"
#include "../header/config.h"

#include "../header/save.h"
#include "../header/load.h"
#include "../header/queue.h"
#include "../header/stack.h"
#include "../header/inventory.h"

int folder_exists(const char* folder_name) {
    DIR* dir = opendir(folder_name);
    if (dir) {
        closedir(dir);
        return 1;
    }
    return 0;
}

int is_folder_empty(const char* folder_name) {
    DIR* dir = opendir(folder_name);
    if (dir == NULL) return 1;

    struct dirent* entry;
    int count = 0;
    while ((entry = readdir(dir)) != NULL) {
        if (strcmp(entry->d_name, ".") != 0 && strcmp(entry->d_name, "..") != 0) {
            count++;
        }
    }
    closedir(dir);
    return count == 0;
}

void save_config(const char* folder_name) {
    char path[256];
    snprintf(path, sizeof(path), "%s/config.txt", folder_name);
    FILE* f = fopen(path, "w");
    if (!f) {
        printf("Gagal menyimpan config.txt\n");
        return;
    }

    // Baris 1: ukuran denah
    fprintf(f, "%d %d\n", panjang_denah, lebar_denah);

    // Baris 2: kapasitas ruangan dan antrian
    fprintf(f, "%d %d\n", kapasitas_ruangan, kapasitas_antrian);

    // Baris 3-n: ruangan
    for (int i = 0; i < jumlah_ruangan; i++) {
        int row = i / lebar_denah;
        int col = i % lebar_denah;
        Ruangan* r = &ruanganList[row][col];

        fprintf(f, "%d", r->idDokter);
        while (r->antrianPasien.front != NULL)
        {
            fprintf(f, " %d", r->antrianPasien.front->idPasien);
            r->antrianPasien.front = r->antrianPasien.front->next;
        }            
        
        fprintf(f, "\n");
    }

    // Inventory
    int jumlahInventory;
    searchJumlahInventory(&jumlahInventory);
    fprintf(f, "%d\n", jumlahInventory);
    for (int i = 0; i < jumlah_inventory; i++) {
        InventoryPasien* inv = &daftar_inventory[i];
        if (inv->count == 0) continue; // Hanya simpan inventory yang tidak kosong
        
        fprintf(f, "%d", inv->pasien_id);
        for (int j = 0; j < inv->count; j++) {
            fprintf(f, " %d", inv->obat_id[j]);
        }
        fprintf(f, "\n");
    }

    // Stack perut
    int jumlah_stack = 0;
    for (int i = 0; i < userCount; i++) {
        if (users[i].perut.top > 0) {
            jumlah_stack++;
        }
    }
    fprintf(f, "%d\n", jumlah_stack);
    for (int i = 0; i < userCount; i++) {
        if (users[i].perut.data[0] > 0 && users[i].perut.top > -1) {
            // Hanya simpan stack perut yang tidak kosong
            fprintf(f, "%d", users[i].id);
            for (int j = 0; j <=  users[i].perut.top; j++) {
                fprintf(f, " %d", users[i].perut.data[j]);
            }   
            fprintf(f, "\n");
        }
    }

    fclose(f);
}

void save_data(const char* folder_name) {
    char path[256];
    int exists = folder_exists(folder_name);

    if (!exists) {
        mkdir(folder_name, 0777); // Membuat folder dengan permission 0777
        printf("Folder \"%s\" belum ada. Membuat folder baru...\n", folder_name);
    } else if (is_folder_empty(folder_name)) {
        printf("Folder \"%s\" ditemukan dan kosong.\n", folder_name);
    }
    printf("Berhasil menyimpan data di folder %s.\n", folder_name);

    // Simpan user.csv
    snprintf(path, sizeof(path), "%s/user.csv", folder_name);
    FILE* f_user = fopen(path, "w");
    if (f_user) {
        fprintf(f_user, "id;username;password;role;riwayat_penyakit;suhu_tubuh;tekanan_darah_sistolik;tekanan_darah_diastolik;detak_jantung;saturasi_oksigen;kadar_gula_darah;berat_badan;tinggi_badan;kadar_kolesterol;trombosit\n");
        for (int i = 0; i < userCount; i++) {
            fprintf(f_user, "%d;%s;%s;%s;%s;%.1f;%d;%d;%d;%.1f;%d;%.1f;%d;%d;%d\n",
            users[i].id, users[i].username, users[i].password, users[i].role, users[i].riwayat_penyakit,
            users[i].suhu_tubuh, users[i].tekanan_darah_sistolik, users[i].tekanan_darah_diastolik,
            users[i].detak_jantung, users[i].saturasi_oksigen, users[i].kadar_gula_darah,
            users[i].berat_badan, users[i].tinggi_badan, users[i].kadar_kolesterol,
            users[i].trombosit);
        }
        fclose(f_user);
    }

    // Simpan obat.csv
    snprintf(path, sizeof(path), "%s/obat.csv", folder_name);
    FILE* f_obat = fopen(path, "w");
    if (f_obat) {
        fprintf(f_obat, "obat_id;nama_obat\n");
        for (int i = 0; i < obatCount; i++) {
            fprintf(f_obat, "%d;%s\n", obatList[i].id, obatList[i].nama);
        }
        fclose(f_obat);
    }

    // Simpan penyakit.csv
    snprintf(path, sizeof(path), "%s/penyakit.csv", folder_name);
    FILE* f_penyakit = fopen(path, "w");
    if (f_penyakit) {
        fprintf(f_penyakit, "id;nama_penyakit;suhu_tubuh_min;suhu_tubuh_max;tekanan_darah_sistolik_min;tekanan_darah_sistolik_max;tekanan_darah_diastolik_min;tekanan_darah_diastolik_max;detak_jantung_min;detak_jantung_max;saturasi_oksigen_min;saturasi_oksigen_max;kadar_gula_darah_min;kadar_gula_darah_max;berat_badan_min;berat_badan_max;tinggi_badan_min;tinggi_badan_max;kadar_kolesterol_min;kadar_kolesterol_max;trombosit_min;trombosit_max\n");
        for (int i = 0; i < penyakitCount; i++) {
            fprintf(f_penyakit, "%d;%s;%.1f;%.1f;%d;%d;%d;%d;%d;%d;%.1f;%.1f;%.1d;%.1d;%.1f;%.1f;%d;%d;%d;%d;%d;%d\n",
                penyakitList[i].id, penyakitList[i].name_penyakit,
                penyakitList[i].suhu_tubuh_min, penyakitList[i].suhu_tubuh_max,
                penyakitList[i].tekanan_darah_sistolik_min, penyakitList[i].tekanan_darah_sistolik_max,
                penyakitList[i].tekanan_darah_diastolik_min, penyakitList[i].tekanan_darah_diastolik_max,
                penyakitList[i].detak_jantung_min, penyakitList[i].detak_jantung_max,
                penyakitList[i].saturasi_oksigen_min, penyakitList[i].saturasi_oksigen_max,
                penyakitList[i].kadar_gula_darah_min, penyakitList[i].kadar_gula_darah_max,
                penyakitList[i].berat_badan_min, penyakitList[i].berat_badan_max,
                penyakitList[i].tinggi_badan_min, penyakitList[i].tinggi_badan_max,
                penyakitList[i].kadar_kolesterol_min, penyakitList[i].kadar_kolesterol_max,
                penyakitList[i].trombosit_min, penyakitList[i].trombosit_max);
        }
        fclose(f_penyakit);
    }

    // Simpan obat_penyakit.csv
    snprintf(path, sizeof(path), "%s/obat_penyakit.csv", folder_name);
    FILE* f_op = fopen(path, "w");
    if (f_op) {
        fprintf(f_op, "obat_id;penyakit_id;urutan_minum\n");
        for (int i = 0; i < obatPenyakitCount; i++) {
            fprintf(f_op, "%d;%d;%d\n", obatPenyakitList[i].obat_id, obatPenyakitList[i].penyakit_id, obatPenyakitList[i].urutan_minum);
        }
        fclose(f_op);
    }

    // Simpan config.txt
    save_config(folder_name);
}
