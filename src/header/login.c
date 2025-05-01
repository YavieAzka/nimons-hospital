#include "user.h"
#include <stdio.h>

//Read user.csv file and store it in users[] array.
int load_user_data(const char* filename, User users[], int* user_count){
    FILE *user_file = fopen(filename, "r");
    char line[512];
    fgets(line, sizeof(line), user_file);
    *user_count = 0;
    
    while(fgets(line, sizeof(line), user_file)){
        
        //printf("%s\n", line);
    }
}
int login(User users[], int user_count, char* input_username, char* input_password){

}

int main(){
    User u[5]; int *count;
    load_user_data("../../data/user.csv", u, count);
}