#makefile for sentence array project
CC = g++
CFLAGS = -Wall -Werror -g
OBJS = ARR.o main.o

run: $(OBJS)
	$(CC) $(CFLAGS) -o run $(OBJS)

$(OBJS): ARR.h

clean:
	-rm -f *.o run
