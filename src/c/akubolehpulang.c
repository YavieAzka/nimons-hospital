#include "stdio.h"
#include "../header/akubolehpulang.h"
#include "../header/user.h"

//Belum terdiagnosis

//Belum menghabiskan seluruh obat

//Sudah minum tapi urutan salah

// Habis dan semuanya valid

//(butuh diagnosis dan ngobatin sepertinya [maaf blm lanjut] :])
void akuBolehPulang(User usernow) {
    //Belum terdiagnosis
    printf("Kamu belum menerima diagnosis apapun dari dokter, jangan buru-buru pulang!\n");

    //Belum menghabiskan seluruh obat
    printf("Dokter sedang memeriksa keadaanmu...\n");
    printf("Masih ada obat yang belum kamu habiskan, minum semuanya dulu yukk! :3\n");

    //Sudah minum tapi urutan salah
    printf("Dokter sedang memeriksa keadaanmu...\n");
    printf("Maaf, tetapi kamu belum bisa pulang! T^T\n");
    printf("Urutan peminum obat yang diharapkan:\n");

    printf("");
    printf("Urutan peminum obat yang kamu minum:\n");
    printf("Silahkan kunjungi dokter untuk meminta penawar yang sesuai! :]\n");

    // Habis dan semuanya valid
    printf("Dokter sedang memeriksa keadaanmu...\n");
    printf("Selamat! :D\n");
    printf("Kamu sudah dinyatakan sembuh oleh dokter. Silahkan pulang dan semoga sehat selalu! :3\n");

}

