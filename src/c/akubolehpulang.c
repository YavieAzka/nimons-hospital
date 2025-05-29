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

// // For testing 
// int panjang_denah_eff = 1;
// int lsebar_denah_eff = 1;

//Check sudah diagnosis atau belum
boolean checkDiagnosis(User *pasien) {
    if(strcmp(pasien->riwayat_penyakit, "") == 0) {
        return false; //belum terdiagnosis
    } else if(strcmp(pasien->riwayat_penyakit, "Nothing") == 0) {
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
    
    for(int j = 0; j < obatPenyakitCount; j ++) {
        int idObat = obatPenyakitList[j].obat_id;
        for(int i = 0; i < obatPenyakitCount; i++) {
            if(idObat == obatPenyakitList[i].obat_id && getIdFromPenyakit(pasien) == obatPenyakitList[i].penyakit_id && urutanNow == obatPenyakitList[i].urutan_minum) {
                if(urutanNow != getjumlahObat(pasien)) {
                    printf("%s -> ", obatList[idObat].nama);
                } else {
                    printf("%s\n", obatList[idObat].nama);
                }
                
                urutanNow ++;
            }
        }
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
    Ruangan* ruanganPasien = cariRuanganPasien(pasien);

    //Cek Lokasi pasien 
    if(ruanganPasien == NULL) {
        printf("Pasien tidak ditemukan. Silahkan melakukan registrasi terlebih dahulu :)\n");

    } else {
        if(cekAntrianPasien(pasien, ruanganPasien) == NULL) {
            printf("Kamu belum berada di urutan terdepan antrian mana pun. Sabar dulu ya! :(\n");
        } else {
            //Pasien belum terdiagnosis
            if(checkDiagnosis(pasien) == false) {
                if(strcmp(pasien->riwayat_penyakit, "") == 0) {
                    printf("Kamu belum menerima diagnosis apapun dari dokter, jangan buru-buru pulang! T^T\n");
                
                } else if(strcmp(pasien->riwayat_penyakit, "Nothing") == 0) {
                    printf("Kamu tidak ada penyakit apapun. Silahkan pulang dan semoga sehat selalu! :3\n");
                    dequeue(&(ruanganPasien->antrianPasien), &idPasienPulang, namaPasienPulang);
                }
            
            } else {
                printf("Dokter sedang memeriksa keadaanmu...\n");
                //Obat belum habis
                if(inventoryPasien.count != 0) {
                    printf("Masih ada obat yang belum kamu habiskan, minum semuanya dulu yukk! :3\n");
                
                } else if(inventoryPasien.count == 0 && checkUrutanObat(pasien) == 0){ 
                    // Urutan salah
                    printf("Maaf, tapi kamu masih belum bisa pulang!\n");
                    printf("Urutan obat yang diharapkan:\n");
                    urutanHarapan(pasien);
                
                    printf("Urutan obat yang kamu minum:\n");
                    int jumlahObat = getjumlahObat(pasien);

                    for(int i = 0; i < jumlahObat; i ++) {
                        if(i != jumlahObat) {
                            printf("%s -> ", obatList[pasien->perut.data[i]].nama);
                        } else {
                            printf("%s\n", obatList[pasien->perut.data[i]].nama);
                        }
                    }
                    printf("Silahkan kunjungi dokter untuk meminta penawar yang sesuai !\n");
                
                } else {
                    printf("Selamat! :D\n");
                    printf("Kamu sudah dinyatakan sembuh oleh dokter. Silahkan pulang dan semoga sehat selalu! :3\n");
                
                    // Reset data pasien dan perut 
                    // (inventory tidak direset karena obat sudah habis (inventory.Count = 0))
                    strcpy(pasien->riwayat_penyakit, "");
                    while (pasien->perut.top != -1) {
                        pop(&pasien->perut);
                    }

                    // Pasien keluar dari antrian
                    dequeue(&(ruanganPasien->antrianPasien), &idPasienPulang, namaPasienPulang);
                }        
            }
        }
    }
}

// int main() {
//     obatList = malloc(sizeof(Obat) * 3);
//     strcpy(obatList[0].nama, "Klorofil");
//     obatList[0].id = 1;
//     strcpy(obatList[1].nama, "Alkali Tanah");
//     obatList[1].id = 2;
//     strcpy(obatList[2].nama, "Es Kopi Susu");
//     obatList[2].id = 3;
// 
//     obatPenyakitList = malloc(sizeof(ObatPenyakit) * 3);
//     obatPenyakitList[0].obat_id = 1;
//     obatPenyakitList[0].penyakit_id = 1;
//     obatPenyakitList[0].urutan_minum = 2;
//     obatPenyakitList[1].obat_id = 2;
//     obatPenyakitList[1].penyakit_id = 1;
//     obatPenyakitList[1].urutan_minum = 1;
//     obatPenyakitList[2].obat_id = 3;
//     obatPenyakitList[2].penyakit_id = 1;
//     obatPenyakitList[2].urutan_minum = 3;
// 
//     penyakitList = malloc(sizeof(Penyakit) * 1);
//     penyakitList[0].id = 1;
//     strcpy(penyakitList[0].name_penyakit, "Heart Attack");
//     // strcpy(penyakitList[0].name_penyakit, "Nothing");
//     // strcpy(penyakitList[0].name_penyakit, "");
// 
//     User pasien;
//     pasien.id = 1; 
//     strcpy(pasien.username, "Monsieur Neuvillette");
//     strcpy(pasien.riwayat_penyakit, "Heart Attack");
//     // strcpy(pasien.riwayat_penyakit, "Nothing");
//     // strcpy(pasien.riwayat_penyakit, "");
// 
//     //Minum obat
//     push(&pasien.perut, 2);
//     push(&pasien.perut, 1);
//     push(&pasien.perut, 3);
// 
//     inventoryPasien.count = 0;
//     // inventory.pasien_id = 1;
//     // inventory.obat_id[0] = 1;
//     // inventory.obat_id[1] = 2;
//     // inventory.obat_id[2] = 3;
// 
//     ruanganList[0][0].totalPasien = 1;
//     ruanganList[0][0].idPasien[0] = 1;
//     
//     enqueue(&ruanganList[0][0].antrianPasien, pasien.id, "Monsieur Neuvillette");
// 
//     akubolehpulang(&pasien);
// }
// 
// // gcc akubolehpulang.c stack.c queue.c inventory.c load.c utils.c -I../header -o akubolehpulang
