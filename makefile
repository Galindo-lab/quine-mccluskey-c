compile:
	# gcc -W -Wall -O3 -pedantic -std=c99 main.c
	gcc -W -Wall -pedantic -std=c99 main.c
	./a.out

memory:	
	valgrind --tool=memcheck --leak-check=yes ./a.out

time:
	time ./a.out
