#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../header/minumobat.h"

void daftarObat(Obat list[], int jumlah){ //array dan jumlah obat yang ada
    printf(">>> MINUM_OBAT ===========\n");
    printf("========== DAFTAR OBAT ==========\n");
    for(int i=0; i<jumlah; i++){
        if(list[i].tersedia){
            printf("%d. %s\n", i+1, list[i].nama);
        }
    }
}
void minumObat(Obat list[], int nomorObat){
    if(list[nomorObat].tersedia){
        printf("GLEKGLEKGLEK... %s berhasil diminum!!!\n\n", list[nomorObat].nama);
        list[nomorObat].tersedia = 0; //obat udah tidak tersedia abis dipilih
    } else{ // Apabila obat yang dipilih tidak ada
        printf("Pilihan nomor tidak tersedia!\n");
    }
}
int main(){
    Obat inventory[MAX_OBAT] = {
        {"Paracetamol", 1}, {"Amoxicillin", 1}, {"Panadol", 1}
        // inisialisasi semua obat di inventory itu tersedia
    };
    int pilihan; 
    int masihAdaObat;
    do{
        daftarObat(inventory, MAX_OBAT);
        printf("Yuk, pilih obat yang mau diminum supaya segera sembuh: ");
        scanf("%d", &pilihan);
        if(pilihan<1 || pilihan > MAX_OBAT || !inventory[pilihan - 1].tersedia){
            //Kalau tersedia == 0, juga dianggap tidak valid
            printf("Pilihan nomor tidak tersedia!\n\n");
        } else{ //pilihan valid
            minumObat(inventory, pilihan-1);
            // array dimulai dari 0, sedangkan input user dimulai dari 1
        }
        masihAdaObat = 0; //buat cek ketersediaan obat
        for(int i=0; i<MAX_OBAT; i++){
            if(inventory[i].tersedia){
                masihAdaObat = 1;
                break;
            }
        }
    } while(masihAdaObat);
    printf("Semua obat udah kamu minum. Hati-hati bisa overdosis!\n");
    return 0;
}
