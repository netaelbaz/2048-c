CC=gcc
OBJS= main.o game.o
EXEC=prog
DEBUG= -g
CFLAGS=-std=c99 -Wall -Werror $(DEBUG)

$(EXEC) : $(OBJS)
	$(CC) $(OBJS) -o $@
  
game.o: game.c game.h
main.o: main.c game.h

clean:
	rm -f $(OBJS) $(EXEC)
	
