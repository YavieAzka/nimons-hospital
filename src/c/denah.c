#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "../header/denah.h"
#include "../header/utils.h"
#include "../header/login.h"
#include "../header/user.h"
#include "../header/lihat_antrian.h"
#include "../header/queue.h"
#include "../header/config.h"
#include "../header/load.h"

#define MAX_LINE_LENGTH 1024
#define MAX_FIELD_LENGTH 256

int panjang_denah_eff = 0;
int lebar_denah_eff = 0;

void lihatRuang(char * str){
    int x, y;
    x = str[0] - 'A';
    y = stringToInt(&str[1]) - 1;

    printf("--- Detail Ruangan %s ---\n", str);
    printf("Kapasitas  : %d\n", kapasitas_ruangan);

    if (ruanganList[x][y].idDokter != 0)
    {
        printf("Dokter     : Dr. %s\n", ruanganList[x][y].usernameDokter);
    }else
    {
        printf("Dokter     : -\n");
    }

    printf("Pasien di dalam ruangan:\n");
    if (ruanganList[x][y].totalPasien == 0)
    {
        printf("   Tidak ada pasien di dalam ruangan saat ini.\n");
    } else if (ruanganList[x][y].totalPasien > 0)
    {
        for (int i = 1; i <= ruanganList[x][y].totalPasien; i++)
        {
            printf("   %d. %s\n", i, ruanganList[x][y].usernamePasien[i - 1]);
        }
    }
    printf("------------------------------\n");   
}

void gambarDenah(){
    printf("     ");
    for (int k = 1; k <= lebar_denah; k++)
    {
        printf("  %d   ", k);
    }
    printf("\n");

    for (int i = 1; i <= panjang_denah; i++)
    {   
        printf("    ");
        for (int k = 1; k <= lebar_denah; k++)
        {
            printf("+-----");
        }
        printf("+\n");

        printf(" %c  ", 'A' + i - 1);

        for (int j = 1; j <= lebar_denah; j++)
        {
            printf("| %c%d  ",'A' + i - 1 ,j);
        }
        printf("|\n");
    }

    printf("    ");
    for (int k = 1; k <= lebar_denah; k++)
    {
        printf("+-----");
    }
    printf("+\n");
}

void denahRumahSakit(char* str){
    if (strcmp(str ,"LIHAT_DENAH") == 0)
    {
        gambarDenah();
    } else if (strcmp(str, "LIHAT_RUANGAN") == 0)
    {
        char ruang[10];
        scanf("%s", ruang);

        lihatRuang(ruang);
    } 
    else if(strcmp(str, "LIHAT_SEMUA_ANTRIAN") == 0){
        lihatSemuaAntrian();
    } 
    else if (strcmp(str, "UBAH_DENAH") == 0)
    {
        ubahDenah();
    } 
    else if (strcmp(str, "PINDAH_DOKTER") == 0)
    {
        pindahDokter();
    }
    
    
}

void ubahDenah(){
    //search eff ukuran denah
    for (int i = 0; i < panjang_denah; i++) {
        for (int j = 0; j < lebar_denah; j++) {
            if (ruanganList[i][j].idDokter != 0) {
                if (i + 1 > panjang_denah_eff) panjang_denah_eff = i + 1;
                if (j + 1 > lebar_denah_eff) lebar_denah_eff = j + 1;
            }
        }
    }

    int newPanjang, newLebar;
    printf("Masukkan ukuran denah yang baru: ");
    scanf("%d %d", &newPanjang, &newLebar);
    while (newLebar > MAX_RUANGAN || newPanjang > MAX_RUANGAN){
        printf("Masukkan Nilai Panjang dan Lebar yang tidak melebihi capacity Ruangan (5 5): \n");
        scanf("%d %d", &newPanjang, &newLebar);
    }
    
    if (newLebar < lebar_denah_eff || newPanjang < panjang_denah_eff) {
        int baris = -1, kolom = -1;
        cariRuang(&baris, &kolom, newLebar, newPanjang);
        printf("Tidak dapat mengubah ukuran denah. Ruangan %c%d masih ditempati oleh Dr. %s. Silakan pindahkan dokter terlebih dahulu.\n",
               'A' + baris, kolom + 1, ruanganList[baris][kolom].usernameDokter);
    } else {
        lebar_denah = newLebar;
        panjang_denah = newPanjang;
        printf("Denah rumah sakit berhasil diubah menjadi %d baris dan %d kolom.\n", newPanjang, newLebar);
    }
}

void pindahDokter(){
    char ruang1[10], ruang2[10];
    scanf("%s %s", ruang1, ruang2);
    int baris1, kolom1, baris2, kolom2;

    baris1 = ruang1[0] - 'A'; kolom1 = stringToInt(&ruang1[1]) - 1;
    baris2 = ruang2[0] - 'A'; kolom2 = stringToInt(&ruang2[1]) - 1;
    
    Ruangan r1, r2;
    
    r1 = ruanganList[baris1][kolom1];
    r2 = ruanganList[baris2][kolom2];

    if (r1.idDokter == 0)
    {
        printf("Pemindahan gagal. Ruangan %c%d Kosong.\n", 'A' + baris1 + 1, kolom1 + 1);
    } else{
        if (r2.idDokter == 0)
        {
            ruanganList[baris2][kolom2] = r1;
            ruanganList[baris1][kolom1] = r2; //jadi kosong
            printf("Dr. %s berhasil dipindahkan dari ruangan %c%d ke ruangan %c%d.\n", r1.usernameDokter, 'A' + baris1, kolom1 + 1, 'A' +  baris2, kolom2 + 1);
        } else{
            printf("Pemindahan gagal. Ruangan %c%d Sudah ditempati.\n", 'A' + baris2, kolom2 + 1);
        }
    }
}

void cariRuang(int *baris, int *kolom, int newLebar, int newPanjang) {
    for (int i = 0; i < panjang_denah; i++) {
        for (int j = 0; j < lebar_denah; j++) {
            if (i >= newPanjang || j >= newLebar) {
                if (ruanganList[i][j].idDokter != 0) {
                    *baris = i;
                    *kolom = j;
                    return;
                }
            }
        }
    }
}

/*int main(int argc, char* argv[]) {
    if (argc != 2) {
        printf("Usage: %s <nama_folder>\n", argv[0]);
        return 1;
    }

    char* folder = argv[1];

    // ====================== LOAD FILE START ======================
    printf("Loading...\n");
    load_all_data(folder);
    printf("Data berhasil dimuat dari folder: %s\n", folder);
    bool status = true;
    while (status == true)
    {
        char str[100];
        scanf("%s", str);
        denahRumahSakit(str);
    }
    return 0;
}*/

//gcc src/c/denah.c src/c/queue.c src/c/lihat_antrian.c src/c/utils.c src/c/login.c src/c/load.c -o test
