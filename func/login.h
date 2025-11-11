#ifndef LOGIN_H
#define LOGIN_H

#include <stdio.h>
#include <string.h>

// ================= STRUCTURE =================

struct User
{
    char username[50];
    char password[50];
};

// ================= FUNCTION DECLARATIONS =================

int registerUser();
int loginUser(char currentUser[]);

#endif
