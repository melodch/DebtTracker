#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <gtk/gtk.h>

#define BUTTON_SPACING 40

void show_group(GtkWidget *show_group, gpointer data);
void create_new_group(GtkWidget *new_group, gpointer data);
void ok_return_to_main(GtkWidget *calculate, gpointer data);
void set_up_main_menu();
void new_group_action(char* filename, char* names, int num_of_users);
