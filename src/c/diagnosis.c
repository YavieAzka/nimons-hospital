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
boolean cekSuhu(User user, Penyakit penyakit){
    return user.suhu_tubuh >= penyakit.suhu_tubuh_min && user.suhu_tubuh <= penyakit.suhu_tubuh_max;
}

boolean cekTekananSistolik(User user, Penyakit penyakit){
    return user.tekanan_darah_sistolik >= penyakit.tekanan_darah_sistolik_min && user.tekanan_darah_sistolik <= penyakit.tekanan_darah_sistolik_max;
}

boolean cekTekananDiastolik(User user, Penyakit penyakit){
    return user.tekanan_darah_diastolik >= penyakit.tekanan_darah_diastolik_min && user.tekanan_darah_diastolik <= penyakit.tekanan_darah_diastolik_max;
}

boolean cekDetakJantung(User user, Penyakit penyakit){
    return user.detak_jantung >= penyakit.detak_jantung_min && user.detak_jantung <= penyakit.detak_jantung_max;
}

boolean cekSaturasiOksigen(User user, Penyakit penyakit){
    return user.saturasi_oksigen >= penyakit.saturasi_oksigen_min && user.saturasi_oksigen <= penyakit.saturasi_oksigen_max;
}

boolean cekKadarGulaDarah(User user, Penyakit penyakit){
    return user.kadar_gula_darah >= penyakit.kadar_gula_darah_min && user.kadar_gula_darah <= penyakit.kadar_gula_darah_max;
}

boolean cekBeratBadan(User user, Penyakit penyakit){
    return user.berat_badan >= penyakit.berat_badan_min && user.berat_badan <= penyakit.berat_badan_max;
}

boolean cekTinggiBadan(User user, Penyakit penyakit){
    return user.tinggi_badan >= penyakit.tinggi_badan_min && user.tinggi_badan <= penyakit.tinggi_badan_max;
}

boolean cekKadarKolesterol(User user, Penyakit penyakit){
    return user.kadar_kolesterol >= penyakit.kadar_kolesterol_min && user.kadar_kolesterol <= penyakit.kadar_kolesterol_max;
}

boolean cekTrombosit(User user, Penyakit penyakit){
    return user.trombosit >= penyakit.trombosit_min && user.trombosit <= penyakit.trombosit_max;
}

