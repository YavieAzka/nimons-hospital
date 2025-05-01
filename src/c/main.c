// Include any necessary headers
#include <stdio.h>
#include "../header/user.h"
#include "../header/login.h"


int main() {
    // Your code goes here
    User u;
    
     u = login(&u);
     printf("#%s", u.username);
     return 0;
}