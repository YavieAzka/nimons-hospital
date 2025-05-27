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
                return;
            }
        }
    }
    return;
}
bool cekSuhu(User user, Penyakit penyakit){
    return user.suhu_tubuh >= penyakit.suhu_tubuh_min && user.suhu_tubuh <= penyakit.suhu_tubuh_max;
}

bool cekTekananSistolik(User user, Penyakit penyakit){
    return user.tekanan_darah_sistolik >= penyakit.tekanan_darah_sistolik_min && user.tekanan_darah_sistolik <= penyakit.tekanan_darah_sistolik_max;
}

bool cekTekananDiastolik(User user, Penyakit penyakit){
    return user.tekanan_darah_diastolik >= penyakit.tekanan_darah_diastolik_min && user.tekanan_darah_diastolik <= penyakit.tekanan_darah_diastolik_max;
}

bool cekDetakJantung(User user, Penyakit penyakit){
    return user.detak_jantung >= penyakit.detak_jantung_min && user.detak_jantung <= penyakit.detak_jantung_max;
}

bool cekSaturasiOksigen(User user, Penyakit penyakit){
    return user.saturasi_oksigen >= penyakit.saturasi_oksigen_min && user.saturasi_oksigen <= penyakit.saturasi_oksigen_max;
}

bool cekKadarGulaDarah(User user, Penyakit penyakit){
    return user.kadar_gula_darah >= penyakit.kadar_gula_darah_min && user.kadar_gula_darah <= penyakit.kadar_gula_darah_max;
}

bool cekBeratBadan(User user, Penyakit penyakit){
    return user.berat_badan >= penyakit.berat_badan_min && user.berat_badan <= penyakit.berat_badan_max;
}

bool cekTinggiBadan(User user, Penyakit penyakit){
    return user.tinggi_badan >= penyakit.tinggi_badan_min && user.tinggi_badan <= penyakit.tinggi_badan_max;
}

bool cekKadarKolesterol(User user, Penyakit penyakit){
    return user.kadar_kolesterol >= penyakit.kadar_kolesterol_min && user.kadar_kolesterol <= penyakit.kadar_kolesterol_max;
}

bool cekTrombosit(User user, Penyakit penyakit){
    return user.trombosit >= penyakit.trombosit_min && user.trombosit <= penyakit.trombosit_max;
}

char * cekPenyakit(User pasien){
    for (int i = 0; i < penyakitCount; i++)
    {
        if (cekSuhu(pasien, penyakitList[i]) && cekTekananSistolik(pasien, penyakitList[i]) && cekTekananDiastolik(pasien, penyakitList[i]) && cekDetakJantung(pasien, penyakitList[i]) && cekSaturasiOksigen(pasien, penyakitList[i]) && cekKadarGulaDarah(pasien, penyakitList[i]) && cekBeratBadan(pasien, penyakitList[i]) && cekTinggiBadan(pasien, penyakitList[i]) && cekKadarKolesterol(pasien, penyakitList[i]) && cekTrombosit(pasien, penyakitList[i]))
        {
            return penyakitList[i].name_penyakit;
        }
        i++;
    }
    return "";
}

void diagnosis(User user){
    Ruangan ruangan;
    searchRuangan(user, &ruangan);
    char namaPenyakit[MAX_NAMA_PENYAKIT];
    if (isEmptyQueue(&ruangan.antrianPasien))
    {
        printf("Tidak ada pasien untuk diperiksa!\n");
    } else{
        User* pasien;
        
        for (int i = 0; i < userCount; i++)
        {
            if (ruangan.antrianPasien.front->idPasien == users[i].id)
            {
                pasien = &users[i];
                break;
            }
        }
        
        printf("%d\n", pasien->tinggi_badan);
        if (strcmp(pasien->riwayat_penyakit, "") == 0)
        {
            strcpy(namaPenyakit, cekPenyakit(*pasien));
        
            if (strcmp(namaPenyakit, "Sehat") == 0)
            {
                printf("%s tidak terdiagnosis penyakit apapun!\n", pasien->username);
                
            } else{
                strcpy(pasien->riwayat_penyakit, namaPenyakit);
                printf("%s terdiagnosa penyakit %s!\n", pasien->username, pasien->riwayat_penyakit);
            }

        } else{
            printf("Pasian telah terdiagnosis, arahkan pasien menuju ke Ngobatin.\n");
        }
    }
}