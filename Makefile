CC=gcc
RELEASE=-DNDEBUG
DEBUG=-g
CFLAGS=-Wall -Werror $(DEBUG) -pedantic
OBJS=lexer.o main.o token.o parser.o object.o
TARGET=clisp
LEMON=lemon

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) -o $(TARGET) $(CFLAGS) $(OBJS)
#parse.c parse.h: $(LEMON) parse.y
#	$(LEMON) parse.y
#$(LEMON): lemon.c
#	$(CC) $< -o $@
%.o: %.c %.h
	$(CC) -o $@ $(CFLAGS) -c $<

.PHONY: clean
clean:
	rm -rf $(OBJS) $(TARGET) $(LEMON) parse.h parse.c parse.out
