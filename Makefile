ProcessFlow: main.o tasks.o
			gcc main.o tasks.o -o ProcessFlow

main.o: main.c tasks.h
	gcc -c main.c

tasks.o: tasks.c tasks.h 
		gcc -c tasks.c


run: ProcessFlow 
	./ProcessFlow

clean: 
	rm -f *.o a.out ProcessFlow

.PHONY: run clean
	