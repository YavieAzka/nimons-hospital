
// Include any necessary headers
#include <stdio.h>
#include <unistd.h> 
#include <stdlib.h>
#include "../header/user.h"
#include "../header/login.h"
#include "../header/help.h"
#include "../header/boolean.h"
#include "../header/cariuser.h"
#include "../header/diagnosis.h"
#include "../header/register.h"
#include "../header/logout.h"
#include "../header/lupa_password.h"
#include "../header/lihatUser.h"
#include "../header/set.h"
#include "../header/utils.h"
#include "../header/obat.h"
#include "../header/obatPenyakit.h"
#include "../header/penyakit.h"
#include "../header/load.h"
#include "../header/config.h"
#include "../header/denah.h"
#include "../header/exit.h"
#include "../header/save.h"
#include "../header/tambah_dokter.h"
#include "../header/stack.h"
#include "../header/antrian-saya.h"
#include "../header/ngobatin.h"
#include "../header/daftar-check-up.h"
#include "../header/akubolehpulang.h"
#include "../header/minum-obat.h"
#include "../header/minumpenawar.h"
#include "../header/lihat_antrian.h"

void printCommandMessage(){
    printf("\033[1;35m--------------------------------------------------------------\033[0m\n");
    printf("Masukkan perintah (Ketik [HELP] untuk melihat daftar perintah): \n");
}      


void handleManager(User* user, Status* status) {
    char input[50];
    while (*status == MANAGER_LOGGED_IN) {
        printCommandMessage();
        printf("\033[93m>>> \033[0m");
        scanf("%s", input);
        if (strcmp(input, "HELP") == 0) {
            help(*user);     
        }

        else if(strcmp(input, "TAMBAH_DOKTER") == 0|| strcmp(input, "2") == 0){
            tambahDokter();
        }
        else if(strcmp(input, "ASSIGN_DOKTER") == 0 || strcmp(input, "3") == 0){
            assignDokter();
        }
        else if (strcmp(input, "CARI_USER") == 0 || strcmp(input, "7") == 0) {
            cariUser();
        }
        else if (strcmp(input, "CARI_DOKTER") == 0 || strcmp(input, "9") == 0) {
            cariDokter();
        }
        else if (strcmp(input, "CARI_PASIEN") == 0 || strcmp(input, "8") == 0) {
            cariPasien();
        } 
        else if (strcmp(input, "LIHAT_USER") == 0 || strcmp(input, "4") == 0) {
            lihatUser(input);
        }
        else if (strcmp(input, "LIHAT_PASIEN") == 0 || strcmp(input, "5") == 0) {
            lihatPasien(input);
        }
        else if (strcmp(input, "LIHAT_DOKTER") == 0 || strcmp(input, "6") == 0) {
            lihatDokter(input);
        }  
        else if (strcmp(input, "LIHAT_DENAH") == 0 || strcmp(input, "10") == 0) {
            gambarDenah();
            //return;
        }
        else if (strcmp(input, "LIHAT_RUANGAN") == 0 || strcmp(input, "11") == 0) {
            char ruanganInput[10];
            printf("Masukkan ruangan yang ingin dilihat: ");
            scanf("%s", ruanganInput);
            lihatRuang(ruanganInput);
            //return;
        }
        else if (strcmp(input, "UBAH_DENAH") == 0 || strcmp(input, "13") == 0) {
            ubahDenah();
            //return;
        }
        else if (strcmp(input, "PINDAH_DOKTER") == 0 || strcmp(input, "14") == 0) {
            pindahDokter();
        }
        else if (strcmp(input, "LIHAT_SEMUA_ANTRIAN") == 0 || strcmp(input, "12") == 0 ) {
            lihatSemuaAntrian();
            //return;
        }
        else if (strcmp(input, "LOGOUT") == 0 || strcmp(input, "1") == 0) {
            logout(user, status);
            return;
        } 
        else if (strcmp(input, "EXIT") == 0 || strcmp(input, "15") == 0) {
            *status = EXIT;
            exit_program();
            return;
        }
        else{
            printf("Perintah tidak dikenali. Mohon berikan perintah yang valid!\n");
        } 
    }
}

