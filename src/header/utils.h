#ifndef UTILS_H
#define UTILS_H

#include <stdio.h>

typedef enum {
    USER_LOGGED_OFF,
    MANAGER_LOGGED_IN,
    DOKTER_LOGGED_IN,
    PASIEN_LOGGED_IN,
    EXIT
} Status;

char char_toLower(char c);
int stringToInt(char* str);
float stringToFloat(char* str);
void getFieldAt(char* line, int field_number, char* output, int max_length);
int parse_int(const char *str, int *idx); 

#endif