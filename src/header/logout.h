#ifndef LOGOUT_h
#define LOGOUT_h

#include <stdio.h>

typedef int LogType;
#define LOGGED_IN 1
#define LOGGED_OFF 0

LogType logout(LogType status);

#endif