void handleDokter(User* user, Status* status) {
    char input[50];
    while (*status == DOKTER_LOGGED_IN) {
        printCommandMessage();
        printf("\033[93m>>> \033[0m");
        scanf("%s", input);

        if (strcmp(input, "HELP") == 0 ) {
            help(*user);
        }
        else if (strcmp(input, "LIHAT_ANTRIAN") == 0 || strcmp(input, "2") == 0) {
            // implementasi modul lihat_antrian(); // placeholder
        }
        else if (strcmp(input, "DIAGNOSIS") == 0 || strcmp(input, "3") == 0) {
            diagnosis(*user);
        }
        else if (strcmp(input, "NGOBATIN") == 0 || strcmp(input, "4") == 0) {
            ngobatin(*user);
        }
        else if (strcmp(input, "LOGOUT") == 0 || strcmp(input, "1") == 0) {
            logout(user, status);
            return;
        }
        else if (strcmp(input, "LIHAT_DENAH") == 0 || strcmp(input, "5") == 0) {
            gambarDenah();
            //return;
        }
        else if (strcmp(input, "LIHAT_RUANGAN") == 0 || strcmp(input, "6") == 0) {
            char ruanganInput[10];
            printf("Masukkan ruangan yang ingin dilihat: ");
            scanf("%s", ruanganInput);
            lihatRuang(ruanganInput);
            //return;
        }
        else if (strcmp(input, "EXIT") == 0 || strcmp(input, "7") == 0) {
            *status = EXIT;
            exit_program();
            return;
        }
        else{
            printf("Perintah tidak dikenali. Mohon berikan perintah yang valid!\n");
        } 
    }
}

void handlePasien(User* user, Status* status) {
    char input[50];
    while (*status == PASIEN_LOGGED_IN) {
        printCommandMessage();
        printf("\033[93m>>> \033[0m");
        scanf("%s", input);

        if (strcmp(input, "HELP") == 0) {
            help(*user);
        }
        else if (strcmp(input, "DAFTAR_CHECKUP") == 0 || strcmp(input, "2") == 0) {
            daftarCheckUp(user);
        } 
        else if (strcmp(input, "ANTRIAN_SAYA") == 0 || strcmp(input, "3") == 0) {
            antrianSaya(user);
        } 
        else if (strcmp(input, "MINUM_OBAT") == 0 || strcmp(input, "4") == 0) {
            minumObat(user);
        } 
        else if (strcmp(input, "MINUM_PENAWAR") == 0 || strcmp(input, "5") == 0) {
            minumPenawar(user);
        } 
        else if (strcmp(input, "DOK_AKU_MAU_PULANG") == 0 || strcmp(input, "6") == 0) {
            akubolehpulang(user);
        } 
        else if (strcmp(input, "LOGOUT") == 0 || strcmp(input, "1") == 0) {
            logout(user, status);
            return;
        }
        else if (strcmp(input, "LIHAT_DENAH") == 0 || strcmp(input, "7") == 0) {
            gambarDenah();

        }
        else if (strcmp(input, "LIHAT_RUANGAN") == 0 || strcmp(input, "8") == 0) {
            char ruanganInput[10];
            printf("Masukkan ruangan yang ingin dilihat: ");
            scanf("%s", ruanganInput);
            lihatRuang(ruanganInput);

        }
        else if(strcmp(input, "EXIT") == 0 || strcmp(input, "9") == 0){
            *status = EXIT;
            exit_program();
            return;
        }
        else{
            printf("Perintah tidak dikenali. Mohon berikan perintah yang valid!\n");
        } 
    }
}

void printWelcomeMessage(){
    printf("\033[33m");
    printf(" __      __       .__                                  __                  .__                               .__                         .__  __         .__   \n");
    printf("/  \\    /  \\ ____ |  |   ____  ____   _____   ____   _/  |_  ____     ____ |__| _____   ____   ____   ______ |  |__   ____  ____________ |__|/  |______  |  |  \n");
    printf("\\   \\/\\/   // __ \\|  | _/ ___\\/  _ \\ /     \\_/ __ \\  \\   __\\/  _ \\   /    \\|  |/     \\ /  _ \\ /    \\ /  ___/ |  |  \\ /  _ \\/  ___\\/\\____\\|  \\   __\\__  \\ |  |  \n");
    printf(" \\        /\\  ___/|  |_\\  \\__(  <_> )  Y Y  \\  ___/   |  | (  <_> ) |   |  \\  |  Y Y  (  <_> )   |  \\\\___ \\  |   Y  (  <_> )___ \\ |  |_> >  ||  |  / __ \\|  |__\n");
    printf("  \\__/\\  /  \\___  >____/\\___  >____/|__|_|  /\\___  >  |__|  \\____/  |___|  /__|__|_|  /\\____/|___|  /____  > |___|  /\\____/____  >|   __/|__||__| (____  /____/\n");
    printf("       \\/       \\/          \\/            \\/     \\/                      \\/         \\/            \\/     \\/       \\/           \\/ |__|                 \\/      \n");
    printf("\033[0m");
}

