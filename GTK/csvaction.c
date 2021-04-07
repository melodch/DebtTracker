#include "gtkapp.h"

// initialize CSV file with values 0, generate bill txt files
// void new_group_action(char* filename, char* names_str, int num_of_users) {
void new_group_action(char* filename, char* names, int num_of_users) {

    FILE *csv_file;
    FILE *bill_file;
    char* names_arr[num_of_users];
    char* user_names = strdup(names);
    
    char* name = strtok(user_names, " \n");
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

    csv_file = fopen(filename,"w+");

    fprintf(csv_file,"Name");
    for (int n = 0; n < num_of_users; n++) {
        fprintf(csv_file, " %s", names_arr[n]);
    }

    for(int i = 0; i < num_of_users; i++) {
        // Set up CSV file
        fprintf(csv_file, "\n%s", names_arr[i]);
        for(int j = 0; j < num_of_users; j++) {
            fprintf(csv_file," %d", 0);
        }

        // Create bill file
        bill_file = fopen(names_arr[i],"w+");
        fclose(bill_file);
    }
    fclose(csv_file);
    free(user_names);
}
