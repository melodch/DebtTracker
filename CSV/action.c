#include "main.h"

#define MAXLINE 200

int user_to_index(char* filename, char* user) {

    FILE *file;
    char line[MAXLINE];
    char buffer[MAXLINE];
    int loop_index = 0;

    file = fopen(filename,"r");
    if (fgets(line, MAXLINE, file)) {
        strcpy(buffer, line);
        fclose(file);
    }
    char* value = strtok(buffer, " \n");
    while (value) {
        if (strcmp(value, user) == 0) {
            return loop_index;
        }
        value = strtok(NULL, " \n");
        loop_index++;
    }
    return -1;
}

void index_to_user(char* filename, int user_i, char* names[]) {

    FILE *file;
    char line[MAXLINE];
    char buffer[MAXLINE];
    int loop_index = 0;

    file = fopen(filename,"r");
    if (fgets(line, MAXLINE, file)) {
        // Copy first line of file into buffer
        strcpy(buffer, line);
        fclose(file);
    }
    else {
        puts("Index to user error");
        exit(EXIT_FAILURE);
    }

    // Loop through line of names
    char* value = strtok(buffer, " \n");
    while (value) {
        // if (loop_index == user_i) {
        //     strcpy(names[loop_index], value);
        // }
        strcpy(names[loop_index], value);
        value = strtok(NULL, " \n");
        loop_index++;
    }
    
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
        char line[MAXLINE];
        char buffer[MAXLINE];
        int column;
        int row = 0;
        
        while (fgets(line, MAXLINE, fp)) {
            column = 0;
            strcpy(buffer, line);
            char* value = strtok(buffer, " \n");
            while (value) {
                printf("value: %s\n", value);
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
        fprintf(file, "%s owes you $%d for ", user2, payment);
        fprintf(file, "%s", message);
    }
    else {
        fprintf(file, "You paid %s $%d for ", user2, payment);
        fprintf(file, "%s", message);        
    }
    fclose(file);
    
    file = fopen(user2, "a");
    if(file == NULL) {
        perror("Error opening user2 file");
    }
    if (exp_or_settle == 'e') {
        fprintf(file, "You owe %s $%d for ", user1, payment);
        fprintf(file, "%s", message);
    }
    else {
        fprintf(file, "%s paid you $%d for ", user1, payment);
        fprintf(file, "%s", message);
    }
    fclose(file);
}

void generate_personal_bill_action(char* filename, char *user) {

    FILE* file = fopen(filename, "r");
    int row = 0;
    char line[MAXLINE];
    char buffer[MAXLINE];
    char* names[50];
    int val;
    int total = 0;
    int user_i = user_to_index(filename, user);

    char file_str[FILENAME_MAX];
    strcpy(file_str, filename);
    FILE* new_file = fopen(strcat(user,"_total"), "w+");

    // Populate array of user names
    int loop_index = 0;
    if (fgets(line, MAXLINE, file)) {
        // Copy first line of file into buffer
        strcpy(buffer, line);
    }
    else {
        puts("Index to user error");
        exit(EXIT_FAILURE);
    }
    // Loop through line of names
    char* value = strtok(buffer, " \n");
    while (value) {
        // if (loop_index == user_i) {
        //     strcpy(names[loop_index], value);
        // }
        strcpy(names[loop_index], value);
        value = strtok(NULL, " \n");
        loop_index++;
    }

    if (!file) printf("Can't open file\n");
    while (fgets(line, MAXLINE, file)) {
        printf("line: %s", line);
        if (row == user_i) {
            int col = 1;
            strcpy(buffer, line);
            char* value = strtok(buffer, " \n");
            int val_i = 0;
            while (value) {
                printf("value: %s\n", value);
                val = atoi(value);
                if (val < 0) fprintf(new_file, "You owe %s $%d\n", names[col], -val);
                else if (val > 0) fprintf(new_file, "%s owes you $%d\n", names[col], val);
                total += val;
                value = strtok(NULL, " \n");
                col++;
                val_i++;
            }
        }
        row++;
    }

    fprintf(new_file, "\nYour total is $%d", total);

    fclose(new_file);
    fclose(file);
}

void add_user(char* filename, char *addedUser) {

    FILE *file;
    FILE *fPtr;
    FILE *fTemp;
    char buffer[BUFFER_SIZE];

    // This makes the new users individual csv file
    char *name = addedUser;
    file = fopen(name, "w+");

    // Open the required file:
    fPtr = fopen(filename, "r");
    fTemp = fopen("replace.tmp", "w");

    /* fopen() return NULL if unable to open file in given mode. */
    if (fPtr == NULL || fTemp == NULL)
    {
        /* Unable to open file hence exit */
        printf("\nUnable to open file.\n");
        printf("Please check whether file exists and you have read/write privilege.\n");
        exit(EXIT_SUCCESS);
    }

    int count = 1;
    while (fgets(buffer, BUFFER_SIZE, fPtr)) {
        char* val = strtok(buffer, "\n");
        if (count == 1) {
            sprintf(val, "%s %s", val, name);
            fprintf(fTemp, "%s", val);
        }
        if (count > 1) {
            val = strcat(val, " 0");
            fprintf(fTemp, "%s\n", val);
        }
        count++;
    }

    // Adding the last line
    name[strcspn(name, "\n")] = 0;
    fprintf(fTemp, "%s", name);               // changed from replace.tmp to fTemp
    for (int a = 0; a < count - 1; a++) {
        fprintf(fTemp," %d", 0);                //  changed from replace.tmp to fTemp
    }

    fclose(fPtr);
    fclose(fTemp);
    /* Rename temporary file as original file */
    rename("replace.tmp", filename);
    /* Once made a new file, I want to 
        1. Write to the "name bar" in the CSV file
        2. Append to the file and make row with 0's
    */

    fclose(file);
    mainMenu();
}