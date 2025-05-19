#ifndef GLOBAL_H
#define GLOBAL_H

#include "user.h"
#include "obat.h"
#include "penyakit.h"
#include "obatPenyakit.h"

extern User* users;
extern int userCount;

extern Obat* obatList;
extern int obatCount;

extern Penyakit* penyakitList;
extern int penyakitCount;

extern ObatPenyakit* obatPenyakitList;
extern int obatPenyakitCount;

#endif