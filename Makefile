CFLAGS = -I.

ProcessFlow: main.o tasks.o terminal.o
	gcc main.o tasks.o terminal.o -o ProcessFlow

main.o: main.c functions/tasks.h functions/task.h functions/terminal.h
	gcc $(CFLAGS) -c main.c -o main.o

tasks.o: functions/tasks.c functions/tasks.h functions/task.h
	gcc $(CFLAGS) -c functions/tasks.c -o tasks.o

terminal.o: functions/terminal.c functions/terminal.h functions/task.h
	gcc $(CFLAGS) -c functions/terminal.c -o terminal.o

run: ProcessFlow
	./ProcessFlow

clean:
	rm -f src/*.o *.o a.out ProcessFlow

.PHONY: run clean