#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "../header/denah.h"
#include "../header/utils.h"
#include "../header/login.h"
#include "../header/user.h"

#define MAX_LINE_LENGTH 1024
#define MAX_FIELD_LENGTH 256

void lihatRuang(Denah denah, char * str){
    int x, y;
    x = str[0] - 'A';
    y = stringToInt(&str[1]) - 1;

    printf("--- Detail Ruangan %s ---\n", str);
    printf("Kapasitas  : %d\n", denah.MaxPasien);

    if (denah.daftarRuang[x][y].idDokter != 0)
    {
        printf("Dokter     : Dr. %s\n", denah.daftarRuang[x][y].usernameDokter);
    }else
    {
        printf("Dokter     : -\n");
    }

    printf("Pasien di dalam ruangan:\n");
    if (denah.daftarRuang[x][y].totalPasien == 0)
    {
        printf("   Tidak ada pasien di dalam ruangan saat ini.\n");
    } else if (denah.daftarRuang[x][y].totalPasien > 0)
    {
        for (int i = 1; i <= denah.daftarRuang[x][y].totalPasien; i++)
        {
            printf("   %d. %s\n", i, denah.daftarRuang[x][y].usernamePasien[i - 1]);
        }
    }
    printf("------------------------------\n");   
}
void getUsernameFromArray(int id, char* str){
    int user_count = 0;
    User* users = getUserData("data/user.csv", &user_count);

    for (int i = 0; i < user_count; i++)
    {
        if (users[i].id == id)
        {
            strcpy(str, users[i].username);
        }
    }
}

void gambarDenah(Denah denah){
    printf("     ");
    for (int k = 1; k <= denah.kolomMax; k++)
    {
        printf("  %d   ", k);
    }
    printf("\n");

    for (int i = 1; i <= denah.barisMax; i++)
    {   
        printf("    ");
        for (int k = 1; k <= denah.kolomMax; k++)
        {
            printf("+-----");
        }
        printf("+\n");

        printf(" %c  ", 'A' + i - 1);

        for (int j = 1; j <= denah.kolomMax; j++)
        {
            printf("| %c%d  ",'A' + i - 1 ,j);
        }
        printf("|\n");
    }

    printf("    ");
    for (int k = 1; k <= denah.kolomMax; k++)
    {
        printf("+-----");
    }
    printf("+\n");
}

void denahRumahSakit(char* str){
    FILE *file = fopen("data/config.txt", "r");
    if (file == NULL) {
        perror("Gagal membuka file config.txt");
        return;
    }

    Denah denah;

    char line[MAX_LINE_LENGTH];

    if (fgets(line, sizeof(line), file)) {
        int i = 0;
        denah.barisMax = parse_int(line, &i);
        denah.kolomMax = parse_int(line, &i);
    }

    if (fgets(line, sizeof(line), file)) {
        int i = 0;
        denah.MaxPasien = parse_int(line, &i);
    }
    
    for (int i = 0; i < denah.barisMax; i++)
    {
        for(int j = 0; j < denah.kolomMax; j++){
            if (fgets(line, sizeof(line), file)) {
                int pos = 0;
                int id = 0;
                denah.daftarRuang[i][j].idDokter= parse_int(line, &pos);
                denah.daftarRuang[i][j].totalPasien = 0;
                
                if (denah.daftarRuang[i][j].idDokter != 0) {
                    getUsernameFromArray(denah.daftarRuang[i][j].idDokter, denah.daftarRuang[i][j].usernameDokter);
                    denah.barisEff = i;
                    denah.kolomEff = j;

                    while (line[pos] != '\0' && line[pos] != '\n') {
                        int id_pasien = parse_int(line, &pos);
                        if (id_pasien > 0) {
                            denah.daftarRuang[i][j].idPasien[denah.daftarRuang[i][j].totalPasien++] = id_pasien;
                            getUsernameFromArray(denah.daftarRuang[i][j].idPasien[id], denah.daftarRuang[i][j].usernamePasien[id]);
                            id++;
                        } else {
                            break;
                        }   
                    }
                }   
            }
        }
    }  
    
    if (strcmp(str ,"LIHAT_DENAH") == 0)
    {
        gambarDenah(denah);
    } else if (strcmp(str, "LIHAT_RUANGAN") == 0)
    {
        char ruang[10];
        scanf("%s", ruang);

        lihatRuang(denah, ruang);
    }
}


int main(){
    denahRumahSakit("LIHAT_DENAH");
    return 0;
}

//gcc src/c/denah.c src/c/utils.c src/c/login.c -o test