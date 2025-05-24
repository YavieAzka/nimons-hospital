#include "../header/diagnosis.h"
#include "../header/penyakit.h"
#include "../header/utils.h"
#include "../header/config.h"
#include "../header/load.h"
#include "../header/ruangan.h"
#include "../header/queue.h"
#include "../header/boolean.h"

#define MAX_LINE_LENGTH 1024
#define MAX_FIELD_LENGTH 256

void searchRuangan(User user, Ruangan *ruangan){
    for (int i = 0; i < panjang_denah; i++)
    {
        for (int j = 0; j < lebar_denah; j++)
        {
            if (ruanganList[i][j].idDokter == user.id)
            {
                *ruangan = ruanganList[i][j];
                break;
            }
        }
    }
    return;
}
bool cekSuhu(User user, Penyakit penyakit){
    if (user.suhu_tubuh >= penyakit.suhu_tubuh_min && user.suhu_tubuh <= penyakit.suhu_tubuh_max)
    {
        return true;
    }
    return false;
}

bool cekTekananSistolik(User user, Penyakit penyakit){
    if (user.tekanan_darah_sistolik >= penyakit.tekanan_darah_sistolik_min && user.tekanan_darah_sistolik <= penyakit.tekanan_darah_sistolik_max)
    {
        return true;
    }
    return false;
}

bool cekTekananDiastolik(User user, Penyakit penyakit){
    if (user.tekanan_darah_diastolik >= penyakit.tekanan_darah_diastolik_min && user.tekanan_darah_diastolik <= penyakit.tekanan_darah_diastolik_max)
    {
        return true;
    }
    return false;
}

bool cekDetakJantung(User user, Penyakit penyakit){
    if (user.detak_jantung >= penyakit.detak_jantung_min && user.detak_jantung <= penyakit.detak_jantung_max)
    {
        return true;
    }
    return false;
}

bool cekSaturasiOksigen(User user, Penyakit penyakit){
    if (user.saturasi_oksigen >= penyakit.saturasi_oksigen_min && user.saturasi_oksigen <= penyakit.saturasi_oksigen_max)
    {
        return true;
    }
    return false;
}

bool cekKadarGulaDarah(User user, Penyakit penyakit){
    if (user.kadar_gula_darah >= penyakit.kadar_gula_darah_min && user.kadar_gula_darah <= penyakit.kadar_gula_darah_max)
    {
        return true;
    }
    return false;
}

bool cekBeratBadan(User user, Penyakit penyakit){
    if (user.berat_badan >= penyakit.berat_badan_min && user.berat_badan <= penyakit.berat_badan_max)
    {
        return true;
    }
    return false;
}

bool cekTinggiBadan(User user, Penyakit penyakit){
    if (user.tinggi_badan >= penyakit.tinggi_badan_min && user.tinggi_badan <= penyakit.tinggi_badan_max)
    {
        return true;
    }
    return false;
}

bool cekKadarKolesterol(User user, Penyakit penyakit){
    if (user.kadar_kolesterol >= penyakit.kadar_kolesterol_min && user.kadar_kolesterol <= penyakit.kadar_kolesterol_max)
    {
        return true;
    }
    return false;
}

bool cekTrombosit(User user, Penyakit penyakit){
    if (user.trombosit >= penyakit.trombosit_min && user.trombosit <= penyakit.trombosit_max)
    {
        return true;
    }
    return false;
}

char * cekPenyakit(User pasien){
    int i = 0;
    
    while (i < penyakitCount)
    {
        if (cekSuhu(pasien, penyakitList[i]) && cekTekananSistolik(pasien, penyakitList[i]) && cekTekananDiastolik(pasien, penyakitList[i]) && cekDetakJantung(pasien, penyakitList[i]) && cekSaturasiOksigen(pasien, penyakitList[i]) && cekKadarGulaDarah(pasien, penyakitList[i]) && cekBeratBadan(pasien, penyakitList[i]) && cekTinggiBadan(pasien, penyakitList[i]) && cekKadarKolesterol(pasien, penyakitList[i]) && cekTrombosit(pasien, penyakitList[i]))
        {
            return penyakitList[i].name_penyakit;
        }
        i++;
    }
    return "Nothing";
}

void diagnosis(User user){
    Ruangan ruangan;
    searchRuangan(user, &ruangan);

    char namaPenyakit[MAX_NAMA_PENYAKIT];
    if (isEmptyQueue(&ruangan.antrianPasien))
    {
        printf("Tidak ada pasien untuk diperiksa!\n");
    } else{
        if (ruangan.totalPasien == kapasitas_ruangan)
        {
            printf("Ruangan penuh tidak dapat mendiagnosa Pasien dalam antrian\n");
        }
        else{
            User* pasien;
                
            for (int i = 0; i < userCount; i++)
            {
                if (ruangan.antrianPasien.front->idPasien == users[i].id)
                {
                    pasien = &users[i];
                    break;
                }
            }

            strcpy(namaPenyakit, cekPenyakit(*pasien));
        
            if (strcmp(namaPenyakit, "Nothing") == 0)
            {
                printf("%s tidak terdiagnosis penyakit apapun!\n", ruangan.antrianPasien.front->usernamePasien);
            } else{
                printf("%s terdiagnosa penyakit %s!\n", ruangan.antrianPasien.front->usernamePasien, namaPenyakit);
                strcpy(pasien->riwayat_penyakit, namaPenyakit);
            }

            dequeue(&ruangan.antrianPasien, &ruangan.idPasien[ruangan.totalPasien], ruangan.usernamePasien[ruangan.totalPasien]); //Pasien yang telah didiagnosa masuk ke dalam ruangan
            ruangan.totalPasien++; //menambahkan total pasien dalam ruangan
        }
    }
}