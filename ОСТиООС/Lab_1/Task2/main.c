#include "comands.h"

int main()
{
    printf("=== Command Shell ===\n");

    USERS all_users;
    switch (init_users(&all_users))
    {
    case -1:
        printf("Error of init array of Users!\n");
        return -1;
    
    case -2:
        printf("Error of allocating memory for array of Users!\n");
        return -2;
    }

    while (1) 
    {
        switch (show_login_menu(&all_users))
        {
        case 0:
            return 0; // user wants to exit program
        case 1:
            continue;
        case -1:
            printf("Error in user registration!\n");
            return -3;
        case -2:
            printf("Error in memory reallocation!\n");
            free_all(&all_users);
            return -4;
        case -3:
            printf("Pointer in function is NULL!\n");
            return -5;
        }
    }

    return 0;
}