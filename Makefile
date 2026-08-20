CFLAGS = -I.

ProcessFlow: src/main.o tasks.o terminal.o
	gcc src/main.o tasks.o terminal.o -o ProcessFlow

src/main.o: src/main.c functions/tasks.h functions/task.h functions/terminal.h
	gcc $(CFLAGS) -c src/main.c -o src/main.o

tasks.o: functions/tasks.c functions/tasks.h functions/task.h
	gcc $(CFLAGS) -c functions/tasks.c -o tasks.o

terminal.o: functions/terminal.c functions/terminal.h functions/task.h
	gcc $(CFLAGS) -c functions/terminal.c -o terminal.o

run: ProcessFlow 
	./ProcessFlow

clean: 
	rm -f *.o a.out ProcessFlow

.PHONY: run clean
	