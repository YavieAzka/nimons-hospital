#ifndef LUPA_PASS_H
#define LUPA_PASS_H

#include "../header/boolean.h"
#include "../header/user.h"

char* generateUniqueCode(const char* username);
boolean validasiCode(const char* username, const char* inputCode);
void overwriteUserFile(User* users, int count, const char* filename);
void gantiPassword(User* users, int userCount, const char* username, const char* newPassword);
void lupaPassword();
#endif