#ifndef LUPA_PASS_H
#define LUPA_PASS_H

#include "../header/boolean.h"
#include "../header/user.h"

char* generateUniqueCode(const char* username);
bool validasiCode(const char* username, const char* inputCode);
void overwriteUserFile(User* users, int count, const char* filename);
void gantiPassword(const char* username, const char* newPassword);
void lupaPassword();
#endif