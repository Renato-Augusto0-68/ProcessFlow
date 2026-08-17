ProcessFlow : main.o
	gcc main.o -o ProcessFlow

main.o = main.c
		gcc -c main.c


run: app 
	./app

clean: 
		rm -f *.o

.PHONY: run clean
	