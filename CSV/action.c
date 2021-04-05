#include "main.h"

#define MAXLINE 200

int user_to_index(char* filename, char* user) {

    FILE *file;
    char line[MAXLINE + 6];
    int loop_index = 0;
    int target_index = -1;

    file = fopen(filename,"r");
    if (fgets(line, sizeof (line), file)) {
        char* value = strtok(line, " \n");
        while (value) {
            // printf("value: %s, user: %s\n", value, user);
            if (strcmp(value, user) == 0) {
                target_index = loop_index;
                // printf("target i: %d\n", target_index);
            }
            value = strtok(NULL, " \n");
            loop_index++;
        }
    }

    return target_index;
}

// initialize CSV file with values 0, generate bill txt files
void new_group_action(char* filename, char* names[], int num_of_users) {

    FILE *csv_file;
    FILE *bill_file;

    // filename=strcat(filename,".csv");
    csv_file = fopen(filename,"w+");

    fprintf(csv_file,"Name");
    for (int n = 0; n < num_of_users; n++) {
        fprintf(csv_file, " %s", names[n]);
    }

    for(int i = 0; i < num_of_users; i++) {
        // Set up CSV file
        fprintf(csv_file, "\n%s", names[i]);
        for(int j = 0; j < num_of_users; j++) {
            fprintf(csv_file," %d", 0);
        }

        // Create bill file
        bill_file = fopen(names[i],"w+");
        fclose(bill_file);
    }
    fclose(csv_file);
}

// Given row, col index, increment the value at that location by 'change'
void log_action(char* file, int c, int r, int change) {

    FILE* fp = fopen(file, "r");
    if (!fp) printf("Can't open file (loc_func)\n"); 
    else {
        // create new csv which we will copy all values from old csv into, except for changed value
        FILE *new_fp;
        char *new_file = "newfile";
        new_fp = fopen(new_file,"w+");
        char buffer[1024];
        int column;
        int row = 0;
        
        while (fgets(buffer, 1024, fp)) {
            column = 0;
            char* value = strtok(buffer, " \n");
            while (value) {
                if (column == c && row == r) {
                    int num = atoi(value);
                    num += change;
                    fprintf(new_fp, "%d ", num);
                }
                if (column == r && row == c) {
                    int num = atoi(value);
                    num -= change;
                    fprintf(new_fp, "%d ", num);
                }
                else (fprintf(new_fp,"%s ", value));
                value = strtok(NULL, " \n");
                column++;
            }
            fprintf(new_fp,"\n");
            row++;
        }
        fclose(fp);
        fclose(new_fp);
        // implementation-defined?
        // https://stackoverflow.com/questions/41926099/does-the-c-rename-function-delete-files
        rename(new_file, file);
    }
}

void update_bills(char* user1, char* user2, int payment, char* message) {

    FILE *file;

    file = fopen(user1, "a");
    if(file == NULL) {
        perror("Error opening user1 file");
    }
    fprintf(file, "You paid %s $%d for", user2, payment);
    fprintf(file, "%s", message);
    fclose(file);

    file = fopen(user2, "a");
    if(file == NULL) {
        perror("Error opening user2 file");
    }
    fprintf(file, "%s paid you $%d for", user1, payment);
    fprintf(file, "%s", message);
    fclose(file);
}