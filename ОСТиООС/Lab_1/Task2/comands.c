#include "comands.h"

int init_users(
  USERS * users)
{
  if(users == NULL)
  {
    return -1;
  }
  if((users->ptr = malloc(sizeof(USER) * 16)) == NULL)
  {
    return -2;   
  }
  users->size = 0;
  users->capacity = 16;
  return 0;
}

int is_valid_login(
  char const * login) 
{
  if(login == NULL){return -1;}
  int len = strlen(login);
  int i;
  if (len == 0 || len > 6)
  {
    return -2;
  }
  for (i = 0; i < len; i++) 
  {
      if (isalnum(login[i]) == 0)
      {
        return -2;
      }
  }
  return 0;
}


int find_user(
  USERS * users, 
  char const * login) 
{
  if(users == NULL || login == NULL){return -1;}
  int i;
  for (i = 0; i < users->size; i++) 
  {
      if (strcmp(users->ptr[i].login, login) == 0) 
      {
          return i;
      }
  }
  return -2;
}


int register_user(
  USERS * users) 
{
  if (!users)
  {
    return -1;
  }

  if (users->size >= users->capacity) 
  {
    int new_capacity = users->capacity << 1;
    USER * temp = (USER*)realloc(users->ptr, new_capacity * sizeof(USER));
    if (!temp) 
    {
      printf("Memory allocation failed!\n");
      return -2;
    }
    users->ptr = temp;
    users->capacity = new_capacity;
  }

  //Geting login
  char login[LOGIN_LEN];
  printf("Enter login (up to 6 alphanumeric chars): ");
  fgets(login, sizeof(login), stdin);
  login[strcspn(login, "\n")] = 0;

  switch(is_valid_login(login)) 
  {
    case -2:
      printf("Invalid login. Must be 1-6 alphanumeric characters.\n");
      return 1;
    case -1:
      return -3;
  }

  switch(find_user(users, login)) 
  {
    case -1:
      return -4;
    case -2:
      // printf("User '%s' already exists.\n", login);
      // return 1;
      break;
    default:
      printf("User '%s' already exists.\n", login);
      return 1;
  }

  // //cleaning scanf buf for entering login
  //   while (getchar() != '\n');

  // getting PIN
  int pin;
  printf("Enter PIN (0-100000): ");
  if (scanf("%d", &pin) != 1 || pin < 0 || pin > 100000) 
  {
      printf("Invalid PIN.\n");
      while (getchar() != '\n');
      return 1;
  }

  USER * u = &users->ptr[users->size];
  strcpy(u->login, login);
  u->pin = pin;
  u->is_logged_in = 0;
  u->is_sanctioned = 0;
  users->size++;

  printf("User '%s' registered successfully.\n", login);
  return 0;
}

int login_user(USERS * users) 
{
  if (!users)
  {
    return -1;
  }
  // getting login
  char login[LOGIN_LEN];
  printf("Login: ");
  fgets(login, sizeof(login), stdin);
  login[strcspn(login, "\n")] = 0;

  switch(is_valid_login(login)) 
  {
    case -2:
      printf("Invalid login format.\n");
      return 1;
    case -1:
      return -3;
  }

  int idx = find_user(users, login);
  if (idx == -1) 
  {
    return -4;
  }
  else if (idx == -2)
  {
    printf("User not found!\n");
    return 1;
  }

  int pin;
  printf("PIN: ");
  if (scanf("%d", &pin) != 1 || pin < 0 || pin > 100000) 
  {
    printf("Invalid PIN.\n");
    while (getchar() != '\n');
    return 1;
  }
  getchar();

  if (users->ptr[idx].pin != pin) 
  {
      printf("Incorrect PIN.\n");
      return 1;
  }

  if (users->ptr[idx].is_sanctioned) 
  {
    printf("Access denied: this account is under sanctions.\n");
    return 1;
  }

  users->ptr[idx].is_logged_in = 1;
  printf("Welcome, %s!\n", login);

  switch(shell_loop(&users->ptr[idx], users))
  {
    case -1:
      return -3;

  }

  users->ptr[idx].is_logged_in = 0;

  return 0;
}

