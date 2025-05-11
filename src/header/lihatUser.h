#ifndef LIHATUSER_H
#define LIHATUSER_H

#include "user.h"

void urutanSort(User* users, int user_count);
void sortDescID(User* users, int user_count) ;
void sortAscNama(User* users, int user_count) ;
void sortDescNama(User* users, int user_count);
void sortAscNama(User* users, int user_count);
void lihatUser(User usernow) ;
void lihatPasien(User usernow);
void lihatDokter(User usernow);
void interfaceUser(User* users, User usernow, int user_count);
void output(User usernow);


#endif