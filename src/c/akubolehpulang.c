#include "../header/akubolehpulang.h"
#include "../header/user.h"
#include "../header/load.h"
#include "../header/diagnosis.h"
#include "../header/stack.h"
#include "../header/inventory.h"
#include "../header/obat.h"
#include "../header/obatPenyakit.h"
#include "../header/queue.h"
#include "../header/config.h"

//Check sudah diagnosis atau belum
boolean checkDiagnosis(User *pasien) {
    if(strcmp(pasien->riwayat_penyakit, "") == 0) {
        return false; //belum terdiagnosis
    } else if(strcmp(pasien->riwayat_penyakit, "Sehat") == 0) {
        return false; //tidak sakit
    } else {
        return true; //sakit
    }
}

int getIdFromPenyakit(User *pasien) {
    //Cari ID Penyakit yang dialami pasien
    int idPenyakit = -1;
    for(int i = 0; i < penyakitCount; i++) {
        if(strcmp(pasien->riwayat_penyakit, penyakitList[i].name_penyakit) == 0) {
            idPenyakit = penyakitList[i].id;
            break;
        }
    }

    return idPenyakit;
}

int getjumlahObat(User *pasien) {
    //Cek jumlah obat yang harus diminum
    int jumlahObat = 0;
    int idPenyakit = getIdFromPenyakit(pasien);

    for(int i = 0; i < obatPenyakitCount; i++) {
        if(idPenyakit == obatPenyakitList[i].penyakit_id) {
            jumlahObat ++;
        }
    }

    return jumlahObat;

}

//Dipanggil kalau semua obat sudah habis
int checkUrutanObat(User *pasien) {
    Stack tempPerut = pasien->perut;
    //Cek isi perut (Cek urutan_minum dari obat yang sudah diminum sesuai atau tidak)
    int urutBenar = 1;
    int nomorUrutan = 9999;

    while((!isStackEmpty(tempPerut))) {
        int idObat = peek(tempPerut);
        pop(&tempPerut);

        int urutanNow = -1;
        for(int i = 0; i < obatPenyakitCount; i++) {
            if(idObat == obatPenyakitList[i].obat_id && getIdFromPenyakit(pasien) == obatPenyakitList[i].penyakit_id) {
                urutanNow = obatPenyakitList[i].urutan_minum;
                break;
            }
        }
        if(nomorUrutan < urutanNow) {
            urutBenar = 0;
            break;
        }

        nomorUrutan = urutanNow;
    }

    return urutBenar;
}

//Dipanggil kalau semua obat sudah habis
void urutanHarapan(User *pasien) {
    int urutanNow = 1;
    int totalUrutan = getjumlahObat(pasien);

    while (urutanNow <= totalUrutan) {
        for (int i = 0; i < obatPenyakitCount; i++) {
            if (getIdFromPenyakit(pasien) == obatPenyakitList[i].penyakit_id &&
                obatPenyakitList[i].urutan_minum == urutanNow) {
                
                int idObat = obatPenyakitList[i].obat_id;

                // Cari nama obat berdasarkan id
                const char* nama = "-";
                for (int j = 0; j < obatCount; j++) {
                    if (obatList[j].id == idObat) {
                        nama = obatList[j].nama;
                        break;
                    }
                }

                if (urutanNow < totalUrutan) {
                    printf("%s -> ", nama);
                } else {
                    printf("%s\n", nama);
                }

                break; // lanjut ke urutan berikutnya
            }
        }
        urutanNow++;
    }
}


Ruangan *cariRuanganPasien(User *pasien) {
    for(int i = 0; i < panjang_denah; i++) {
        for(int j = 0; j < lebar_denah; j++) {

            Ruangan *ruanganPasien = &ruanganList[i][j];
            
            //Cek pasien ada di salah satu ruangan
            for(int k = 0; k < ruanganPasien->totalPasien; k++) {
                if(pasien->id == ruanganPasien->idPasien[k]) {
                    return ruanganPasien;
                }
            }
        }
    }
    return NULL;
}

