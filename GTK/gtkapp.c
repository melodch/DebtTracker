#include "gtkapp.h"
/*
 To install GTK:
 sudo apt-get install libgtk-3-dev
 To compile this program:
 gcc `pkg-config --cflags gtk+-3.0` gtkapp.c -o gtkapp `pkg-config --libs gtk+-3.0`
 */

GtkWidget *main_window, *fixed;
GtkWidget *fnInput, *nuInput, *unInput;
char *filename, *user_names;
int num_of_users;

void show_group(GtkWidget *show_group, gpointer data) {

    GtkWidget *csv;
    char* file_contents = NULL;
    FILE* fp = fopen("test", "r");

    size_t len;
    ssize_t bytes_read = getdelim( &file_contents, &len, '\0', fp);
    if ( bytes_read != -1) {
        
        csv = gtk_label_new(file_contents);
        gtk_fixed_put(GTK_FIXED(fixed), csv, 200, 35);
        gtk_widget_set_size_request(csv, 100, 100);

        gtk_widget_show_all(main_window);
    }
}

void create_new_group(GtkWidget *new_group, gpointer data) {

    GtkWidget *filename_lbl, *num_users_lbl, *user_names_lbl;
    GtkWidget *ok;

    int button_i = 1;
    int label_col_i = 200;
    int input_col_i = 350;

    // Set up entry boxes
    fnInput = gtk_entry_new();
    nuInput = gtk_entry_new();
    unInput = gtk_entry_new();
    gtk_fixed_put(GTK_FIXED(fixed), fnInput, input_col_i, (button_i++)*BUTTON_SPACING);
    gtk_fixed_put(GTK_FIXED(fixed), nuInput, input_col_i, (button_i++)*BUTTON_SPACING);
    gtk_fixed_put(GTK_FIXED(fixed), unInput, input_col_i, (button_i++)*BUTTON_SPACING);
    
    // Set up labels
    button_i = 1;
    filename_lbl = gtk_label_new("File name:");
    num_users_lbl = gtk_label_new("Number of users:");
    user_names_lbl = gtk_label_new("User names:");
    gtk_fixed_put(GTK_FIXED(fixed), filename_lbl, label_col_i, (button_i++)*BUTTON_SPACING);
    gtk_fixed_put(GTK_FIXED(fixed), num_users_lbl, label_col_i, (button_i++)*BUTTON_SPACING);
    gtk_fixed_put(GTK_FIXED(fixed), user_names_lbl, label_col_i, (button_i++)*BUTTON_SPACING);
    
    // Set up OK button
    ok = gtk_button_new_with_label("OK");
    gtk_fixed_put(GTK_FIXED(fixed), ok, label_col_i, button_i*BUTTON_SPACING);
    g_signal_connect(ok, "clicked", G_CALLBACK(ok_return_to_main), NULL);
    gtk_widget_set_size_request(ok, 30, 30);

    gtk_widget_show_all(main_window);

}

void ok_return_to_main(GtkWidget *calculate, gpointer data) {

    // Store data input
    filename = (char *)gtk_entry_get_text(GTK_ENTRY(fnInput));
    num_of_users = atoi((char *)gtk_entry_get_text(GTK_ENTRY(nuInput)));
    user_names = (char *)gtk_entry_get_text(GTK_ENTRY(unInput));

    new_group_action(filename, user_names, num_of_users);

    gtk_container_remove(GTK_CONTAINER(main_window), fixed);
    set_up_main_menu();
}

void set_up_main_menu() {

    GtkWidget *show_csv, *new_group, *log_exp, *log_set, *bill;

    fixed = gtk_fixed_new();
    gtk_container_add(GTK_CONTAINER(main_window), fixed);

    // Create buttons on left hand side
    int button_i = 0;
    show_csv = gtk_button_new_with_label("Show group");
    g_signal_connect(show_csv, "clicked", G_CALLBACK(show_group), NULL);
    gtk_fixed_put(GTK_FIXED(fixed), show_csv, 0, (button_i++)*BUTTON_SPACING);
    gtk_widget_set_size_request(show_csv, 80, 30);

    new_group = gtk_button_new_with_label("Set up a new group");
    g_signal_connect(new_group, "clicked", G_CALLBACK(create_new_group), NULL);
    gtk_fixed_put(GTK_FIXED(fixed), new_group, 0, (button_i++)*BUTTON_SPACING);
    gtk_widget_set_size_request(new_group, 80, 30);

    log_exp = gtk_button_new_with_label("Log an expense");
    gtk_fixed_put(GTK_FIXED(fixed), log_exp, 0, (button_i++)*BUTTON_SPACING);
    gtk_widget_set_size_request(log_exp, 80, 30);

    log_set = gtk_button_new_with_label("Log a settlement");
    gtk_fixed_put(GTK_FIXED(fixed), log_set, 0, (button_i++)*BUTTON_SPACING);
    gtk_widget_set_size_request(log_set, 80, 30);

    bill = gtk_button_new_with_label("Generate a bill");
    gtk_fixed_put(GTK_FIXED(fixed), bill, 0, (button_i++)*BUTTON_SPACING);
    gtk_widget_set_size_request(bill, 80, 30);

    gtk_widget_show_all(main_window);
}

int main(int argc, char *argv[]) {

    gtk_init(&argc, &argv);
    main_window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(main_window), "Debt Tracker");
    gtk_window_set_default_size(GTK_WINDOW(main_window), 600, 250);
    gtk_window_set_position(GTK_WINDOW(main_window), GTK_WIN_POS_CENTER);
    gtk_window_set_resizable(GTK_WINDOW(main_window), FALSE);

    set_up_main_menu();

    g_signal_connect(G_OBJECT(main_window), "destroy", 
        G_CALLBACK(gtk_main_quit), NULL);

    gtk_main();

    return 0;
}

// Create new group
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
        // Set up group file
        fprintf(csv_file, "\n%s", names_arr[i]);
        for(int j = 0; j < num_of_users; j++) {
            fprintf(csv_file," %d", 0);
        }

        // Create individual bill files
        bill_file = fopen(names_arr[i],"w+");
        fclose(bill_file);
    }
    fclose(csv_file);
    free(user_names);
}
