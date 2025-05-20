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

#define MAX_LINE_LENGTH 1024
#define MAX_FIELD_LENGTH 256

void lihatRuang(Ruangan* ruangan, char * str){
    int x, y;
    x = str[0] - 'A';
    y = stringToInt(&str[1]) - 1;

    printf("--- Detail Ruangan %s ---\n", str);
    printf("Kapasitas  : %d\n", kapasitas_ruangan);

    if (ruanganList[x][y].idDokter != 0)
    {
        printf("Dokter     : Dr. %s\n", ruangan[x][y].usernameDokter);
    }else
    {
        printf("Dokter     : -\n");
    }

    printf("Pasien di dalam ruangan:\n");
    if (ruangan[x][y].totalPasien == 0)
    {
        printf("   Tidak ada pasien di dalam ruangan saat ini.\n");
    } else if (ruang[x][y].totalPasien > 0)
    {
        for (int i = 1; i <= ruangan[x][y].totalPasien; i++)
        {
            printf("   %d. %s\n", i, ruangan[x][y].usernamePasien[i - 1]);
        }
    }
    printf("------------------------------\n");   
}

void gambarDenah(Ruangan* ruangan){
    printf("     ");
    for (int k = 1; k <= ; k++)
    {
        printf("  %d   ", k);
    }
    printf("\n");

    for (int i = 1; i <= lebar_denah; i++)
    {   
        printf("    ");
        for (int k = 1; k <= panjang_denah; k++)
        {
            printf("+-----");
        }
        printf("+\n");

        printf(" %c  ", 'A' + i - 1);

        for (int j = 1; j <= panjang_denah; j++)
        {
            printf("| %c%d  ",'A' + i - 1 ,j);
        }
        printf("|\n");
    }

    printf("    ");
    for (int k = 1; k <= panjang_denah; k++)
    {
        printf("+-----");
    }
    printf("+\n");
}

void denahRumahSakit(char* str){
    if (strcmp(str ,"LIHAT_DENAH") == 0)
    {
        gambarDenah(ruanganList);
    } else if (strcmp(str, "LIHAT_RUANGAN") == 0)
    {
        char ruang[10];
        scanf("%s", ruang);

        lihatRuang(ruanganList, ruang);
    }
    else if(strcmp(str, "LIHAT_SEMUA_ANTRIAN") == 0){
        lihatSemuaAntrian(denah);
    }
}


// int main(){
//     denahRumahSakit("LIHAT_DENAH");
//     return 0;
// }

//gcc src/c/denah.c src/c/queue.c src/c/lihat_antrian.c src/c/utils.c src/c/login.c -o test