Ruangan* cekAntrianPasien(User* pasien, Ruangan *ruanganPasien) {     
    int idPasien;
    char namaPasien[MAX_USERNAME];
        
    //Cek apakah pasien ada di antrian paling depan
    if(!isEmptyQueue(&ruanganPasien->antrianPasien)) {
        peekFront(&(ruanganPasien->antrianPasien), &idPasien, namaPasien);
        if(idPasien == pasien->id) {
            // Pasien di antrian paling depan
            return ruanganPasien;
        } 
    }

    return NULL;
}

void akubolehpulang(User *pasien) {
    int idPasienPulang;
    char namaPasienPulang[MAX_USERNAME];
    int idx = getUserIndex(pasien->username, users, userCount);
    Ruangan* ruanganPasien = cariRuanganPasien(pasien);
    InventoryPasien* inventoryPasien = getInventoryByUser(pasien);
    //Cek Lokasi pasien 
    if(ruanganPasien == NULL) {
        printf("Pasien tidak ditemukan. Silahkan melakukan registrasi terlebih dahulu :)\n");

    } else {
        if(cekAntrianPasien(&users[idx], ruanganPasien) == NULL) {
            printf("Kamu belum berada di urutan terdepan antrian mana pun. Sabar dulu ya! :(\n");
        } else {
            //Pasien belum terdiagnosis
            if(checkDiagnosis(&users[idx]) == false) {
                if(strcmp(users[idx].riwayat_penyakit, "") == 0) {
                    printf("Kamu belum menerima diagnosis apapun dari dokter, jangan buru-buru pulang! T^T\n");
                
                } else if(strcmp(users[idx].riwayat_penyakit, "Nothing") == 0) {
                    printf("Kamu tidak ada penyakit apapun. Silahkan pulang dan semoga sehat selalu! :3\n");
                    dequeue(&(ruanganPasien->antrianPasien), &idPasienPulang, namaPasienPulang);
                }
            
            } else {
                printf("Dokter sedang memeriksa keadaanmu...\n");
                //Obat belum habis
                if(inventoryPasien->count != 0) {
                    printf("Masih ada obat yang belum kamu habiskan, minum semuanya dulu yukk! :3\n");
                
                } else if(inventoryPasien->count == 0 && checkUrutanObat(&users[idx]) == 0){ 
                    // Urutan salah
                    printf("Maaf, tapi kamu masih belum bisa pulang!\n");
                    printf("Urutan obat yang diharapkan:\n");
                    urutanHarapan(&users[idx]);
                
                    printf("Urutan obat yang kamu minum:\n");
                    int jumlahObat = getjumlahObat(&users[idx]);

                    for(int i = 0; i < jumlahObat; i ++) {
                        // Cari nama obat berdasarkan ID
                        char namaObat[20] = "";
                        for (int j = 0; j < obatCount; j++) {
                            if (obatList[j].id == users[idx].perut.data[i]) {
                                strcpy(namaObat, obatList[j].nama);
                                break;
                            }
                        }
                        if(strcmp(namaObat, "") == 0){
                            break;
                        }
                        else if(i == 0) {
                            printf("%s", namaObat);
                            
                        } else {
                            printf("-> %s ", namaObat);
                        }
                    }
                    printf("\nSilahkan kunjungi dokter untuk meminta penawar yang sesuai !\n");
                
                } else {
                    printf("Selamat! :D\n");
                    printf("Kamu sudah dinyatakan sembuh oleh dokter. Silahkan pulang dan semoga sehat selalu! :3\n");
                
                    // Reset data users[idx] dan perut 
                    // (inventory tidak direset karena obat sudah habis (inventory.Count = 0))
                    strcpy(users[idx].riwayat_penyakit, "");
                    while (!isStackEmpty(users[idx].perut)) {
                        pop(&users[idx].perut);
                    }
                    
                    // Pasien keluar dari antrian
                    dequeue(&(ruanganPasien->antrianPasien), &idPasienPulang, namaPasienPulang);
                }        
            }
        }
    }
}