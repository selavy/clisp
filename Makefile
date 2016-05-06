CC=gcc
CFLAGS=-Wall -Werror -g
RE2C=re2c
OBJS=first.o
TARGET=first

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) -o $(TARGET) $(CFLAGS) $(OBJS)
first.o: first.c
	$(CC) $(CFLAGS) -c first.c
first.c: first.re
	$(RE2C) -o first.c first.re
.PHONY: clean
clean:
	rm -rf $(OBJS) first.c $(TARGET)
