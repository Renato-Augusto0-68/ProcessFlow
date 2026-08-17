ProcessFlow: main.o functions.o
			gcc main.o functions.o -o ProcessFlow

main.o: main.c 
	gcc -c main.c

functions.o: tasks.c tasks.h 
		gcc -c tasks.c


run: ProcessFlow 
	./ProcessFlow

clean: 
	rm -f *.o a.out ProcessFlow

.PHONY: run clean
	