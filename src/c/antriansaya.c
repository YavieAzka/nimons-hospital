#include <stdio.h>
#include <string.h>
#include <strings.h> 
#include "../header/antriansaya.h"

Pasien antrian[MAX_PASIEN]; //array buat simpan daftar pasien
int jumlahPasien = 0;

void daftarPasien(const char* nama, const char* dokter, const char* ruangan){
    if(jumlahPasien < MAX_PASIEN){
        strcpy(antrian[jumlahPasien].nama, nama);
        strcpy(antrian[jumlahPasien].dokter, dokter);
        strcpy(antrian[jumlahPasien].ruangan, ruangan);
        antrian[jumlahPasien].posisiAntrian = jumlahPasien + 1;
        antrian[jumlahPasien].terdaftar = 1;
        jumlahPasien++;
    } else{ //jika sudah mencapai batas maksimum MAX_PASIEN
        printf("Maaf banget, jumlah pasien sudah penuh nich!\n");
    }
}
void cekAntrian(const char*nama){
    int found = 0;
    for(int i=0; i<jumlahPasien; i++){
        if(strcasecmp(antrian[i].nama, nama)==0 && antrian[i].terdaftar){
            printf("Status antrian Anda:\n");
            printf("Dokter: %s\n", antrian[i].dokter);
            printf("Ruangan: %s\n", antrian[i].ruangan);
            printf("Posisi antrian: %d dari %d\n", antrian[i].posisiAntrian, jumlahPasien);
            found = 1;
            break;
        }
    }
    if(!found){
        printf("Anda belum terdaftar dalam antrian check-up!\n");
        printf("Silakan daftar terlebih dahulu dengan command DAFTAR_CHECKUP.\n");
    }
}

int main(){
    daftarPasien("Kalyca", "Dr. Budi", "A1");
    daftarPasien("Manullang", "Dr. Budi", "A1");
    char nama[50];
    printf("Kenalan dulu kuy, yuk masukkan nama Anda: ");
    fgets(nama, sizeof(nama), stdin);
    /*Biar bisa baca lebih dari satu kata karena
    siapa tau ada yang namanya pasaran*/
    size_t len = strlen(nama);
    if (len>0 && nama[len-1] == '\n') {
        nama[len-1] = '\0';
    }
    printf("\n>>> ANTRIAN\n");
    cekAntrian(nama);
    return 0;
}