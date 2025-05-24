#include "../header/load.h"
#include "../header/obatPenyakit.h"
#include "../header/obat.h"
#include "../header/penyakit.h"
#include "../header/minumobat.h"
#include "../header/minumpenawar.h"
#include "../header/user.h"

const char* getNamaObatWithId(int idObat) {
    for (int i = 0; i < obatCount; i++) {
        if (obatList[i].id == idObat) {
            return obatList[i].nama;
        }
    }
}

int getIdWithNamaObat(char *namaObat) {
    for (int i = 0; i < obatCount; i++) {
        if (strcmp(namaObat, obatList[i].nama) == 0) {
            return obatList[i].id;
        }
    }
}

int getUrutanWithIdObat(int idObat) {
    for(int i = 0; i < obatPenyakitCount; i ++) {
        if(obatPenyakitList[i].id_obat == idObat) {
            return obatPenyakitList[i].jumlah_obat;
        }
    }
}

int getIdPenyakitWithRiwayat(const char* riwayat) {
    for (int i = 0; i < penyakitCount; i++) {
        if (strcmp(riwayat, penyakitList[i].name_penyakit) == 0) {
            return penyakitList[i].id;
        }
    }
}

//Sebagai tracker untuk fungsi minumobat() di minumobat.c
void getUrutanMinum(Obat list[], int nomorObat, int *idxUrutanMinum) {
        int id = getIdWithNamaObat(list[nomorObat].nama);
        int urutan = getUrutanWithIdObat(id);
        urutanMinumObat[*idxUrutanMinum] = urutan;
        (*idxUrutanMinum)++;
}

//Check apakah input pemasukan minumobat sama/tidak dengan urutan yang benar
int checkUrutanMinum(Obat list[], int IdPenyakit, Perut *P, int urutanMinumObat[], int idxUrutanMinum) {
    //Check banyak obat yang harus diminum
    int jumlahObat = 0;
    for(int i = 0; i < obatPenyakitCount; i++) {
        P[i].IdObat = obatPenyakitList[i].id_obat;
        P[i].urutanMinum = obatPenyakitList[i].jumlah_obat;
            jumlahObat++;     
    }

    //urut membesar sesuai urutan_minum;
    for(int i = 0; i < jumlahObat; i++) {
        for(int j = 0; j < jumlahObat - i - 1; j++) {
            if(P[j].urutanMinum > P[j+1].urutanMinum) {
                int temp = P[j].urutanMinum;
                P[j].urutanMinum = P[j+1].urutanMinum;
                P[j+1].urutanMinum = temp;
            }
        }
    }

    int urutanBenar = 1; 
    for(int i = 0; i < idxUrutanMinum; i++) {
        if(urutanMinumObat[i] != P[i].urutanMinum) {
            urutanBenar = 0;
        }
    }

    return urutanBenar;
}

void minumpenawar(User *pasien) {
    int IdPenyakit = getIdPenyakitWithRiwayat(pasien->riwayat_penyakit);
    int status = checkUrutanMinum(list, IdPenyakit, P, urutanMinumObat, idxUrutanMinum);
    const char* obatName = NULL;

    if(status == 1 && idxUrutanMinum == 0) { //Belum ada obat yang diminum
        printf("Perut kosong!! Belum ada obat yang dimakan.");
    } else if(status == 0) {
        
        //ada yang urutannya tidak sesuai
        int urutanLast = urutanMinumObat[idxUrutanMinum - 1];
        for(int i = 0; i < obatCount; i++) {
            //Ambil nama obat yang terakhir dimasukkan
            int idObat = obatList[i].id;
            int urutan;

            for(int j = 0; j < obatPenyakitCount; j++) {
                if(obatPenyakitList[j].id_obat == idObat && obatPenyakitList[j].id_penyakit == IdPenyakit) {
                    urutan = obatPenyakitList[j].jumlah_obat;
                    break;
                }
            }
            if(urutan == urutanLast) {
                obatName = obatList[i].nama;

                //Update inventory
                for(int k = 0; k < MAX_OBAT_PER_PENYAKIT; k++) {
                    if(strcmp(list[k].nama, obatName) == 0) {
                        list[k].tersedia = 1;
                    }
                }
            } 
        }
        printf("Uwekkk!!! %s keluar dan kembali ke inventory", obatName);
    }
}
