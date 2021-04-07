#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXLINE 200
#define USERNAME_MAX 20
#define MESSAGE_MAX 100
#define BUFFER_SIZE 1000

// File operations
void generate_personal_bill();
void update_bills(char* user1, char* user2, int payment, char* message, char expense_or_settle);
int user_to_index(char* filename, char* user);
void index_to_user(char* filename, int user_i, char* name);

// "Set up a new group" functions
void new_group_input();
void new_group_action(char* filename, char* names[], int num_of_users);

// "Log expense or settlement" functions
void log_input();
void log_action(char* file, int c, int r, int change);

// "Add User" functions
void add_user_input();
void add_user(char* filename, char *addedUser);

// "Generate personal bill" functions
void generate_personal_bill();
void generate_personal_bill_action(char* filename, char* user);

// "Main menu" function
void mainMenu();
