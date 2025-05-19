#include "../header/logout.h"

void logout(User* user, Status* status) {
    if (*status == USER_LOGGED_OFF) {
        printf("Logout gagal!\n");
        printf("Anda belum login, silakan login terlebih dahulu sebelum logout.\n");
    } else {
        printf("Sampai jumpa, %s %s!\n", user->role, user->username);
        *status = USER_LOGGED_OFF;

        // Clear current user
        user->id = -1;
        strcpy(user->username, "");
        strcpy(user->password, "");
        strcpy(user->role, "");
    }
}