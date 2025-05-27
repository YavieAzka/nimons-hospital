#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "../header/boolean.h"
#include "../header/user.h"
#include "../header/penyakit.h"
#include "../header/obat.h"
#include "../header/obatPenyakit.h"
#include "../header/ngobatin.h"

void ngobatin(User currentUser) {
    
    if (strcmp(currentUser.role, "dokter") != 0) {
        printf("Maaf ya, fitur ini cuma bisa dipakai sama dokter. Coba panggil dokternya dulu deh!\n");
        return;
    }

    printf("Yuk, saatnya bantu pasien sembuh!\n");

    char nama_pasien[MAX_USERNAME];
    printf("Masukkan username pasien yang mau diobatin: ");
    scanf(" %[^\n]", nama_pasien);

    User* target = NULL;
    for (int i = 0; i < userCount; i++) {
        if (strcmp(users[i].username, nama_pasien) == 0 && strcmp(users[i].role, "pasien") == 0) {
            target = &users[i];
            break;
        }
    }

    if (target == NULL) {
        printf("Hmm... pasien dengan username '%s' nggak ketemu nih. Coba cek lagi ya.\n", nama_pasien);
        return;
    }

    if (strcmp(target->riwayat_penyakit, "") == 0) {
        printf("Pasien ini belum ada diagnosis penyakit, dok. Kasih diagnosis dulu ya biar bisa dikasih obat yang tepat.\n");
        return;
    }

    int id_penyakit = -1;
    for (int i = 0; i < penyakitCount; i++) {
        if (strcmp(penyakitList[i].name_penyakit, target->riwayat_penyakit) == 0) {
            id_penyakit = penyakitList[i].id;
            break;
        }
    }

    if (id_penyakit == -1) {
        printf("Wah, nama penyakit '%s' nggak ada di database kita, dok. Coba dicek lagi, mungkin typo.\n", target->riwayat_penyakit);
        return;
    }

    int found = 0;
    for (int i = 0; i < obatPenyakitCount; i++) {
        if (obatPenyakitList[i].id_penyakit == id_penyakit) {
            printf("\nPasien '%s' terdiagnosis menderita %s.\n", target->username, target->riwayat_penyakit);
            printf("Berikut daftar obat yang harus diberikan, urutannya jangan sampai kebalik ya!\n\n");

            for (int j = 0; j < obatPenyakitList[i].jumlah_obat; j++) {
                int id_obat = obatPenyakitList[i].id_obat[j];
                int foundObat = 0;
                for (int k = 0; k < obatCount; k++) {
                    if (obatList[k].id == id_obat) {
                        printf(">> Obat ke-%d: %s\n", j + 1, obatList[k].nama);
                        foundObat = 1;
                        break;
                    }
                }
                if (!foundObat) {
                    printf(">> Obat ke-%d: [Data obat dengan ID %d nggak ditemukan, ada yang janggal nih!]\n", j + 1, id_obat);
                }
            }

            printf("\nPastikan obat diberikan satu per satu sesuai urutan di atas ya. Semangat menyembuhkan pasien!\n");
            found = 1;
            break;
        }
    }

    if (!found) {
        printf("Sepertinya belum ada data obat untuk penyakit '%s'. Coba input dulu di sistem ya, dok!\n", target->riwayat_penyakit);
    }
}