void cekPenyakit(User* pasien){
    // strcpy(pasien->riwayat_penyakit, "Sehat");
    // printf("=== DEBUG DATA PASIEN ===\n");
    // printf("Username: %s\n", pasien->username);
    // printf("Suhu: %.2f\n", pasien->suhu_tubuh);
    // printf("Tekanan Sistolik: %d\n", pasien->tekanan_darah_sistolik);
    // printf("Tekanan Diastolik: %d\n", pasien->tekanan_darah_diastolik);
    // printf("Detak Jantung: %d\n", pasien->detak_jantung);
    // printf("Saturasi Oksigen: %.2f\n", pasien->saturasi_oksigen);
    // printf("Kadar Gula Darah: %d\n", pasien->kadar_gula_darah);
    // printf("Berat Badan: %.2f\n", pasien->berat_badan);
    // printf("Tinggi Badan: %d\n", pasien->tinggi_badan);
    // printf("Kadar Kolesterol: %d\n", pasien->kadar_kolesterol);
    // printf("Trombosit: %d\n", pasien->trombosit);
    for (int i = 0; i < penyakitCount; i++)
    {
        // printf("--- Penyakit ke-%d: %s ---\n", i, penyakitList[i].name_penyakit);
        // printf("Suhu: %.2f - %.2f\n", penyakitList[i].suhu_tubuh_min, penyakitList[i].suhu_tubuh_max);
        // printf("Tekanan Sistolik: %d - %d\n", penyakitList[i].tekanan_darah_sistolik_min, penyakitList[i].tekanan_darah_sistolik_max);
        // printf("Tekanan Diastolik: %d - %d\n", penyakitList[i].tekanan_darah_diastolik_min, penyakitList[i].tekanan_darah_diastolik_max);
        // printf("Detak Jantung: %d - %d\n", penyakitList[i].detak_jantung_min, penyakitList[i].detak_jantung_max);
        // printf("Saturasi Oksigen: %.2f - %.2f\n", penyakitList[i].saturasi_oksigen_min, penyakitList[i].saturasi_oksigen_max);
        // printf("Kadar Gula Darah: %d - %d\n", penyakitList[i].kadar_gula_darah_min, penyakitList[i].kadar_gula_darah_max);
        // printf("Berat Badan: %.2f - %.2f\n", penyakitList[i].berat_badan_min, penyakitList[i].berat_badan_max);
        // printf("Tinggi Badan: %d - %d\n", penyakitList[i].tinggi_badan_min, penyakitList[i].tinggi_badan_max);
        // printf("Kadar Kolesterol: %d - %d\n", penyakitList[i].kadar_kolesterol_min, penyakitList[i].kadar_kolesterol_max);
        // printf("Trombosit: %d - %d\n", penyakitList[i].trombosit_min, penyakitList[i].trombosit_max);
    
        if (cekSuhu(*pasien, penyakitList[i]) && cekTekananSistolik(*pasien, penyakitList[i]) && cekTekananDiastolik(*pasien, penyakitList[i]) && cekDetakJantung(*pasien, penyakitList[i]) && cekSaturasiOksigen(*pasien, penyakitList[i]) && cekKadarGulaDarah(*pasien, penyakitList[i]) && cekBeratBadan(*pasien, penyakitList[i]) && cekTinggiBadan(*pasien, penyakitList[i]) && cekKadarKolesterol(*pasien, penyakitList[i]) && cekTrombosit(*pasien, penyakitList[i]))
        {
            // printf("%s cek\n",penyakitList[i].name_penyakit);
            strcpy(pasien->riwayat_penyakit, penyakitList[i].name_penyakit);
            break;
        }
        // printf("%d debug ceksuhu\n", cekSuhu(*pasien, penyakitList[i]));
        // printf("%d debug cekTekananSistolik\n", cekTekananSistolik(*pasien, penyakitList[i]));
        // printf("%d debug cekTekananDiastolik\n", cekTekananDiastolik(*pasien, penyakitList[i]));
        // printf("%d debug cekDetakJantung\n", cekDetakJantung(*pasien, penyakitList[i]));
        // printf("%d debug cekSaturasiOksigen\n", cekSaturasiOksigen(*pasien, penyakitList[i]));
        // printf("%d debug cekKadarGulaDarah\n", cekKadarGulaDarah(*pasien, penyakitList[i]));
        // printf("%d debug cekBeratBadan\n", cekBeratBadan(*pasien, penyakitList[i]));
        // printf("%d debug cekTinggiBadan\n", cekTinggiBadan(*pasien, penyakitList[i]));
        // printf("%d debug cekKadarKolesterol\n", cekKadarKolesterol(*pasien, penyakitList[i]));
        // printf("%d debug cekTrombosit\n", cekTrombosit(*pasien, penyakitList[i]));
        // printf("%d debug i\n", i);
        // printf("%s\n",penyakitList[i].name_penyakit);
        // printf("%d debug id\n", penyakitList[i].id);
    }
    
}

void diagnosis(User user){
    Ruangan ruangan;
    searchRuangan(user, &ruangan);
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
        if (strcmp(pasien->riwayat_penyakit, "") == 0)
        {
            cekPenyakit(pasien);
            // printf("Riwayat penyakit %s\n", pasien->riwayat_penyakit);
            if (strcmp(pasien->riwayat_penyakit, "Sehat") == 0)
            {
                printf("%s tidak terdiagnosis penyakit apapun!\n", pasien->username);
                
            } else{
                printf("%s terdiagnosa penyakit %s!\n", pasien->username, pasien->riwayat_penyakit);
            }

        } else{
            printf("Pasian telah terdiagnosis, arahkan pasien menuju ke Ngobatin.\n");
        }
    }
}