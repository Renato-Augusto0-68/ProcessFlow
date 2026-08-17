ProcessFlow: main.o 
			gcc main.o -o ProcessFlow

main.o: main.c 
	gcc -c main.c

run: ProcessFlow 
	./ProcessFlow

clean: 
	rm -f *.o a.out ProcessFlow

.PHONY: run clean
	