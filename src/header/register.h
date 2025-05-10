<<<<<<< HEAD
#ifndef REGISTER_H
#define REGISTER_H

#include "user.h"
#include <string.h>
#include "set.h"

//register function
void registerUser(); 

//untuk mengecek username merubah huruf menjadi lower A -> a
void toLowerCase(const char* username, char* lowerUsername); 

//untuk mengecek username case-insensitive
int isUsernameUnique(const char* username, Set users, int user_count); //untuk mengecek username unik

//Menambahkan data Baru ke FILE CSV
void appendUserToFile(const char* filename, User user);

=======
#ifndef REGISTER_H
#define REGISTER_H

#include "user.h"
#include <string.h>

//register function
void registerUser(); 

//untuk mengecek username merubah huruf menjadi lower A -> a
void toLowerCase(const char* username, char* lowerUsername); 

//untuk mengecek username case-insensitive
int isUsernameUnique(const char* username, User* users, int user_count); //untuk mengecek username unik

//Menambahkan data Baru ke FILE CSV
void appendUserToFile(const char* filename, User user);

>>>>>>> 0b01762 (feat: register)
#endif