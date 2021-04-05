#include "main.h"

/*  TODO:
    Functions to
        DONE create new group
        -    add new user
        DONE log a settlement / expense
        -    generate personal total
        DONE update personal bills
 */
int main() {

    char action[3];

    puts("0: Set up new group");
    puts("1: Log expense or settlement");
    puts("2: Add user");
    puts("3: Generate personal bill");
    puts("4: View exchanges for user");
    
    puts("What would you like to do? (Input Number)");
    fgets(action, 3, stdin);
    int action_num = atoi(action);
    switch(action_num) {
        case 0:
            new_group_input();
            break;
        
        case 1:
            log_expense_or_settlement();
            break;

        case 3:
            generate_personal_bill();
            break;

        default:
            printf("default");
    }
}
