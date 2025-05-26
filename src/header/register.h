#ifndef REGISTER_H
#define REGISTER_H

#include "user.h"
#include <string.h>
#include "set.h"

//register function
void registerUser(); 

//untuk mengecek username merubah huruf menjadi lower A -> a
void usernameToLowerCase(const char* username, char* lowerUsername); 

//untuk mengecek username case-insensitive
int isUsernameUnique(const char* username, Set users, int user_count); //untuk mengecek username unik

//Mengecek username agar only alfabet
boolean onlyAlfabet(const char *str);

#endif