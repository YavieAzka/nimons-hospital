#include "../header/user.h"
#include "../header/boolean.h"
#include "../header/utils.h"
#include "../header/load.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
User login(User* user_now) {
    user_now->id = 9999; // ID default = guest (jika gagal login)

    char username[100];
    char password[100];

    printf("\033[34mUsername: \033[0m");
    scanf("%s", username);
    str_toLower(username);  // opsional: biar case-insensitive

    printf("\033[34mPassword: \033[0m");
    scanf("%s", password);

    // users dan userCount diasumsikan global
    int index = getUserIndex(username, users, userCount);

    if (index != -1) {
        if (strcmp(users[index].password, password) == 0) {
            *user_now = users[index];
            printf("\033[32mLogin Berhasil!\033[0m Selamat datang %s %s.\n", user_now->role, user_now->username);
        } else {
            printf("\033[91mPassword salah\033[0m untuk user %s.\n", users[index].username);
            printf("Lupa password? Ketik \033[92m[LUPA_PASSWORD]\033[0m untuk mengganti password.\n");
        }
    } else {
        printf("Pengguna dengan username \"%s\" belum terdaftar.\n", username);
        printf("Silakan lakukan REGISTER dengan mengetik \033[92m[REGISTER]\033[0m\n");
        printf("atau melakukan LOGIN dengan akun yang sudah terdaftar.\n");
    }

    return *user_now;
}
