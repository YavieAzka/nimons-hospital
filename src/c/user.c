#include "user.h"

User users[MAX_USERS];
int userCount = 0;

static void chomp(char *s) {
    size_t len = strlen(s);
    if (len > 0 && (s[len-1] == '\n' || s[len-1] == '\r')) {
        s[len-1] = '\0';
        // jika \r\n, hilangkan dua
        if (len > 1 && s[len-2] == '\r') s[len-2] = '\0';
    }
}

void loadUsers(const char* filename) {
    FILE* fp = fopen(filename, "r");
    if (!fp) {
        perror("Error opening user file");
        return;
    }

    char line[512];
    if (!fgets(line, sizeof(line), fp)) {
        fclose(fp);
        return;
    }

    while (fgets(line, sizeof(line), fp)) {
        chomp(line);
        if (strlen(line) == 0) continue;

        User u;
        char *token, *saveptr;
        int field = 0;

        token = strtok_r(line, ";", &saveptr);
        while (token) {
            switch (field) {
                case 0: u.id = atoi(token); break;
                case 1: strncpy(u.username, token, MAX_USERNAME); u.username[MAX_USERNAME-1] = '\0'; break;
                case 2: strncpy(u.password, token, MAX_PASSWORD); u.password[MAX_PASSWORD-1] = '\0'; break;
                case 3: strncpy(u.role, token, MAX_ROLE); u.role[MAX_ROLE-1] = '\0'; break;
                case 4: strncpy(u.riwayat_penyakit, token, MAX_RIWAYAT); u.riwayat_penyakit[MAX_RIWAYAT-1] = '\0'; break;
                case 5: u.suhu_tubuh = (strlen(token)>0 ? atof(token) : -1.0f); break;
                case 6: u.tekanan_darah_sistolik = (strlen(token)>0 ? atoi(token) : -1); break;
                case 7: u.tekanan_darah_diastolik = (strlen(token)>0 ? atoi(token) : -1); break;
                case 8: u.detak_jantung = (strlen(token)>0 ? atoi(token) : -1); break;
                case 9: u.saturasi_oksigen = (strlen(token)>0 ? atoi(token) : -1); break;
                case 10: u.kadar_gula_darah = (strlen(token)>0 ? atoi(token) : -1); break;
                case 11: u.berat_badan = (strlen(token)>0 ? atof(token) : -1.0f); break;
                case 12: u.tinggi_badan = (strlen(token)>0 ? atof(token) : -1.0f); break;
                case 13: u.kadar_kolesterol = (strlen(token)>0 ? atoi(token) : -1); break;
                case 14: u.kadar_kolesterol_ldl = (strlen(token)>0 ? atoi(token) : -1); break;
                case 15: u.trombosit = (strlen(token)>0 ? atoi(token) : -1); break;
                default: break;
            }
            field++;
            token = strtok_r(NULL, ";", &saveptr);
        }

        if (field <= 4) {
            // minimal sampai riwayat
            u.riwayat_penyakit[0] = '\0';
        }

        if (userCount < MAX_USERS) {
            users[userCount++] = u;
        }
    }

    fclose(fp);
}

User* findUserByUsername(const char* username) {
    for (int i = 0; i < userCount; i++) {
        if (strcmp(users[i].username, username) == 0) {
            return &users[i];
        }
    }
    return NULL;
}
