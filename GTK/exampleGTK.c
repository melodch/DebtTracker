#include <stdlib.h>
#include <stdio.h>
#include <gtk/gtk.h>

/*  To install GTK:
    sudo apt-get install libgtk-3-dev
    To compile: 
    gcc `pkg-config --cflags gtk+-3.0` exampleGTK.c -o exampleGTK `pkg-config --libs gtk+-3.0`
 */
// static GtkWidget *number1;
// static GtkWidget *number2;
static GtkWidget *test, *test1, *test2, *test3;
GtkWidget *window, *grid, *new_group, *fixed;

// Add widget
// void show_new_group() {
//   test = gtk_label_new("Hello, World");
//   gtk_grid_attach(GTK_GRID(grid), test, 0, 1, 1, 1);
//   printf("hello");
// }

void show_new_group(GtkWidget *new_group, gpointer data) {
  // char *file = "test";
  FILE* fp = fopen("test", "r");
  if (!fp) printf("Can't open file\n"); 
  else {
    char buffer[500];
    fgets(buffer, 500, fp);
    gtk_label_set_text(GTK_LABEL(test1), buffer);
    fgets(buffer, 500, fp);
    gtk_label_set_text(GTK_LABEL(test2), buffer);
    fgets(buffer, 500, fp);
    gtk_label_set_text(GTK_LABEL(test3), buffer);
    fclose(fp);
    }
  gtk_label_set_text(GTK_LABEL(test), "hello, world");
}

// // Add widget
// static void show_log_input() {
  
// }

// Create GTK Application
static void activate_main_menu(GtkApplication* app, gpointer user_data) {

  // GtkWidget *window, *grid;
  // GtkWidget *log_input;

  window = gtk_application_window_new (app);
  gtk_window_set_title (GTK_WINDOW (window), "Debt Tracker");
  gtk_window_set_default_size (GTK_WINDOW (window), 500, 500);
  gtk_widget_show_all (window);

  grid = gtk_grid_new();
  gtk_container_add(GTK_CONTAINER(window), grid);

  // new_group = gtk_button_new_with_label("Add new group");
  // g_signal_connect(new_group, "clicked", G_CALLBACK(show_new_group), NULL);
  // gtk_grid_attach(GTK_GRID(grid), new_group, 0, 0, 1, 1);

  new_group = gtk_button_new_with_label("Add new group");
  g_signal_connect(new_group, "clicked", G_CALLBACK(show_new_group), NULL);
  gtk_fixed_put(GTK_FIXED(fixed), new_group, 15, 15);
  gtk_widget_set_size_request(new_group, 80, 30);

  // log_input = gtk_button_new_with_label("log_input");
  // g_signal_connect(log_input, "clicked", G_CALLBACK(show_log_input), NULL);
  // gtk_grid_attach(GTK_GRID(grid), log_input, 0, 1, 1, 1);
  
  test = gtk_label_new("Hello, World");
  gtk_grid_attach(GTK_GRID(grid), test, 0, 1, 1, 1);

  test1 = gtk_label_new("Hello, World");
  gtk_grid_attach(GTK_GRID(grid), test1, 0, 2, 1, 1);

  test2 = gtk_label_new("Hello, World");
  gtk_grid_attach(GTK_GRID(grid), test2, 0, 3, 1, 1);

  test3 = gtk_label_new("Hello, World");
  gtk_grid_attach(GTK_GRID(grid), test3, 0, 4, 1, 1);

  gtk_widget_show_all(window);
  gtk_main();

}


int main(int argc, char **argv) {
  GtkApplication *app;
  int status;

  app = gtk_application_new ("gtk.debt.tracker", G_APPLICATION_FLAGS_NONE);
  g_signal_connect (app, "activate", G_CALLBACK (activate_main_menu), NULL);
  status = g_application_run (G_APPLICATION (app), argc, argv);
  g_object_unref (app);

  return status;
}

void add_user(char *addedUser) {
    FILE *file;
    FILE *fPtr;
    FILE *fTemp;
    char buffer[BUFFER_SIZE];
    char c[1000];
    const char zero[3] = " 0";
    char user_count[4];
    int userCount;

    // This makes the new users individual csv file
    char *name = addedUser;
    file = fopen(name, "w+");

    // This is going to replace the first line in the CSV with adding the new User to that line
    // After this, we can just append to the file. 
    char group_name[MAXLINE]; 
    int line_number = 1; 

    // Getting location where to add the user to + count number of users NOW in the group
    puts("Add this user to: ");
    fgets(group_name, MAXLINE, stdin);
    puts("How many users are in this group now (including the new member)? ");
    fgets(user_count, 4, stdin);
    userCount = atoi(user_count);

    // Open the required file:
    fPtr = fopen(group_name, "r");
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
            val = strcat(val, zero);
            fprintf(fTemp, "%s\n", val);
        }
        printf("val: %s", val);
        count++;
    }
    
    // Adding the last line
    
    fprintf(fTemp, "%s", name);               // changed from replace.tmp to fTemp
    for (int a = 0; a < userCount; a++) {
        fprintf(fTemp," %d", 0);                //  changed from replace.tmp to fTemp
    }

    fclose(fPtr);
    fclose(fTemp);
    /* Rename temporary file as original file */
    rename("replace.tmp", group_name);
    /* Once made a new file, I want to 
        1. Write to the "name bar" in the CSV file
        2. Append to the file and make row with 0's
    */

    fclose(file);
    mainMenu();
