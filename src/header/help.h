#ifndef HELP_H
#define HELP_H

#include "user.h"

#define MAX_COMMAND 50

char* help(User userNow); // Mengembalikan nama command berikutnya
void print_helpMessage_pasien(User usernow);
void print_helpMessage_dokter(User usernow);
void print_helpMessage_manager(User usernow);// Mengembalikan nama command berikutnya

#endif