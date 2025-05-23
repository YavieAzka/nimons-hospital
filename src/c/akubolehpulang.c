#include "../header/akubolehpulang.h"
#include "../header/user.h"
#include "../header/load.h"
#include "../header/diagnosis.h"
#include "../header/help.h"
#include "../header/minumobat.h"

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
    //check sudah habis atau belum
    for(int i = 0; i < jumlah; i++) {
        if(list[i].tersedia == 1) {
            belumHabis = true;
        }
    }

    return belumHabis;    
}

bool checkNgobatin() {

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
        } else if() {
            //Sudah minum tapi urutan salah
            printf("Urutan peminum obat yang kamu minum:\n");
            printf("Silahkan kunjungi dokter untuk meminta penawar yang sesuai! :]\n");

        } else {
            // Habis dan semuanya valid
            printf("Selamat! :D\n");
            printf("Kamu sudah dinyatakan sembuh oleh dokter. Silahkan pulang dan semoga sehat selalu! :3\n");
        }
    }
}

