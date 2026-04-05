#ifndef COMANDS_H
#define COMANDS_H


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>

#define LOGIN_LEN (7) // 6 символов + '\0'

typedef struct user
{
    char login[LOGIN_LEN];
    int pin;
    int is_logged_in;
    int is_sanctioned;
} USER;
typedef struct users
{
    USER * ptr;
    int size;
    int capacity;

} USERS;

int show_login_menu(USERS* users);
int init_users(USERS * users);
int register_user(USERS * users);
void free_all(USERS * users); 
int login_user(USERS* users);
int shell_loop(USER* current_user, USERS* all_users);
int find_user(USERS * users, const char * login);


#endif // COMANDS_H