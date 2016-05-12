CC=gcc
CFLAGS=-Wall -Werror -g
OBJS=lexer.o main.o token.o parser.o
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
