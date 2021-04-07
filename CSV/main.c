#include "main.h"

// Main menu function to return to after each action
void mainMenu() {
    char action[3];

    puts("0: Set up new group");
    puts("1: Log expense or settlement");
    puts("2: Add user");
    puts("3: Generate personal bill");
    
    puts("What would you like to do? (Input Number)");
    fgets(action, 3, stdin);
    int action_num = atoi(action);
    switch(action_num) {
        case 0:
            new_group_input();
            break;
        case 1:
            log_input();
            break;
        case 2: 
            add_user_input();
            break;
        case 3: 
            generate_personal_bill();
            break;
    }
}

int main() {
    
    mainMenu();

}