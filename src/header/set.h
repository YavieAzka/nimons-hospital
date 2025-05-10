#ifndef SET_H
#define SET_H

#define MAX_SET_SIZE 1000
#define MAX_STRING_LENGTH 512

typedef struct {
    char elements[MAX_SET_SIZE][MAX_STRING_LENGTH];
    int size;
} Set;

// Initialize an empty set
void createEmptySet(Set* s); 

// Check does Set s contain String str
int contains(Set s, const char* str);

// Copying String str to Set s if Set s does not contain str (to avoid duplication)
void insert(Set* s, const char* str);

#endif