void printOpeningMessage(){
    printf("+===================================================+\n");
    printf("|    SILAKAN LOGIN DENGAN MENGETIK \033[92m[LOGIN]\033[0m ATAU     |\n");
    printf("|    MELAKUKAN REGISTER DENGAN MENGETIK \033[92m[REGISTER]\033[0m  |\n");
    printf("+===================================================+\n");
}

int main(int argc, char* argv[]) { 
    if (argc != 2) {
        printf("Usage: %s <nama_folder>\n", argv[0]);
        return 1;
    }

    char* folder = argv[1];

    // ====================== LOAD FILE START ======================
    printf("Loading...\n");
    load_all_data(folder);
    printf("Data berhasil dimuat dari folder: %s\n", folder);
    // ====================== LOAD FILE END ======================

    // ====================== PROGRAM START ======================
    //list of array for processingL: users, penyakitList, obatList, penyakitObatList
    
    Status status = USER_LOGGED_OFF;
    User current_user; char userInput[10]; 

    
    while(status != EXIT){
        printWelcomeMessage();
        printOpeningMessage();
        printf("\033[93m>>> \033[0m");
        scanf("%s", userInput);

        //================ LOGIN ================//
        if(strcmp(userInput, "LOGIN") == 0){        
            current_user = login(&current_user);
            if(strcmp(current_user.role, "dokter") == 0){
                status = DOKTER_LOGGED_IN;
            }
            if(strcmp(current_user.role, "pasien") == 0){
                status = PASIEN_LOGGED_IN;
            }
            if(strcmp(current_user.role, "manager") == 0){
                status = MANAGER_LOGGED_IN;
            }
            //printf("Apa yang bisa dibantu hari ini, %s %s?. Ketik [HELP] untuk melihat daftar command.\n", current_user.role, current_user.username);

        }
        else if(strcmp(userInput, "REGISTER") == 0){        
            registerUser();
        }
        else if(strcmp(userInput, "SAVE") == 0){
            char newData[50];
            printf("Masukkan nama folder: ");
            scanf("%s", newData);
            save_data(newData);
        }
        else if (strcmp(userInput, "EXIT") == 0){
            status = EXIT;
            exit_program();
        }
        else if(strcmp(userInput, "LUPA_PASSWORD") == 0){
            lupaPassword();
        }
        else if (strcmp(userInput, "LOGOUT") == 0)
        {
            logout(&current_user, &status);
        }else{
            printf("\033[91mPerintah tidak dikenali.\033[0m Mohon berikan perintah yang valid!\n");
        }
        //================ LOGIN END ================//

        //================ LUPA PASSWORD ================
        
        switch (status) {
            case MANAGER_LOGGED_IN:
                handleManager(&current_user, &status);
                break;
            case DOKTER_LOGGED_IN:
                handleDokter(&current_user, &status);
                break;
            case PASIEN_LOGGED_IN:
                handlePasien(&current_user, &status);
                break;
            default:
                break;

        }
    }
    printf("Sampai jumpa di lain hari!\n");
    return 0;
}

// gcc src/c/main.c src/c/login.c src/c/load.c src/c/help.c src/c/register.c src/c/cariuser.c src/c/denah.c src/c/logout.c src/c/utils.c src/c/set.c src/c/lihatUser.c src/c/lihat_antrian.c src/c/queue.c src/c/lupa_password.c -o main
// gcc src/c/main.c src/c/daftar-checsrc/c/antrian-saya.c src/c/minum-obat.c src/c/minumpenawar.c src/c/exit.c src/c/ngobatin.c src/c/save.c src/c/stack.c src/c/diagnosis.c src/c/tambah_dokter.c src/c/login.c src/c/load.c src/c/help.c src/c/register.c src/c/cariuser.c src/c/denah.c src/c/logout.c src/c/utils.c src/c/set.c src/c/lihatUser.c src/c/lihat_antrian.c src/c/queue.c src/c/lupa_password.c -o main
// gcc src/c/main.c src/c/antrian-saya.c src/c/akubolehpulang.c src/c/minum-obat.c src/c/minumpenawar.c src/c/inventory.c src/c/daftar-check-up.c src/c/exit.c src/c/ngobatin.c src/c/save.c src/c/stack.c src/c/diagnosis.c src/c/tambah_dokter.c src/c/login.c src/c/load.c src/c/help.c src/c/register.c src/c/cariuser.c src/c/denah.c src/c/logout.c src/c/utils.c src/c/set.c src/c/lihatUser.c src/c/lihat_antrian.c src/c/queue.c src/c/lupa_password.c -o main
/*

Applied module:
F01 - LOGIN
F02 - REGISTER
F03 - LOGOUT
F05 - Menu & Help
F08 - Cari User
F18 - EXIT

*/

