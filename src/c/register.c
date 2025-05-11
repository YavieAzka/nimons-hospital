#include "../header/user.h"
#include "../header/boolean.h"
#include "../header/register.h"
#include "../header/login.h"
#include "../header/set.h"
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
    fprintf(file, "\n%d;%s;%s;%s;;;;",
            user.id,
            user.username,
            user.password,
            user.role);

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

int isUsernameUnique(const char* username, Set users, int user_count){
    for(int i = 0; i < user_count; i++){
        //printf("#%s %s\n", *username, users[i].username);
        char lower_username[512];
        toLowerCase(users.elements[i], lower_username);
        if(strcmp(username, lower_username) == 0){
            return 0;
        }
    }
    return -1;
}

void registerUser(){
    Set setUsername;
    createEmptySet(&setUsername);
    int user_count = 0;

    User* users = getUserData("data/user.csv", &user_count);
    char newUsername[512]; char newPassword[512];
    
    //Proses pemindahan array to set
    for (int i = 0; i < user_count; i++)
    {
        insert(&setUsername, users[i].username);
    }
    
    
    // input username
    printf("Username: ");
    scanf("%s", newUsername);

    // input password
    printf("Password: ");
    scanf("%s", newPassword);

    char lowerNewUsername[512];
    toLowerCase(newUsername, lowerNewUsername);

    if(isUsernameUnique(lowerNewUsername, setUsername, user_count) == 0){
        printf("Registrasi gagal! Pasien dengan nama %s sudah terdaftar.\n", newUsername);
    }
    else{
        User new_user;
        strcpy(new_user.username, newUsername);
        strcpy(new_user.password, newPassword);
        new_user.id = user_count + 1;
        strcpy(new_user.role, "Pasien");
        appendUserToFile("data/user.csv", new_user);

        printf("Pasien %s berhasil ditambahkan!", new_user.username);
    }
} //register function