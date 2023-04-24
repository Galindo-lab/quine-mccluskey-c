compile:
	gcc -W -Wall -pedantic -std=c99 main.c
	valgrind --tool=memcheck --leak-check=yes ./a.out