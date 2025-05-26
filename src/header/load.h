#ifndef LOAD_H
#define LOAD_H

#define MAX_OBAT 200
#define MAX_MAPPING 100
#define MAX_LINE_LENGTH 1024
#define MAX_FIELD_LENGTH 256

#include "user.h"

void load_all_data(const char* folder);
void str_toLower(char *str);
char char_toLower(char c);
int getUserIndex(const char* username, User* users, int user_count);

#endif
