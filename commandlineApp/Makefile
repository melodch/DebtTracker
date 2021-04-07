input.o: input.c main.h
	gcc -c input.c
action.o: action.c main.h
	gcc -c action.c
main.o: main.c action.o input.o
	gcc -c main.c 

csv_program: main.o
	gcc -Wall main.o input.o action.o -g -o csv_program
