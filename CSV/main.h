#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXLINE 200
#define USERNAME_MAX 20
#define MESSAGE_MAX 100

void new_group_input();
void log_expense_or_settlement();
void new_group_action(char* filename, char* names[], int num_of_users);
void update_bills(char* user1, char* user2, int payment, char* message);
int user_to_index(char* filename, char* user);
void log_action(char* file, int c, int r, int change);
