// Include any necessary headers
#include <stdio.h>
#include "../header/user.h"
#include "../header/login.h"
#include "../header/register.h"

int main() {
     // users adalah array yang menampung data User.
     int user_count = 0;
     User u;
    
    u = login(&u);
    printf("#%s", u.username);
    return 0;
}