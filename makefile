compile:
	gcc -W -Wall -pedantic -std=c99 main.c
	./a.out

memoryTest:	
	valgrind --tool=memcheck --leak-check=yes ./a.out