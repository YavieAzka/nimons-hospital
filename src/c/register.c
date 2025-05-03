#include "../header/user.h"
#include "../header/boolean.h"
#include "../header/register.h"
#include "../header/login.h"
//Read user.csv file and store it in users[] array.
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void appendUserToFile(const char* filename, User user) {
    FILE* file = fopen(filename, "a");  // buka dalam mode append
    if (file == NULL) {
        printf("Gagal membuka file %s untuk ditulis.\n", filename);
        return;
    }
    //id;username;password;role;riwayat_penyakit;suhu_tubuh;tekanan_darah_sistolik;tekanan_darah_diastolik;detak_jantung;saturasi_oksigen;kadar_gula_darah;berat_badan;tinggi_badan;kadar_kolesterol;kadar_kolesterol_ldl;trombosit

    // Format penulisan sesuai struktur User
    fprintf(file, "%d;%s;%s;%s;%s;%f;%d;%d;%d;%d;%d;%f;%f;%d;%d;%d\n",
            user.id,
            user.username,
            user.password,
            user.role,
            user.riwayat_penyakit,
            user.suhu_tubuh,
            user.tekanan_darah_sistolik,
            user.tekanan_darah_diastolik,
            user.detak_jantung,
            user.saturasi_oksigen,
            user.kadar_gula_darah,
            user.berat_badan,
            user.tinggi_badan,
            user.kadar_kolesterol,
            user.kadar_kolesterol_ldl,
            user.trombosit);

    fclose(file);
}

void toLowerCase(const char* username, char* lowerUsername) {
    while (*username) {
        if (*username >= 'A' && *username <= 'Z') {
            *lowerUsername = *username + ('a' - 'A');  // konversi manual huruf besar ke kecil
        } else {
            *lowerUsername = *username;
        }
        username++;
        lowerUsername++;
    }
    *lowerUsername = '\0';
}

int isUsernameUnique(const char* username, User* users, int user_count){
    for(int i = 0; i < user_count; i++){
        //printf("#%s %s\n", *username, users[i].username);
        char lower_username[512];
        toLowerCase(users[i].username, lower_username);
        if(strcmp(username, lower_username) == 0){
            return i;
        }
    }
    return -1;
}

void registerUser(){
    int user_count = 0;
    User* users = getUserData("data/user.csv", &user_count);
    char new_username[512]; char new_password[512];

    // input username
    printf("Username: ");
    scanf("%s", &new_username);

    // input password
    printf("Password: ");
    scanf("%s", &new_password);

    char lowernewUsername[512];
    toLowerCase(new_username, lowernewUsername);

    if(isUsernameUnique(lowernewUsername, users, user_count) == 0){
        printf("Registrasi gagal! Pasien dengan nama %s sudah terdaftar.\n", new_username);
    }
    else{
        User new_user;
        strcpy(new_user.username, new_username);
        strcpy(new_user.password, new_password);
        new_user.id = user_count + 1;
        appendUserToFile("data/user.csv", new_user);
        printf("Pasien %s berhasil ditambahkan!", new_user.username);
    }
} //register function