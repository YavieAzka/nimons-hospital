#ifndef DIAGNOSIS_H
#define DIAGNOSIS_H

#include "user.h"
#include <string.h>
#include "penyakit.h"

int getUserIndex(const char* username, User* users, int user_count);
User* getUserData(const char* filename, int* user_count);
int getTrombosit(char* line);
int getKadarKolesterolLDL(char* line);
int getKadarKolesterol(char* line);


int stringToInt(char* str);
float stringToFloat(char* str);
int getTinggiBadanMax(char* line);
int getTinggiBadanMin(char* line);
float getBeratBadanMax(char* line);
float getBeratBadanMin(char* line);
int getKadarGulaDarahMax(char* line);
int getKadarGulaDarahMin(char* line);
int getSaturasiOksigenMin(char* line);
int getSaturasiOksigenMax(char* line);
int getDetakJantungMax(char* line);
int getDetakJantungMin(char* line);
int getTekananDarahDiastolikMax(char* line);
int getTekananDarahDiastolikMin(char* line);
int getTekananDarahSistolikMax(char* line);
int getTekananDarahSistolikMin(char* line);
float getSuhuTubuhMax(char* line);
float getSuhuTubuhMin(char* line);
void getNamaPenyakit(char* line, char* nama_penyakit);
int getPenyakitId(char* line);
void getFieldAt(char* line, int field_number, char* output, int max_length);

char *cekPenyakit(User user, Penyakit penyakit);
void diagnosis(const char* filename, User user);
Penyakit* getPenyakitData(const char* filename, int* user_count);

#endif