int shell_loop(
  USER * current_user, 
  USERS * all_users) 
{
  if(current_user == NULL || all_users == NULL){return -1;}
  char command[64];
  while (1) 
  {
    printf("%s> ", current_user->login);
    fflush(stdout);

    if (fgets(command, sizeof(command), stdin) == NULL) 
    {
      printf("\nSession ended.\n");
      break;
    }

    // Убираем символ новой строки
    command[strcspn(command, "\n")] = 0;

    // Убираем пробелы в начале
    char* cmd = command;
    while (isspace((unsigned char)*cmd)) cmd++;

    // Пустая строка — пропускаем
    if (strlen(cmd) == 0) continue;

    // --- Команда: Time ---
    if (strcmp(cmd, "Time") == 0) 
    {
      time_t t = time(NULL);
      struct tm tm = *localtime(&t);
      printf("%02d:%02d:%02d\n", tm.tm_hour, tm.tm_min, tm.tm_sec);
    }
    // --- Команда: Date ---
    else if (strcmp(cmd, "Date") == 0) 
    {
      time_t t = time(NULL);
      struct tm tm = *localtime(&t);
      printf("%02d:%02d:%04d\n", tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1900);
    }
    // --- Команда: Howmuch ---
    else if (strncmp(cmd, "Howmuch", 7) == 0) 
    {
      char * args = cmd + 7;
      while (isspace((unsigned char)*args)) args++;

      int day, month, year, hour, min, sec;
      char flag[4];
      int matched = sscanf(args, "%d:%d:%d %d:%d:%d %3s",
                          &day, &month, &year, &hour, &min, &sec, flag);

      if (matched != 7) 
      {
          printf("Invalid format. Use: Howmuch dd:MM:yyyy hh:mm:ss -f\n");
          continue;
      }

      if (strcmp(flag, "-s") != 0 && strcmp(flag, "-m") != 0 &&
          strcmp(flag, "-h") != 0 && strcmp(flag, "-y") != 0) 
      {
          printf("Invalid flag. Use: -s, -m, -h, -y\n");
          continue;
      }

      if (day < 1 || day > 31 || month < 1 || month > 12 ||
          year < 1900 || hour < 0 || hour > 23 ||
          min < 0 || min > 59 || sec < 0 || sec > 59) 
      {
          printf("Invalid date or time.\n");
          continue;
      }

      struct tm past = {0};
      past.tm_mday = day;
      past.tm_mon  = month - 1;
      past.tm_year = year - 1900;
      past.tm_hour = hour;
      past.tm_min  = min;
      past.tm_sec  = sec;
      past.tm_isdst = -1;

      time_t past_time = mktime(&past);
      time_t now = time(NULL);

      if (past_time == (time_t)(-1) || difftime(now, past_time) < 0) 
      {
        printf("Invalid date/time or future date.\n");
        continue;
      }

      double seconds = difftime(now, past_time);
      double result;

      if (strcmp(flag, "-s") == 0) result = seconds;
      else if (strcmp(flag, "-m") == 0) result = seconds / 60.0;
      else if (strcmp(flag, "-h") == 0) result = seconds / 3600.0;
      else if (strcmp(flag, "-y") == 0) result = seconds / (365.25 * 24 * 3600);
      else continue;

      printf("%.0f\n", result);
    }

    // --- Команда: Logout ---
    else if (strcmp(cmd, "Logout") == 0) 
    {
      printf("Logging out...\n");
      break; 
    }
    // --- Команда: Sanctions <username> ---
    else if (strncmp(cmd, "Sanctions", 9) == 0) 
    {
      char* args = cmd + 9;
      while (isspace((unsigned char)*args)) args++;

      if (strlen(args) == 0) 
      {
        printf("Usage: Sanctions <username>\n");
        continue;
      }

      char target_login[LOGIN_LEN];
      sscanf(args, "%6s", target_login);  // максимум 6 символов

      // Проверка: нельзя санкционировать себя
      if (strcmp(current_user->login, target_login) == 0) 
      {
        printf("Error: You cannot apply sanctions to yourself.\n");
        continue;
      }

      int idx = find_user(all_users, target_login);
      if (idx == -2) 
      {
        printf("User '%s' not found.\n", target_login);
        continue;
      }

      printf("Enter 52 to confirm sanctions on user '%s': ", target_login);
      int confirmation;
      if (scanf("%d", &confirmation) != 1 || confirmation != 52) 
      {
          printf("Sanctions not applied.\n");
          while (getchar() != '\n');
          continue;
      }
      getchar(); // убираем \n

            all_users->ptr[idx].is_sanctioned = 1;
            printf("User '%s' has been sanctioned. Access to shell is blocked.\n", target_login);
    }
    // --- Неизвестная команда ---
    else 
    {
      printf("Unknown command: '%s'\n", cmd);
    }
    }
}


int show_login_menu(
  USERS * users) 
{
    int choice;
    printf("\n--- Login Menu ---\n");
    printf("1. Register\n");
    printf("2. Login\n");
    printf("0. Exit\n");
    printf("Choose: ");

    if (scanf("%d", &choice) != 1) 
    {
      printf("Error! Invalid input!\n");
      while (getchar() != '\n'); //cleaning scanf buf
      return -1; 
    }
    //cleaning scanf buf for entering login
    while (getchar() != '\n'); 
    switch (choice) 
    {
      case 1:
        switch(register_user(users))
        {
          case -1:
            printf("The pointer to an array of users is NULL!\n");
            return -1;
          case -2:
            printf("Memory allocation failed!\n");
            return -2;
          // case -3:
          //   return -3;
          case -4:
            return -3;
          case 1:
            return 1;// continue program
          case 0:
            return 1;// continue program
        }

      case 2:
        switch(login_user(users))
        {
          case -1:
            return -3;
          // case -3:
          //   return -3;
          case -4:
            return -3;
          case 1:
            return 1;
          case 0:
            return 1;
        }

      case 0:
        printf("Goodbye!\n");
        return 0;  // user wants to exit

      default:
        printf("Invalid choice. Please select 0, 1, or 2.\n");
        return 1; // continue program 
    }
}

void free_all(
  USERS * users) 
{
    if (users == NULL) 
    {
      return;
    }
    if (users->ptr != NULL) 
    {
      free(users->ptr);
      users->ptr = NULL;
    }
    users->size = 0;
    users->capacity = 0;
}