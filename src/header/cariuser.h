#ifndef CARIUSER_H
#define CARIUSER_H

#include <stdio.h>
#include <string.h>
#include "login.h"

void printHorizontalLine();
char toLowerChar(char c);
void strToLower(const char* src, char* dest);
int compareUsername(const void* a, const void* b);
int binarySearchUsername(User* users, int userCount, const char* target);
void printHeader();
void printUser_general(User U);
void printPasien(User U);
void printPilihan();
void printDokter(User U);
void cariPasien();
void cariDokter();
void cariUser();

#endif
