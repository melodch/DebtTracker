#include "main.h"

#define MAXLINE 200

int user_to_index(char* filename, char* user) {

    FILE *file;
    char line[MAXLINE + 6];
    int loop_index = 0;

    file = fopen(filename,"r");
    if (fgets(line, sizeof (line), file)) {
        char* value = strtok(line, " \n");
        while (value) {
            // printf("value: %s, user: %s\n", value, user);
            if (strcmp(value, user) == 0) {
                return loop_index;
                // printf("target i: %d\n", target_index);
            }
            value = strtok(NULL, " \n");
            loop_index++;
        }
    }

    return -1;
}

char* index_to_user(char* filename, int user_i) {

    FILE *file;
    char line[MAXLINE + 6];
    int loop_index = 0;

    file = fopen(filename,"r");
    if (fgets(line, sizeof (line), file)) {
        char* value = strtok(line, " \n");
        while (value) {
            printf("loop_index: %d, user_i: %d\n", loop_index, user_i);
            if (loop_index == user_i) {
                printf("value: %s\n", value);
                return value;
            }
            value = strtok(NULL, " \n");
            loop_index++;
        }
    }

    puts("Index to user error");
    exit(EXIT_FAILURE);
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
    if (!fp) printf("Can't open file\n"); 
    else {
        // create new csv which we will copy all values from old csv into, except for changed value
        FILE *new_fp;
        char *new_file = "newfile";
        new_fp = fopen(new_file,"w+");
        char buffer[MAXLINE];
        int column;
        int row = 0;
        
        while (fgets(buffer, MAXLINE, fp)) {
            column = 0;
            char* value = strtok(buffer, " \n");
            while (value) {
                if (column == c && row == r) {
                    int num = atoi(value);
                    num += change;
                    fprintf(new_fp, "%d ", num);
                }
                else if (column == r && row == c) {
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

void update_bills(char* user1, char* user2, int payment, char* message, char exp_or_settle) {

    FILE *file;

    file = fopen(user1, "a");
    if(file == NULL) {
        perror("Error opening user1 file");
    }
    if (exp_or_settle == 'e') {
        fprintf(file, "You paid %s $%d for ", user2, payment);
        fprintf(file, "%s", message);
    }
    else {
        fprintf(file, "%s owes you $%d for ", user1, payment);
        fprintf(file, "%s", message);
    }
    fclose(file);
    
    file = fopen(user2, "a");
    if(file == NULL) {
        perror("Error opening user2 file");
    }
    if (exp_or_settle == 'e') {
        fprintf(file, "%s paid you $%d for ", user1, payment);
        fprintf(file, "%s", message);
    }
    else {
        fprintf(file, "You owe %s $%d for ", user2, payment);
        fprintf(file, "%s", message);
    }
    fclose(file);
}

void generate_personal_bill_action(char* filename, int user_i) {

    char file_str[FILENAME_MAX];
    FILE* file = fopen(filename, "r");
    int row = 0, col = 0;
    char buffer[MAXLINE];
    int val;
    int total = 0;

    strcpy(file_str, filename);
    FILE* new_file = fopen(strcat(filename,"_total"), "w+");

    if (!file) printf("Can't open file\n");
    while (fgets(buffer, 1024, file)) {
        if (row == user_i) {
            char* value = strtok(buffer, " \n");
            while (value) {
                char* name = index_to_user(file_str, col);
                val = atoi(value);
                if (val <= 0) fprintf(new_file, "You owe %s $%d\n", name, val);
                else if (val > 0) fprintf(new_file, "%s owes you $%d\n", name, val);
                total += val;
                value = strtok(NULL, " \n");
                col++;
            }
        }
        row++;
    }

    fprintf(new_file, "\nYour total is $%d", total);

    fclose(new_file);
    fclose(file);
}