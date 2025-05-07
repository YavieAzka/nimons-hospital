#include "../header/logout.h"

int logout(int status){
    if (status == LOGGED_IN) //dapat diganti dengan strcmp kalo status dalam string
    {
        printf("Sampai jumpa!\n");
        return LOGGED_OFF;
    } else if (status == LOGGED_OFF)
    {
        printf("Logout gagal!\n");
        printf("Anda belum login, silahkan login terlebih dahulu sebelum melakukan logout\n");
        return LOGGED_OFF;
    }
}