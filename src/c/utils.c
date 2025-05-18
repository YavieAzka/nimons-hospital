#include "../header/utils.h"

int stringToInt(char* str){
    int value = 0;
    int i = 0;
    int is_negative = 0;
    
    // Periksa jika nilai negatif
    if (str[i] == '-') {
        is_negative = 1;
        i++;
    }
    
    while (str[i] != '\0') {
        if (str[i] >= '0' && str[i] <= '9') {
            value = value * 10 + (str[i] - '0');
        }
        i++;
    }
    
    return is_negative ? -value : value;
}

float stringToFloat(char* str){
    float value = 0.0;
    int i = 0;
    int decimal_pos = -1;
    int is_negative = 0;
    
    // Periksa jika nilai negatif
    if (str[i] == '-') {
        is_negative = 1;
        i++;
    }
    
    // Cari bagian integral dan desimal
    while (str[i] != '\0') {
        if (str[i] == '.') {
            decimal_pos = 0;
        } else if (str[i] >= '0' && str[i] <= '9') {
            if (decimal_pos >= 0) {
                value = value + (str[i] - '0') / (10.0 * (++decimal_pos));
            } else {
                value = value * 10 + (str[i] - '0');
            }
        }
        i++;
    }
    
    return is_negative ? -value : value;
}

void getFieldAt(char* line, int field_number, char* output, int max_length) {
    int current_field = 0;
    int i = 0;
    int j = 0;
    
    // Cari field yang diminta
    while (line[i] != '\0' && current_field < field_number) {
        if (line[i] == ';') {
            current_field++;
        }
        i++;
    }
    
    // Ekstrak field
    while (line[i] != ';' && line[i] != '\0' && line[i] != '\n' && j < max_length - 1) {
        output[j++] = line[i++];
    }
    
    output[j] = '\0';
}

int parse_int(const char* str, int* idx) {
    int value = 0;
    int is_negative = 0;

    while (str[*idx] == ' ') {
        (*idx)++;
    }

    if (str[*idx] == '-') {
        is_negative = 1;
        (*idx)++;
    }

    while (str[*idx] >= '0' && str[*idx] <= '9') {
        value = value * 10 + (str[*idx] - '0');
        (*idx)++;
    }

    return is_negative ? -value : value;
}