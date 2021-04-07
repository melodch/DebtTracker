#include "main.h"

void new_group_input() {

    char file_str[FILENAME_MAX];
    char name_str[MAXLINE];
    char n_of_users[4];
    int num_of_users;

    // Get group filename, number of users in the group,
    // and user names
    puts("Enter group name: ");
    fgets(file_str, FILENAME_MAX, stdin);

    puts("Enter number of users: ");
    fgets(n_of_users, 4, stdin);
    num_of_users = atoi(n_of_users);

    char* names_arr[num_of_users];
    puts("Enter user names: ");
    fgets(name_str, MAXLINE, stdin);
    char* name = strtok(name_str, " \n");
    int name_i = 0;
    while (name) {
        names_arr[name_i] = name;
        name = strtok(NULL, " \n");
        name_i++;
        if (name==NULL && name_i < num_of_users) {
            puts("Number of user names given doesn't match number of users");
            exit(EXIT_FAILURE);
        }
    }

    new_group_action(file_str, names_arr, num_of_users);
}

void log_input() {

    char file_str[FILENAME_MAX];
    char user1[USERNAME_MAX], user2[USERNAME_MAX];
    char change[5];
    char message[MESSAGE_MAX];
    int one, two, ch;
    char exp_or_settle[3];

    // Get group filename, users that transaction is happening between,
    // payment, and message to attach to transaction
    puts("Enter group name: ");
    fgets(file_str, FILENAME_MAX, stdin);

    puts("Enter 'e' for expense, 's' for settlement: ");
    fgets(exp_or_settle, 3, stdin);
    char exp_or_set = exp_or_settle[0];

    puts("Enter first user: ");
    fgets(user1, USERNAME_MAX, stdin);
    user1[strcspn(user1, " \n")] = 0;
    one = user_to_index(file_str, user1);

    puts("Enter second user: ");
    fgets(user2, USERNAME_MAX, stdin);
    user2[strcspn(user2, " \n")] = 0;
    two = user_to_index(file_str, user2);

    puts("Enter payment value: ");
    fgets(change, 5, stdin);
    ch = atoi(change);

    puts("Enter message: ");
    fgets(message, MESSAGE_MAX, stdin);

    if (exp_or_set == 'e') log_action(file_str, one, two, ch);
    else log_action(file_str, two, one, ch);
    update_bills(user1, user2, ch, message, exp_or_set);
}

void generate_personal_bill() {

    char file_str[FILENAME_MAX];
    char user[USERNAME_MAX];
    int user_i;

    // Get group filename and user name to generate personal bill for
    puts("Enter group name: ");
    fgets(file_str, FILENAME_MAX, stdin);

    puts("Enter user name: ");
    fgets(user, USERNAME_MAX, stdin);
    user[strcspn(user, " \n")] = 0;

    generate_personal_bill_action(file_str, user);
}

void add_user_input() {

    char group_name[FILENAME_MAX]; 
    char addedUser[USERNAME_MAX];

    // Get group filename and user name to add
    puts("Add this user to: ");
    fgets(group_name, FILENAME_MAX, stdin);
    
    puts("Enter user: ");
    fgets(addedUser, USERNAME_MAX, stdin);
    
    add_user(group_name, addedUser);

}
