ProcessFlow: main.o tasks.o
			gcc main.o tasks.o -o ProcessFlow

ProcessFlow: src/main.o tasks.o terminal.o
	gcc src/main.o tasks.o terminal.o -o ProcessFlow

tasks.o: tasks.c tasks.h task.h
		gcc -c tasks.c


run: ProcessFlow 
	./ProcessFlow

clean: 
	rm -f *.o a.out ProcessFlow

.PHONY: run clean
	