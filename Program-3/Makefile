Programa: main.o stack.o queue.o
	gcc main.o stack.o queue.o -o Programa

main.o: main.c
	gcc -c main.c

queue.o: queue.c header.h
	gcc -c queue.c

stack.o: stack.c header.h
	gcc -c stack.c

clean:
	rm *.o Programa