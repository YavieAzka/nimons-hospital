#include "../header/user.h"
#include "../header/boolean.h"
#include "../header/login.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


//menghasilkan kode unik dengan implementasi Run-Length-Encoding
char* generateUniqueCode(const char* username){
    int len = strlen(username);
    char* code = (char*)malloc(2 * len + 1);
    int index = 0;
    int count = 1;
    for (int i = 1; i <= len;i++){
        if(i<len && username[i] == username[i-1]){
            count++;
        }
        else{
            if (count>1){
                index += sprintf(code + index, "%d", count);
            }
            code[index++] = username[i-1];
            count = 1;
        }
    }
    code[index] = '\0';
    return code;
}
//memvalidasi kode unik
boolean validasiCode(const char* username, const char* inputCode){
    char* trueCode = generateUniqueCode(username);
    boolean isValid = (strcmp(trueCode, inputCode) == 0);
    free(trueCode);
    return isValid;
}

void lupaPassword(User* users, int userCount) {
    char username[MAX_USERNAME];
    char kodeUnik[200];
    char newPassword[MAX_PASSWORD];

    // Input username
    printf("\n=== Lupa Password ===\n");
    printf("Username: ");
    if (scanf("%49s", username) != 1) {
        printf("Input tidak valid\n");
        while (getchar() != '\n');
        return;
    }

    // Cari user
    int userIndex = -1;
    for (int i = 0; i < userCount; i++) {
        if (strcmp(users[i].username, username) == 0) {
            userIndex = i;
            break;
        }
    }

    if (userIndex == -1) {
        printf("Username tidak ditemukan!\n");
        return;
    }

    // Validasi kode unik
    printf("Kode Unik: ");
    if (scanf("%199s", kodeUnik) != 1) {
        printf("Input tidak valid\n");
        while (getchar() != '\n');
        return;
    }

    if (!validasiCode(username, kodeUnik)) {
        printf("Kode unik tidak valid!\n");
        return;
    }

    // Input password baru
    printf("Password Baru: ");
    if (scanf("%49s", newPassword) != 1) {
        printf("Input tidak valid\n");
        while (getchar() != '\n');
        return;
    }

    // Update password
    strncpy(users[userIndex].password, newPassword, MAX_PASSWORD - 1);
    users[userIndex].password[MAX_PASSWORD - 1] = '\0';
    
    printf("Password berhasil diubah untuk user %s\n", username);
}