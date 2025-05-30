#include "../header/daftar-check-up.h"
#include "../header/load.h"
#include <stdio.h>
#include <stdlib.h>

bool sudahTerdaftar(int pasienID) {
    for (int i = 0; i < panjang_denah; i++) {
        for (int j = 0; j < lebar_denah; j++) {
            Node* current = ruanganList[i][j].antrianPasien.front;
            while (current != NULL) {
                if (current->idPasien == pasienID) return true;
                current = current->next;
            }
        }
    }
    return false;
}

void daftarCheckUp(User* userNow) {
    
    if (sudahTerdaftar(userNow->id)) {
        printf("\nEh, kamu udah daftar buat check-up nih!\n");
        printf("Yuk, tunggu giliran dulu. Nanti aja daftarnya lagi.\n");
        return;
    }
    int idx = getUserIndex(userNow->username, users, userCount);
    printf("\n--- FORMULIR CHECK-UP PASIEN ---\n");
    printf("Masukin data kesehatan kamu dulu ya. Jangan asal, ini penting!\n");

    float suhu;
    int sistol, diastol, detak;
    float saturasi;
    int gula;
    float berat;
    int tinggi;
    int kolesterol, trombosit;

    do {
        printf("Suhu Tubuh (°C): ");
        scanf("%f", &suhu);
        if (suhu <= 0) printf("Suhu tubuh harus di atas nol yaa.\n");
    } while (suhu <= 0);

    do {
        printf("Tekanan Darah (sistol dan diastol): ");
        scanf("%d %d", &sistol, &diastol);
        if (sistol <= 0 || diastol <= 0) printf("Hmm... tekanan darah gak bisa negatif dong.\n");
    } while (sistol <= 0 || diastol <= 0);

    do {
        printf("Detak Jantung (bpm): ");
        scanf("%d", &detak);
        if (detak <= 0) printf("Detak jantung kamu ilang? Masukin lagi yg bener.\n");
    } while (detak <= 0);

    do {
        printf("Saturasi Oksigen (%%): ");
        scanf("%f", &saturasi);
        if (saturasi <= 0) printf("Jangan ngasal... Napas dulu baru isi!\n");
    } while (saturasi <= 0);

    do {
        printf("Gula Darah (mg/dL): ");
        scanf("%d", &gula);
        if (gula <= 0) printf("Manis dikit gapapa, asal jangan kosong!\n");
    } while (gula <= 0);

    do {
        printf("Berat Badan (kg): ");
        scanf("%f", &berat);
        if (berat <= 0) printf("Yakin berat badan kamu 0? Coba isi ulang.\n");
    } while (berat <= 0);

    do {
        printf("Tinggi Badan (cm): ");
        scanf("%d", &tinggi);
        if (tinggi <= 0) printf("Coba diukur lagi tinggi badannya.\n");
    } while (tinggi <= 0);

    do {
        printf("Kolesterol Total (mg/dL): ");
        scanf("%d", &kolesterol);
        if (kolesterol <= 0) printf("Kolesterol gak boleh minus yaa.\n");
    } while (kolesterol <= 0);

    do {
        printf("Trombosit (ribu/µL): ");
        scanf("%d", &trombosit);
        if (trombosit <= 0) printf("Trombositnya harus diisi yang bener yaa.\n");
    } while (trombosit <= 0);

    // Simpan data ke user
    users[idx].suhu_tubuh = suhu;
    users[idx].tekanan_darah_sistolik = sistol;
    users[idx].tekanan_darah_diastolik = diastol;
    users[idx].detak_jantung = detak;
    users[idx].saturasi_oksigen = saturasi;
    users[idx].kadar_gula_darah = gula;
    users[idx].berat_badan = berat;
    users[idx].tinggi_badan = tinggi;
    users[idx].kadar_kolesterol = kolesterol;
    users[idx].trombosit = trombosit;

    printf("\n--- DOKTER YANG SIAP NANGGEPIN KAMU ---\n");
    int opsi[100][2];
    int count = 0;

    for (int i = 0; i < panjang_denah; i++) {
        for (int j = 0; j < lebar_denah; j++) {
            if (ruanganList[i][j].idDokter != 0 && ruanganList[i][j].antrianPasien.length < kapasitas_ruangan + kapasitas_antrian) {
                printf("%d. Dr. %s - Ruangan %c%d (Antrian: %d pasien)\n",
                       count + 1,
                       ruanganList[i][j].usernameDokter,
                       'A' + i, j + 1,
                       ruanganList[i][j].antrianPasien.length);
                opsi[count][0] = i;
                opsi[count][1] = j;
                count++;
            }
        }
    }

    if (count == 0) {
        printf("Ups... Semua dokter lagi istirahat nih. Coba lagi nanti ya!\n");
        return;
    }

    int pilihan;
    do {
        printf("Pilih dokter (1 - %d): ", count);
        scanf("%d", &pilihan);
        if (pilihan < 1 || pilihan > count) {
            printf("Nomor pilihan gak valid, cek daftar lagi yaa!\n");
        }
    } while (pilihan < 1 || pilihan > count);

    int i = opsi[pilihan - 1][0];
    int j = opsi[pilihan - 1][1];
    enqueue(&ruanganList[i][j].antrianPasien, userNow->id, userNow->username);
    ruanganList[i][j].idPasien[ruanganList[i][j].totalPasien] = userNow->id;
    ruanganList[i][j].totalPasien++;

    printf("\nMantap! Check-up kamu udah masuk daftar.\n");
    printf("Antrian kamu sekarang di Dr. %s - Ruangan %c%d\n",
           ruanganList[i][j].usernameDokter,
           'A' + i, j + 1);
    printf("Nomor urut kamu: %d\n", ruanganList[i][j].antrianPasien.length);
}
