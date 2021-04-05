#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXLINE 200
#define USERNAME_MAX 20
#define MESSAGE_MAX 100

void new_group_input();
void log_expense_or_settlement();
void generate_personal_bill();
void new_group_action(char* filename, char* names[], int num_of_users);
void update_bills(char* user1, char* user2, int payment, char* message, char expense_or_settle);
int user_to_index(char* filename, char* user);
char* index_to_user(char* filename, int user_i);
void log_action(char* file, int c, int r, int change);
void generate_personal_bill_action(char* filename, int user_i);
