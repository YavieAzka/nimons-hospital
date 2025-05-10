#include <string.h>
#include "../header/set.h"

void createEmptySet(Set* s) {
    s->size = 0;
}

int contains(Set s, const char* str) {
    for (int i = 0; i < s.size; i++) {
        if (strcmp(s.elements[i], str) == 0) return 1;
    }
    return 0;
}

void insert(Set* s, const char* str) {
    if (!contains(*s, str)) {
        strcpy(s->elements[s->size], str);
        s->size++;
    }
}
    