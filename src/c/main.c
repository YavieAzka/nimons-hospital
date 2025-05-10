// Include any necessary headers
#include <stdio.h>
#include "../header/user.h"
#include "../header/login.h"
#include "../header/help.h"
#include "../header/boolean.h"
#include "../header/cariuser.h"
#include "../header/register.h"
#include "../header/logout.h"
// void print_nimons(){
    
// printf ("__      __       .__                                  __                  .__                               .__                         .__  __         .__   \n");
// printf("/  \    /  \ ____ |  |   ____  ____   _____   ____   _/  |_  ____     ____ |__| _____   ____   ____   ______ |  |__   ____  ____________ |__|/  |______  |  |  \n");
// printf("\   \/\/   // __ \|  | _/ ___\/  _ \ /     \_/ __ \  \   __\/  _ \   /    \|  |/     \ /  _ \ /    \ /  ___/ |  |  \ /  _ \/  ___/\____ \|  \   __\__  \ |  |  \n");
// printf(" \        /\  ___/|  |_\  \__(  <_> )  Y Y  \  ___/   |  | (  <_> ) |   |  \  |  Y Y  (  <_> )   |  \\___ \  |   Y  (  <_> )___ \ |  |_> >  ||  |  / __ \|  |__\n");
// printf("  \__/\  /  \___  >____/\___  >____/|__|_|  /\___  >  |__|  \____/  |___|  /__|__|_|  /\____/|___|  /____  > |___|  /\____/____  >|   __/|__||__| (____  /____/\n");
// printf("       \/       \/          \/            \/     \/                      \/         \/            \/     \/       \/           \/ |__|                 \/      \n");

// }

void print_openingMessage(){
    printf("==============================================================\n");
    printf("| SELAMAT DATANG DI RUMAH SAKIT NIMONS! SILAKAN LOGIN DENGAN |\n");
    printf("| MENGETIK LOGIN ATAU REGISTER DENGAN MENGETIK REGISTER      |\n");
    printf("==============================================================\n");
}

int main() { 
    //gcc src/c/main.c src/c/login.c src/c/help.c src/c/cariuser.c src/c/register.c src/c/set.c src/c/logout.c -I src/header -o src/c/main
    // sekaiwonekkyounouzuni 
    // Your code goes here
    int status = LOGGED_OFF;
    User current_user; char userInput[10]; 

    print_openingMessage();
    scanf("%s", &userInput);

    if(strcmp(userInput, "LOGIN") == 0){        // User Login
        current_user = login(&current_user);
        status = LOGGED_IN;
        printf("Apa yang bisa dibantu hari ini, %s %s?. Ketik HELP untuk melihat daftar command.\n", current_user.role, current_user.username);
        scanf("%s", &userInput);
        if(strcmp(userInput, "HELP") == 0){
            char *command = help(current_user);

            // Tambahkan fungsi/modul yang sudah dibuat di bawah.
            if(strcmp(command, "LOGOUT") == 0){
                status = logout(status);
            }
        }
    }

    else if(strcmp(userInput, "REGISTER") == 0){    // User register
        registerUser();
    }

    else if(strcmp(userInput, "CARI_USER") == 0){
        cariUser();
    }

    else if(strcmp(userInput, "CARI_PASIEN") == 0){
        cariPasien();
    }

    else if(strcmp(userInput, "CARI_DOKTER") == 0){
        cariDokter();
    }

    else{
        printf("Perintah tidak dikenali. Mohon melakukan login atau register terlebih dahulu.");
    }
    
    return 0;
}
// gcc c/main.c c/login.c c/help.c c/exit.c c/cariuser.c c/register.c c/set.c  -o main
