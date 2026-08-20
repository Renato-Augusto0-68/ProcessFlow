ProcessFlow: main.o functions.o
			gcc main.o functions.o -o ProcessFlow

main.o: main.c tasks.h task.h
	gcc -c main.c

functions.o : tasks.o terminal.o
	gcc -c tasks.o terminal.o

tasks.o: tasks.c tasks.h task.h 
		gcc -c tasks.c

terminal.o: terminal.c terminal.h task.h
		gcc -c terminal.c

run: ProcessFlow 
	./ProcessFlow

clean: 
	rm -f *.o a.out ProcessFlow

.PHONY: run clean
	