#include "../header/akubolehpulang.h"
#include "../header/user.h"
#include "../header/load.h"
#include "../header/diagnosis.h"
#include "../header/help.h"
#include "../header/minumobat.h"
#include "../header/minumpenawar.h"

bool checkDiagnosis(User *pasien) {
    if(strcmp(pasien->riwayat_penyakit, "") == 0) {
        return false; //belum terdiagnosis
    } else if(strcmp(pasien->riwayat_penyakit, "Nothing") == 0) {
        return false; //tidak sakit
    } else {
        return true; //sakit
    }
}

bool checkObatHabis(Obat list[], int jumlah) {
    bool belumHabis = false;
    //check sudah habis semua atau belum
    for(int i = 0; i < jumlah; i++) {
        if(list[i].tersedia == 1) {
            belumHabis = true;
        }
    }

    return belumHabis;    
}

void akuBolehPulang(User *pasien) {
    //Belum terdiagnosis
    if(checkDiagnosis(pasien) == false) {
        if(pasien->riwayat_penyakit == "") {
            printf("Kamu belum menerima diagnosis apapun dari dokter, jangan buru-buru pulang!\n");

        } else if(pasien->riwayat_penyakit == "Nothing") {
            printf("Kamu tidak ada penyakit apapun. Silahkan pulang dan semoga sehat selalu! :3\n");
        }
    } else {
        printf("Dokter sedang memeriksa keadaanmu...\n");
        if() {
            //Belum menghabiskan seluruh obat
            printf("Masih ada obat yang belum kamu habiskan, minum semuanya dulu yukk! :3\n");
        } else if(checkUrutanMinum(list, getIdPenyakitByRiwayat(pasien->riwayat_penyakit), P, urutanMinumObat, &idxUrutanMinum) == 0) {
            //Sudah minum tapi urutan salah

            int jumlahObat = 0; //Jumlah obat yang dibinum
            for(int i = 0; i < obatPenyakitCount; i++) {
                P[i].IdObat = obatPenyakitList[i].id_obat;
                P[i].urutanMinum = obatPenyakitList[i].jumlah_obat;
                    jumlahObat++;     
            }

            printf("Urutan peminum obat yang harus kamu minum:\n");
            for(int i = 0; i < jumlahObat; i++) {
                if(i != jumlahObat - 1) {
                    printf("%s -> ", getNamaObatById(P[i].IdObat));
                } else {
                    printf("%s", getNamaObatById(P[i].IdObat));
                }
            }
            printf("Silahkan kunjungi dokter untuk meminta penawar yang sesuai! :]\n");

        } else {
            // Habis dan semuanya valid
            printf("Selamat! :D\n");
            printf("Kamu sudah dinyatakan sembuh oleh dokter. Silahkan pulang dan semoga sehat selalu! :3\n");
        }
    }
}

