CC=gcc
CFLAGS=-Wall -Werror -g
RE2C=re2c
#OBJS=first.o
#TARGET=first
OBJS=lexer.o main.o
TARGET=clisp

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) -o $(TARGET) $(CFLAGS) $(OBJS)
main.o: main.c
	$(CC) $(CFLAGS) -c main.c
lexer.o: lexer.c lexer.h token.h
	$(CC) $(CFLAGS) -c lexer.c
#first.o: first.c
#	$(CC) $(CFLAGS) -c first.c
#first.c: first.re
#	$(RE2C) -o first.c first.re
.PHONY: clean
clean:
	rm -rf $(OBJS) first.c $(TARGET)
