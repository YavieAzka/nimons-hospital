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

// Fungsi untuk mengupdate password dalam array users[]
void updatePasswordInArray(User* users, int userCount, const char* username, const char* newPassword) {
    for (int i = 0; i < userCount; i++) {
        if (strcmp(users[i].username, username) == 0) {
            strcpy(users[i].password, newPassword);  // Ubah password langsung di array
            break;
        }
    }
}

// lupa password
void lupaPassword() {
    char username[100];
    char kodeUnik[200];
    char newPassword[100];

    printf("Username: ");
    scanf("%s", username);

    int userCount;
    User* users = getUserData("user.csv", &userCount);

    boolean found = false;
    for (int i = 0; i < userCount; i++) {
        if (strcmp(users[i].username, username) == 0) {
            found = true;
            break;
        }
    }

    if (!found) {
        printf("Username tidak terdaftar!\n");
        free(users);
        return;
    }

    printf("Kode Unik: ");
    scanf("%s", kodeUnik);

    if (!validasiCode(username, kodeUnik)) {
        printf("Kode unik salah!\n");
        free(users);
        return;
    }

    printf("Halo %s, silakan daftarkan ulang password anda!\n", username);
    printf("Password Baru: ");
    scanf("%s", newPassword);

    updatePasswordInArray(users, userCount, username, newPassword);
    printf("Password berhasil diperbarui dalam memori!\n");

    free(users);
}