#ifndef LOGIN_H
#define LOGIN_H

#include "user.h"

User login(User *user_now);
int getUserIndex(const char* username, User* users, int user_count);
User* getUserData(const char* filename, int* user_count);
int getTrombosit(char* line);
int getKadarKolesterolLDL(char* line);
int getKadarKolesterol(char* line);
float getTinggiBadan(char* line);
int getSaturasiOksigen(char* line);
int getKadarGulaDarah(char* line);
float getBeratBadan(char* line);
float getSuhuTubuh(char* line);
int getTekananDarahSistolik(char* line);
int getTekananDarahDiastolik(char* line);
int getDetakJantung(char* line);
void getUsername(char* line, char* username);
void getPassword(char* line, char* password);
void getRole(char* line, char* role);
void getRiwayatPenyakit(char* line, char* riwayat_penyakit);
int getId(char* line);

#endif