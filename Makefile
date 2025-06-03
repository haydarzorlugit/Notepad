
CC = gcc
CFLAGS = -Wall -std=c99


TARGET = notepad


SRCS = main.c notepad.c password.c


OBJS = $(SRCS:.c=.o)


all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^


clean:
	rm -f *.o $(TARGET)