CC     = gcc
CFLAGS = -Wall -Wextra -std=c11 -g
OBJ    = main.o liste.o

demo: $(OBJ)
	gcc $(CFLAGS) -o $@ $^

main.o: main.c liste.h
	gcc $(CFLAGS) -c main.c -o main.o

liste.o: liste.c liste.h
	gcc $(CFLAGS) -c liste.c -o liste.o

clean:
	rm -f $(OBJ) demo

.PHONY: clean
