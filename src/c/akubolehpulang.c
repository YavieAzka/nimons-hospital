#include "../header/akubolehpulang.h"
#include "../header/user.h"
#include "../header/load.h"
#include "../header/diagnosis.h"
#include "../header/stack.h"
#include "../header/inventory.h"
#include "../header/obat.h"
#include "../header/obatPenyakit.h"

//Check sudah diagnosis atau belum
bool checkDiagnosis(User *pasien) {
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
        if(idPenyakit == obatPenyakitList[i].id_penyakit) {
            jumlahObat ++;
        }
    }

    return jumlahObat;

}

//Dipanggil kalau semua obat sudah habis
int checkUrutanObat(User *pasien, Stack *perut) {
    //Cek isi perut (Cek urutan_minum dari obat yang sudah diminum sesuai atau tidak)
    int urutBenar = 1;
    int nomorUrutan = 9999;

    while((!isStackEmpty(perut))) {
        int idObat = peek(perut);
        pop(perut);

        int urutanNow = -1;
        for(int i = 0; i < obatPenyakitCount; i++) {
            if(idObat == obatPenyakitList[i].id_obat && getIdFromPenyakit(pasien) == obatPenyakitList[i].id_penyakit) {
                urutanNow = obatPenyakitList[i].jumlah_obat;
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
void urutanHarapan(User *pasien, Stack *perut, Inventory *inv) {
    int urutanNow = 1;
    
    for(int j = 0; j < obatPenyakitCount; j ++) {
        int idObat = obatPenyakitList[j].id_obat;
        for(int i = 0; i < obatPenyakitCount; i++) {
            if(idObat == obatPenyakitList[i].id_obat && getIdFromPenyakit(pasien) == obatPenyakitList[i].id_penyakit && urutanNow == obatPenyakitList[i].jumlah_obat) {
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

void akubolehpulang(User *pasien, Stack *perut, Inventory *inv) {
    //Pasien belum terdiagnosis
    if(checkDiagnosis(pasien) == false) {
        if(strcmp(pasien->riwayat_penyakit, "") == 0) {
            printf("Kamu belum menerima diagnosis apapun dari dokter, jangan buru-buru pulang!\n");

        } else if(strcmp(pasien->riwayat_penyakit, "Nothing") == 0) {
            printf("Kamu tidak ada penyakit apapun. Silahkan pulang dan semoga sehat selalu! :3\n");
        }

    } else {
        printf("Dokter sedang memeriksa keadaanmu...\n");

        if(inv->count != 0) {
            printf("Masih ada obat yang belum kamu habiskan, minum semuanya dulu yukk! :3\n");

        } else if(inv->count == 0 && checkUrutanObat(pasien, perut) == 0){ 
            // Urutan salah
            printf("Urutan obat yang diharapkan:\n");
            urutanHarapan(pasien, perut, inv);

            printf("Urutan obat yang kamu minum:\n");
            int jumlahObat = getjumlahObat(pasien);
            
            for(int i = 0; i < jumlahObat; i ++) {
                if(i != jumlahObat) {
                    printf("%s -> ", obatList[perut->data[i]].nama);
                } else {
                    printf("%s\n", obatList[perut->data[i]].nama);
                }
            }

        } else {
            printf("Selamat! :D\n");
            printf("Kamu sudah dinyatakan sembuh oleh dokter. Silahkan pulang dan semoga sehat selalu! :3\n");
        }        
    }
}

