#ifndef LIHATUSER_H
#define LIHATUSER_H

#include "user.h"

void urutanSort(User* users, int user_count);
void sortDescID(User* users, int user_count) ;
void sortAscNama(User* users, int user_count) ;
void sortDescNama(User* users, int user_count);
void sortAscNama(User* users, int user_count);
void lihatUser(char *command) ;
void lihatPasien(char *command);
void lihatDokter(char *command);
void interfaceUser(User* users, char *command, int user_count);

#endif