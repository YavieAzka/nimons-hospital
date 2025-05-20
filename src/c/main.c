// Include any necessary headers
#include <stdio.h>
#include "../header/user.h"
#include "../header/login.h"
#include "../header/help.h"
#include "../header/boolean.h"
#include "../header/cariuser.h"
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



void handleManager(User* user, Status* status) {
    char input[50];
    while (*status == MANAGER_LOGGED_IN) {
        printf(">>> ");
        scanf("%s", input);

        if (strcmp(input, "HELP") == 0) {
            help(*user);
        } else if (strcmp(input, "REGISTER") == 0) {
            //register_user();
        } else if (strcmp(input, "CARI_USER") == 0) {
            //cari_user();
        } else if (strcmp(input, "LIHAT_USER") == 0) {
            //lihat_user();
        } else if (strcmp(input, "SET_ROLE") == 0) {
            //set_role();
        } else if (strcmp(input, "LOGOUT") == 0) {
            logout(user, status);
            return;
        } else if (strcmp(input, "EXIT") == 0) {
            //*status = EXIT;
            //return;
        }
    }
}

void handleDokter(User* user, Status* status) {
    char input[50];
    while (*status == DOKTER_LOGGED_IN) {
        printf(">>> ");
        scanf("%s", input);

        if (strcmp(input, "HELP") == 0) {
            help(*user);
        }
        if (strcmp(input, "LIHAT_ANTRIAN") == 0) {
            // implementasi modul lihat_antrian(); // placeholder
        }
        if (strcmp(input, "DIAGNOSIS") == 0) {
            // implementasi modul diagnosis(); // placeholder
        }
        if (strcmp(input, "NGOBATIN") == 0) {
            // implementasi modul ngobatin(); // placeholder
        }
        if (strcmp(input, "LOGOUT") == 0) {
            logout(user, status);
            return;
        }
        if (strcmp(input, "EXIT") == 0) {
            *status = EXIT;
            return;
        } 
    }
}

void handlePasien(User* user, Status* status) {
    char input[50];
    while (*status == PASIEN_LOGGED_IN) {
        printf(">>> ");
        scanf("%s", input);

        if (strcmp(input, "HELP") == 0) {
            char* nextCommand = help(*user);;  // dapat string hasil input setelah HELP
            strcpy(input, nextCommand);          // salin ke userInput untuk dieksekusi di loop selanjutnya
            free(nextCommand);
        } 
        if (strcmp(input, "DAFTAR_CHECKUP") == 0) {
            // implementasi modul daftar_checkup(); // placeholder
        } 
        if (strcmp(input, "ANTRIAN_SAYA") == 0) {
            // implementasi modul antrian_saya(); // placeholder
        } 
        if (strcmp(input, "MINUM_OBAT") == 0) {
            // implementasi modul minum_obat(); // placeholder
        } 
        if (strcmp(input, "MINUM_PENAWAR") == 0) {
            // implementasi modul minum_penawar(); // placeholder
        } 
        if (strcmp(input, "DOK_AKU_MAU_PULANG") == 0) {
            // implementasi modul pulang(); // placeholder
        } 
        if (strcmp(input, "LOGOUT") == 0) {
            logout(user, status);
            //return;
        }
        if (strcmp(input, "EXIT") == 0) {
            *status = EXIT;
            return;
        } 
        
    }
}

void printWelcomeMessage(){
    printf(" __      __       .__                                  __                  .__                               .__                         .__  __         .__   \n");
    printf("/  \\    /  \\ ____ |  |   ____  ____   _____   ____   _/  |_  ____     ____ |__| _____   ____   ____   ______ |  |__   ____  ____________ |__|/  |______  |  |  \n");
    printf("\\   \\/\\/   // __ \\|  | _/ ___\\/  _ \\ /     \\_/ __ \\  \\   __\\/  _ \\   /    \\|  |/     \\ /  _ \\ /    \\ /  ___/ |  |  \\ /  _ \\/  ___\\/\\____\\|  \\   __\\__  \\ |  |  \n");
    printf(" \\        /\\  ___/|  |_\\  \\__(  <_> )  Y Y  \\  ___/   |  | (  <_> ) |   |  \\  |  Y Y  (  <_> )   |  \\\\___ \\  |   Y  (  <_> )___ \\ |  |_> >  ||  |  / __ \\|  |__\n");
    printf("  \\__/\\  /  \\___  >____/\\___  >____/|__|_|  /\\___  >  |__|  \\____/  |___|  /__|__|_|  /\\____/|___|  /____  > |___|  /\\____/____  >|   __/|__||__| (____  /____/\n");
    printf("       \\/       \\/          \\/            \\/     \\/                      \\/         \\/            \\/     \\/       \\/           \\/ |__|                 \\/      \n");
}

void printOpeningMessage(){
    printf("+===================================================+\n");
    printf("|    SILAKAN LOGIN DENGAN MENGETIK [LOGIN] ATAU     |\n");
    printf("|    MELAKUKAN REGISTER DENGAN MENGETIK REGISTER    |\n");
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

    printWelcomeMessage();
    printOpeningMessage();

    printf(">>> ");
    scanf("%s", userInput);
    while(status != EXIT){
        //================ LOGIN ================//
        if(strcmp(userInput, "LOGIN") == 0){        
            current_user = login(&current_user);
            if(current_user.id == 9999){
                // REGISTER
            }
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
        //================ LOGIN ================// 
        else if (strcmp(userInput, "REGISTER") == 0)
        {
            registerUser();
        }
        
        //================ LOGIN END ================//
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
        printf(">>> ");
        scanf("%s", userInput);
    }
    printf("Sampai jumpa di lain hari!\n");
    return 0;
}

// gcc src/c/main.c src/c/login.c src/c/load.c src/c/help.c src/c/register.c src/c/cariuser.c src/c/logout.c src/c/utils.c src/c/set.c src/c/lihatUser.c src/c/queue.c src/c/lupa_password.c -o main

