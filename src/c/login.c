#include "../header/user.h"
#include "../header/boolean.h"
#include "../header/utils.h"
#include "../header/load.h"
#include "../header/global.h"
#include <stdio.h>
#include <string.h>

User login(User* user_now) {
    user_now->id = 9999; // ID default = guest (jika gagal login)

    char username[100];
    char password[100];

    printf("Username: ");
    scanf("%s", username);
    str_toLower(username);  // opsional: biar case-insensitive

    printf("Password: ");
    scanf("%s", password);

    // users dan userCount diasumsikan global
    int index = getUserIndex(username, users, userCount);

    if (index != -1) {
        if (strcmp(users[index].password, password) == 0) {
            *user_now = users[index];
            printf("Login Berhasil! Selamat datang %s %s.\n", user_now->role, user_now->username);
            printf("Silakan ketik [HELP] untuk melihat daftar perintah.\n");
        } else {
            printf("Password salah untuk user %s.\n", users[index].username);
        }
    } else {
        printf("Pengguna dengan username \"%s\" belum terdaftar.\n", username);
        printf("Silakan lakukan REGISTER.\n");
    }

    return *user_now;
}
