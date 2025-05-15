#ifndef DIAGNOSIS_H
#define DIAGNOSIS_H

#include "user.h"
#include <string.h>
#include "penyakit.h"

char *cekPenyakit(User user, Penyakit penyakit);
void diagnosis(const char* filename, User user);

#endif