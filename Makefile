CC = gcc

CFLAGS = -Wall -Wextra -Iinclude

SRC = \
scr/main.c \
scr/affichage.c \
scr/persistance.c \
scr/transport.c \
scr/utils.c

TARGET = app


all:
	$(CC) $(CFLAGS) $(SRC) -o $(TARGET)


run: all
	./$(TARGET)


clean:
	rm -f $(TARGET)


reset: clean all