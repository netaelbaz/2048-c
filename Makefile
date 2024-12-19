CC=gcc
OBJS= main.o game.o gui.o
EXEC=prog
DEBUG= -g
CFLAGS=-std=c99 -Wall -Werror $(DEBUG)

$(EXEC) : $(OBJS)
	$(CC) $(OBJS) -o $@
  
game.o: game.c game.h gui.h
gui.o: gui.c gui.h
main.o: main.c game.h

clean:
	rm -f $(OBJS) $(EXEC)
	
