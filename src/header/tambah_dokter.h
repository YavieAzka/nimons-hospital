#ifndef TAMBAH_DOKTER_H
#define TAMBAH_DOKTER_H
#include "user.h"
#include "ruangan.h"

// Define Set structure for username validation
#define MAX_SET_SIZE 100
typedef struct {
    char usernames[MAX_SET_SIZE][MAX_USERNAME];
    int count;
} UsernameSet;

// Function declarations
void initUsernameSet(UsernameSet *set);
char char_toLower(char c);
void toLowerCase(const char *str, char *result);
int isUsernameExists(UsernameSet *set, const char *username);
void addUsernameToSet(UsernameSet *set, const char *username);
int isValidUsername(const char *username);
int getNextUserId(User *users, int userCount);
int findAvailableRoom(Ruangan *ruangan, int ruanganCount);
void tambahDokter(User *users, int *userCount, UsernameSet *usernameSet);
void assignDokter(User *users, int userCount, Ruangan *ruangan, int ruanganCount);
void tampilkanDokterDanRuangan(User *users, int userCount, Ruangan *ruangan, int ruanganCount);

#endif