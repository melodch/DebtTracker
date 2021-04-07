csvaction.o: csvaction.c gtkapp.h
	gcc -c csvaction.c
gtkapp.o: gtkapp.c csvaction.o
	# gcc -c gtkapp.c
	gcc `pkg-config --cflags gtk+-3.0` gtkapp.c `pkg-config --libs gtk+-3.0`

gtk_program: gtkapp.o
	gcc -Wall gtkapp.o csvaction.o -g -o gtk_program
