#include "../header/user.h"
#include "../header/save.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void Exit(User* users, const char* filenameIn, const char* filenameOut){
    FILE* fin = fopen(filenameIn, "r") //file dibuka untuk dibaca
    FILE* fout = fopen(filenameOut, "w") //file dibuka untuk dicopy (save)

    char ch;
    do{
        printf("Apakah Anda mau melakukan penyimpanan file yang sudah diubah? (y/n)\n");
        scanf("%c", &ch);
    } while(ch != 'y' || ch != 'Y' || ch != 'n' || ch != 'N');

    char buffer[256];
    if(ch == 'y' || ch == 'Y'){
        save(fin, fout);
    }
    else return;
}
