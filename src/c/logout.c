#include "../header/logout.h"

int logout(int status){
    if (status == 1) //dapat diganti dengan strcmp kalo status dalam string
    {
        printf("Sampai jumpa!\n");
        return 0;
    } else if (status == 0)
    {
        printf("Logout gagal!\n");
        printf("Anda belum login, silahkan login terlebih dahulu sebelum melakukan logout\n");
        return 0;
    }
    
}