// Include any necessary headers
#include <stdio.h>
#include "../header/user.h"
#include "../header/login.h"
#include "../header/help.h"


void print_openingMessage(){
    printf("==============================================================\n");
    printf("| SELAMAT DATANG DI RUMAH SAKIT NIMONS! SILAKAN LOGIN DENGAN |\n");
    printf("| MENGETIK LOGIN ATAU REGISTER DENGAN MENGETIK REGISTER      |\n");
    printf("==============================================================\n");
}

int main() { 
    // gcc src/c/main.c src/c/login.c src/c/help.c -I src/header -o src/c/main
    // sekaiwonekkyounouzuni 
    // Your code goes here
    User current_user; char userInput[10]; 

    print_openingMessage();
    scanf("%s", &userInput);

    if(strcmp(userInput, "LOGIN") == 0){        // User Login
        current_user = login(&current_user);

        printf("Apa yang bisa dibantu hari ini, %s %s?. Ketik HELP untuk melihat daftar command.\n", current_user.role, current_user.username);
        scanf("%s", &userInput);
        if(strcmp(userInput, "HELP") == 0){
            char *command = help(current_user);

            // Tambahkan fungsi/modul yang sudah dibuat di bawah.
            if(strcmp(command, "LOGOUT") == 0){
                printf("Logged out\n");
            }
        }
    }

    else if(strcmp(userInput, "REGISTER") == 0){    // User Login
        printf("Mohon maaf, fungsi belum tersedia :(\n");
    }
    else{
        printf("Perintah tidak dikenali. Mohon melakukan login atau register terlebih dahulu.");
    }
    
    return 0;
}