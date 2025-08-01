#include "../header/boolean.h"
#include "../header/register.h"
#include "../header/login.h"
#include "../header/load.h"
#include "../header/user.h"
#include "../header/boolean.h"
//Read user.csv file and store it in users[] array.
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// void appendUserToFile(const char* filename, User user) {
//     FILE* file = fopen(filename, "a");  // buka dalam mode append
//     if (file == NULL) {
//         printf("Gagal membuka file %s untuk ditulis.\n", filename);
//         return;
//     }
//     //id;username;password;role;riwayat_penyakit;suhu_tubuh;tekanan_darah_sistolik;tekanan_darah_diastolik;detak_jantung;saturasi_oksigen;kadar_gula_darah;berat_badan;tinggi_badan;kadar_kolesterol;kadar_kolesterol_ldl;trombosit

//     // Format penulisan sesuai struktur User
//     fprintf(file, "\n%d;%s;%s;%s;;;;",
//             user.id,
//             user.username,
//             user.password,
//             user.role);

//     fclose(file);
// }

int searchMaxID(){
    int max = 0;
    for (int i = 0; i < userCount; i++)
    {
        if (max < users[i].id)
        {
            max = users[i].id;
        }
    }
    return max;
}
boolean onlyAlfabet(const char *username) {
    while (*username) {
        if (!((*username >= 'A' && *username <= 'Z') || (*username >= 'a' && *username <= 'z'))) {
            return false;
        }
        username++;
    }
    return true;
}

void usernameToLowerCase(const char* username, char* lowerUsername) {
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

int isUsernameUnique(const char* username, Set userset, int user_count){
    for(int i = 0; i < user_count; i++){
        //printf("#%s %s\n", *username, users[i].username);
        char lower_username[512];
        usernameToLowerCase(userset.elements[i], lower_username);
        if(strcmp(username, lower_username) == 0){
            return 0;
        }
    }
    return -1;
}

void registerUser(){
    Set setUsername;
    createEmptySet(&setUsername);
    char newUsername[512]; char newPassword[512];
    
    //Proses pemindahan array to set
    for (int i = 0; i < userCount; i++)
    {
        insert(&setUsername, users[i].username);
    }
    
    // input username
    printf("\033[34mUsername: \033[0m");
    scanf("%s", newUsername);
    while (!onlyAlfabet(newUsername))
    {
        printf("Masukkan username hanya dengan Huruf A-Z, a-z!!\n");
        printf("\033[34mUsername: \033[0m");
        scanf("%s", newUsername);
    }
    
    
    // input password
    printf("\033[34mPassword: \033[0m");
    scanf("%s", newPassword);

    char lowerNewUsername[512];
    usernameToLowerCase(newUsername, lowerNewUsername);

    if(isUsernameUnique(lowerNewUsername, setUsername, userCount) == 0){
        printf("Registrasi gagal! Pasien dengan nama %s sudah terdaftar.\n", newUsername);
    }
    else{
        strcpy(users[userCount].username, newUsername);
        strcpy(users[userCount].password, newPassword);
        strcpy(users[userCount].role, "pasien");
        int maxID = searchMaxID();
        users[userCount].id = maxID + 1;

        userCount = userCount + 1;

        printf("Pasien %s berhasil ditambahkan!\n", newUsername);
        printf("Silakan melakukan login dengan mengetik [LOGIN].\n");
    }
} //register function