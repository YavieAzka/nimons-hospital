#ifndef UTILS_H
#define UTILS_H

#include <stdio.h>

int stringToInt(char* str);
float stringToFloat(char* str);
void getFieldAt(char* line, int field_number, char* output, int max_length);

#endif